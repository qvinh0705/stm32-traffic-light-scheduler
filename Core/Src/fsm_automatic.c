#include "fsm_automatic.h"
#include "traffic_light.h"
#include "software_timer.h"

// Xuất trạng thái kết hợp ra 2 tuyến. Tuyến chuyển sang ĐỎ được ghi TRƯỚC.
void light_apply(light_state_t s) {
    switch (s) {
    case ST_R1_G2: traffic_set(1, TL_RED);   traffic_set(2, TL_GREEN); break;
    case ST_R1_Y2: traffic_set(1, TL_RED);   traffic_set(2, TL_AMBER); break;
    case ST_G1_R2: traffic_set(2, TL_RED);   traffic_set(1, TL_GREEN); break;
    case ST_Y1_R2: traffic_set(2, TL_RED);   traffic_set(1, TL_AMBER); break;
    default:       traffic_set(1, TL_RED);   traffic_set(2, TL_RED);   break;
    }
}

light_state_t light_next(light_state_t s) {
    switch (s) {
    case ST_R1_G2: return ST_R1_Y2;
    case ST_R1_Y2: return ST_G1_R2;
    case ST_G1_R2: return ST_Y1_R2;
    default:       return ST_R1_G2;      // ST_Y1_R2 và ST_ALL_RED
    }
}

static int duration_s(light_state_t s) {
    return (s == ST_R1_G2 || s == ST_G1_R2) ? time_green : time_amber;
}

// "Entry action": vào một trạng thái thì bật đèn và đặt timer
void fsm_auto_enter(light_state_t s) {
    light_state = s;
    light_apply(s);
    setTimer(TIMER_LIGHT, duration_s(s) * 1000);
}

void fsm_auto_run(void) {
    switch (light_state) {
    case ST_R1_G2:
    case ST_R1_Y2:
    case ST_G1_R2:
    case ST_Y1_R2:
        if (timer_flag[TIMER_LIGHT]) fsm_auto_enter(light_next(light_state));
        break;
    default:                                  // trạng thái lạ: về trạng thái an toàn
        fsm_auto_enter(ST_R1_G2);
        break;
    }
}



