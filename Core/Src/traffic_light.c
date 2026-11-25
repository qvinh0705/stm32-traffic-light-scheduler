#include "main.h"
#include "traffic_light.h"

// Tổ hợp tín hiệu {A, B} cho từng màu
static const uint8_t tl_code[4][2] = {
    [TL_OFF]   = {0, 0},
    [TL_RED]   = {1, 1},
    [TL_AMBER] = {0, 1},
    [TL_GREEN] = {1, 0},
};

static GPIO_TypeDef* portA[2] = { TL1_A_GPIO_Port, TL2_A_GPIO_Port };
static uint16_t      pinA [2] = { TL1_A_Pin,       TL2_A_Pin };
static GPIO_TypeDef* portB[2] = { TL1_B_GPIO_Port, TL2_B_GPIO_Port };
static uint16_t      pinB [2] = { TL1_B_Pin,       TL2_B_Pin };

void traffic_set(int line, tl_color_t color) {
    if (line < 1 || line > 2) return;
    int k = line - 1;
    HAL_GPIO_WritePin(portA[k], pinA[k], tl_code[color][0] ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(portB[k], pinB[k], tl_code[color][1] ? GPIO_PIN_SET : GPIO_PIN_RESET);
}
