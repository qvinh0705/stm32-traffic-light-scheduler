#include "fsm_mode.h"
#include "global.h"
#include "button.h"
#include "fsm_automatic.h"
#include "fsm_manual.h"
#include "fsm_tuning.h"

void fsm_run(void) {
    if (button_is_pressed(BTN_MODE)) {
        switch (mode) {
        case MODE_AUTO:
            mode = MODE_MANUAL;
            fsm_manual_enter();
            break;
        case MODE_MANUAL:
            mode = MODE_TUNING;
            fsm_tuning_enter();
            break;
        case MODE_TUNING:
            if (!fsm_tuning_try_save()) return;   // sai: ở lại, LCD báo lỗi
            mode = MODE_AUTO;
            fsm_auto_enter(ST_R1_G2);             // chạy lại từ đầu với thời gian mới
            break;
        }
        button_clear_all();                       // bỏ các lần nhấn tồn của chế độ cũ
        return;
    }

    switch (mode) {
    case MODE_AUTO:   fsm_auto_run();   break;
    case MODE_MANUAL: fsm_manual_run(); break;
    case MODE_TUNING: fsm_tuning_run(); break;
    }
}
