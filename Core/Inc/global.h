#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

typedef enum { MODE_AUTO, MODE_MANUAL, MODE_TUNING } sys_mode_t;
typedef enum { ST_R1_G2, ST_R1_Y2, ST_G1_R2, ST_Y1_R2, ST_ALL_RED } light_state_t;

#define BTN_MODE  0
#define BTN_NEXT  1
#define BTN_INC   2
#define BTN_DEC   3

#define TIMER_LIGHT  0          // software timer số 0 dành cho đèn

#define TIME_MIN  1             // giây
#define TIME_MAX  99

extern sys_mode_t    mode;
extern light_state_t light_state;
extern int time_red, time_green, time_amber;   // giây

#endif
