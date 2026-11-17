#include "software_timer.h"

static int timer_counter[TIMER_NUM];
int timer_flag[TIMER_NUM];

void setTimer(int idx, int duration_ms) {
    timer_counter[idx] = duration_ms / TICK_MS;
    timer_flag[idx]    = (timer_counter[idx] == 0);   // setTimer(i, 0) thì hết hạn ngay
}

void timerRun(void) {
    for (int i = 0; i < TIMER_NUM; i++) {
        if (timer_counter[i] > 0) {
            timer_counter[i]--;
            if (timer_counter[i] == 0) timer_flag[i] = 1;
        }
    }
}

int getTimerRemainMs(int idx) { return timer_counter[idx] * TICK_MS; }
