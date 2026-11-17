#include "main.h"
#include "button.h"

// SỬA theo kết quả bước 3.3: nhấn thì đọc ra 0 hay 1?
#define BTN_PRESSED   GPIO_PIN_RESET
#define BTN_RELEASED  GPIO_PIN_SET

#define LONG_TICKS    100   // 100 × 10 ms = 1 s
#define REPEAT_TICKS  20    // giữ tiếp: lặp mỗi 200 ms

static GPIO_TypeDef* btn_port[NUM_BUTTONS] = { BTN1_GPIO_Port, BTN2_GPIO_Port,
                                               BTN3_GPIO_Port, BTN4_GPIO_Port };
static uint16_t      btn_pin [NUM_BUTTONS] = { BTN1_Pin, BTN2_Pin,
                                               BTN3_Pin, BTN4_Pin };

static GPIO_PinState reg0[NUM_BUTTONS], reg1[NUM_BUTTONS], reg2[NUM_BUTTONS];
static GPIO_PinState stable[NUM_BUTTONS];
static uint16_t hold_cnt[NUM_BUTTONS];
static uint8_t  pressed_flag[NUM_BUTTONS], long_flag[NUM_BUTTONS];

void button_init(void) {
    for (int i = 0; i < NUM_BUTTONS; i++) {
        reg0[i] = reg1[i] = reg2[i] = stable[i] = BTN_RELEASED;
        hold_cnt[i] = pressed_flag[i] = long_flag[i] = 0;
    }
}

void button_scan(void) {
    for (int i = 0; i < NUM_BUTTONS; i++) {
        reg2[i] = reg1[i];
        reg1[i] = reg0[i];
        reg0[i] = HAL_GPIO_ReadPin(btn_port[i], btn_pin[i]);

        if (reg0[i] != reg1[i] || reg1[i] != reg2[i]) continue;   // đang dội, bỏ qua

        if (reg0[i] != stable[i]) {                 // trạng thái ổn định vừa thay đổi
            stable[i] = reg0[i];
            if (stable[i] == BTN_PRESSED) {
                pressed_flag[i] = 1;                // cạnh nhấn xuống, chỉ báo 1 lần
                hold_cnt[i] = 0;
            }
        } else if (stable[i] == BTN_PRESSED) {      // đang giữ
            hold_cnt[i]++;
            if (hold_cnt[i] >= LONG_TICKS) {
                long_flag[i] = 1;
                hold_cnt[i] = LONG_TICKS - REPEAT_TICKS;   // để 200 ms sau báo tiếp
            }
        }
    }
}

int button_is_pressed(int i) {
    if (pressed_flag[i]) { pressed_flag[i] = 0; return 1; }
    return 0;
}

int button_is_long_pressed(int i) {
    if (long_flag[i]) { long_flag[i] = 0; return 1; }
    return 0;
}

void button_clear_all(void) {
    for (int i = 0; i < NUM_BUTTONS; i++) pressed_flag[i] = long_flag[i] = 0;
}
