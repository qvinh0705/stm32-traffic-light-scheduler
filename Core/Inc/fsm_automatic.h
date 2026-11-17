#ifndef INC_FSM_AUTOMATIC_H_
#define INC_FSM_AUTOMATIC_H_
#include "global.h"

void          light_apply(light_state_t s);      // dùng chung cho cả 3 chế độ
light_state_t light_next(light_state_t s);
void          fsm_auto_enter(light_state_t s);
void          fsm_auto_run(void);

#endif
