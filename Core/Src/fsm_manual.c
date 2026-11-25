#include "fsm_manual.h"
#include "fsm_automatic.h"
#include "button.h"

void fsm_manual_enter(void) {
    light_apply(light_state);        // giữ nguyên trạng thái lúc rời AUTO
}

void fsm_manual_run(void) {
    if (button_is_pressed(BTN_NEXT)) {
        light_state = light_next(light_state);   // luôn đi qua Vàng
        light_apply(light_state);
    }
}
