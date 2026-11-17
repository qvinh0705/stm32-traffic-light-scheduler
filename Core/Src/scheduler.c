#include "scheduler.h"
#include "main.h"          // để có __disable_irq / __enable_irq

static sTask    SCH_tasks_G[SCH_MAX_TASKS];
static uint8_t  SCH_count = 0;
static uint32_t next_id   = 1;   // ID 0 dành cho "không có task"

void SCH_Init(void) {
    SCH_count = 0;
    next_id   = 1;
}

// Gọi trong ngắt timer mỗi 10 ms. O(1): chỉ xét task đầu.
void SCH_Update(void) {
    if (SCH_count == 0) return;
    if (SCH_tasks_G[0].Delay > 0) SCH_tasks_G[0].Delay--;
    if (SCH_tasks_G[0].Delay == 0) SCH_tasks_G[0].RunMe = 1;
}


// Chèn task t vào đúng vị trí. t.Delay lúc vào là delay TUYỆT ĐỐI (tính từ bây giờ).
static uint8_t SCH_Insert(sTask t) {
    if (SCH_count >= SCH_MAX_TASKS) return 0;     // đầy

    // (1) Tìm vị trí chèn i, sum = tổng Delay các task đứng trước
    uint8_t  i = 0;
    uint32_t sum = 0;
    while (i < SCH_count && sum + SCH_tasks_G[i].Delay <= t.Delay) {
        sum += SCH_tasks_G[i].Delay;
        i++;
    }

    // (2) Dời các task từ i sang phải 1 ô
    for (uint8_t j = SCH_count; j > i; j--)
        SCH_tasks_G[j] = SCH_tasks_G[j - 1];

    // (3) Đổi Delay tuyệt đối thành tương đối rồi đặt vào ô i
    t.Delay -= sum;
    t.RunMe  = (i == 0 && t.Delay == 0);
    SCH_tasks_G[i] = t;
    SCH_count++;

    // (4) Task ngay sau giờ tính từ task mới nên phải trừ đi
    if (i + 1 < SCH_count)
        SCH_tasks_G[i + 1].Delay -= t.Delay;

    return 1;
}

uint32_t SCH_Add_Task(void (*pFunc)(void), uint32_t DELAY, uint32_t PERIOD) {
    sTask t = { pFunc, DELAY, PERIOD, 0, next_id };
    uint32_t id = NO_TASK_ID;

    __disable_irq();               // không cho SCH_Update chen vào lúc đang dời mảng
    if (SCH_Insert(t)) id = next_id++;
    __enable_irq();

    return id;
}

static void SCH_RemoveAt(uint8_t i) {
    // Task phía sau được "cộng bù" phần Delay của task bị xóa, để vẫn chạy đúng giờ
    if (i + 1 < SCH_count)
        SCH_tasks_G[i + 1].Delay += SCH_tasks_G[i].Delay;

    for (uint8_t j = i; j < SCH_count - 1; j++)
        SCH_tasks_G[j] = SCH_tasks_G[j + 1];
    SCH_count--;

    // Task mới lên đầu có Delay = 0 (chạy cùng lúc với task vừa xóa) thì bật RunMe luôn
    if (SCH_count > 0 && SCH_tasks_G[0].Delay == 0)
        SCH_tasks_G[0].RunMe = 1;
}

void SCH_Dispatch_Tasks(void) {
    while (1) {
        __disable_irq();
        if (SCH_count == 0 || SCH_tasks_G[0].RunMe == 0) {
            __enable_irq();
            break;                       // không còn task nào đến giờ
        }

        sTask t = SCH_tasks_G[0];        // (1) copy task ra
        SCH_RemoveAt(0);                 // (2) xóa khỏi đầu danh sách

        if (t.Period > 0) {              // (3) task chu kỳ: thêm lại, GIỮ NGUYÊN ID
            t.Delay = t.Period;
            SCH_Insert(t);
        }                                //     one-shot (Period = 0): không thêm lại
        __enable_irq();

        t.pTask();                       // (4) chạy task, đặt cuối cùng
    }
}


uint8_t SCH_Delete_Task(uint32_t taskID) {
    uint8_t ok = 0;
    __disable_irq();
    for (uint8_t i = 0; i < SCH_count; i++) {
        if (SCH_tasks_G[i].TaskID == taskID) {
            SCH_RemoveAt(i);
            ok = 1;
            break;
        }
    }
    __enable_irq();
    return ok;
}
