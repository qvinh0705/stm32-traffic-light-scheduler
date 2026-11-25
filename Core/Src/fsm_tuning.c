#include "fsm_tuning.h"
#include "fsm_automatic.h"
#include "button.h"

static int edit[3];                       // [0] Đỏ  [1] Xanh  [2] Vàng
static int item;                          // đang chỉnh mục nào
static int error;
static const char* names[3] = { "RED", "GREEN", "AMBER" };

void fsm_tuning_enter(void) {
    edit[0] = time_red;  edit[1] = time_green;  edit[2] = time_amber;
    item  = 0;
    error = 0;
    light_state = ST_ALL_RED;             // an toàn: cả 2 tuyến Đỏ khi đang chỉnh
    light_apply(ST_ALL_RED);
}

void fsm_tuning_run(void) {
    if (button_is_pressed(BTN_NEXT)) {
        item = (item + 1) % 3;
        error = 0;
    }
    if (button_is_pressed(BTN_INC) || button_is_long_pressed(BTN_INC)) {
        if (edit[item] < TIME_MAX) edit[item]++;
        error = 0;
    }
    if (button_is_pressed(BTN_DEC) || button_is_long_pressed(BTN_DEC)) {
        if (edit[item] > TIME_MIN) edit[item]--;
        error = 0;
    }
}

int fsm_tuning_try_save(void) {
    if (edit[0] != edit[1] + edit[2]) {   // ràng buộc Đỏ = Xanh + Vàng
        error = 1;
        return 0;
    }
    time_red = edit[0];  time_green = edit[1];  time_amber = edit[2];
    return 1;
}

const char* tuning_item_name(void)  { return names[item]; }
int         tuning_item_value(void) { return edit[item]; }
int         tuning_value(int i)     { return edit[i]; }
int         tuning_has_error(void)  { return error; }
