#include <stdio.h>
#include <string.h>
#include "display.h"
#include "global.h"
#include "lcd.h"
#include "dht20.h"
#include "software_timer.h"
#include "fsm_tuning.h"

static const char* st_name[] = { "R1 G2", "R1 Y2", "G1 R2", "Y1 R2", "ALLRD" };
static char last[2][17];

static void show(int row, const char* s) {
    if (strcmp(s, last[row]) != 0) {          // chỉ in khi khác lần trước
        strcpy(last[row], s);
        lcd_set_cursor(row, 0);
        lcd_print(s);
    }
}

void display_run(void) {
    char l0[17], l1[17];
    int t = dht20_temp_x10(), h = dht20_hum_x10();

    switch (mode) {
    case MODE_AUTO:
        snprintf(l0, sizeof l0, "AUTO   %-5s %2ds", st_name[light_state],
                 (getTimerRemainMs(TIMER_LIGHT) + 999) / 1000);
        snprintf(l1, sizeof l1, "T:%2d.%dC H:%2d.%d%% ", t / 10, t % 10, h / 10, h % 10);
        break;
    case MODE_MANUAL:
        snprintf(l0, sizeof l0, "MANUAL %-9s", st_name[light_state]);
        snprintf(l1, sizeof l1, "T:%2d.%dC H:%2d.%d%% ", t / 10, t % 10, h / 10, h % 10);
        break;
    case MODE_TUNING:
        snprintf(l0, sizeof l0, "TUNE  >%-5s %2ds", tuning_item_name(), tuning_item_value());
        if (tuning_has_error())
            snprintf(l1, sizeof l1, "ERR: R != G + Y ");
        else
            snprintf(l1, sizeof l1, "R%02d G%02d Y%02d     ",
                     tuning_value(0), tuning_value(1), tuning_value(2));
        break;
    }
    show(0, l0);
    show(1, l1);
}
