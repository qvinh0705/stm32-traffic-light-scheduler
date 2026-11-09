#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#define TIMER_NUM  10      // số timer, dư ra để dùng dần
#define TICK_MS    10      // khớp với chu kỳ ngắt TIM2

extern int timer_flag[TIMER_NUM];

void setTimer(int idx, int duration_ms);
void timerRun(void);       // gọi mỗi 10 ms
int getTimerRemainMs(int idx);
#endif
