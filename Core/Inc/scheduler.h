#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include <stdint.h>

#define SCH_MAX_TASKS  20
#define NO_TASK_ID     0

typedef struct {
    void (*pTask)(void);   // hàm task
    uint32_t Delay;        // số tick còn lại, TƯƠNG ĐỐI so với task trước
    uint32_t Period;       // chu kỳ; 0 = one-shot
    uint8_t  RunMe;        // 1 = sẵn sàng chạy
    uint32_t TaskID;
} sTask;

void     SCH_Init(void);
uint32_t SCH_Add_Task(void (*pFunc)(void), uint32_t DELAY, uint32_t PERIOD);
uint8_t  SCH_Delete_Task(uint32_t taskID);
void     SCH_Update(void);
void     SCH_Dispatch_Tasks(void);

#endif
