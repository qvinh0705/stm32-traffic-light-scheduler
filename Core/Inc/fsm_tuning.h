#ifndef INC_FSM_TUNING_H_
#define INC_FSM_TUNING_H_

void        fsm_tuning_enter(void);
void        fsm_tuning_run(void);
int         fsm_tuning_try_save(void);   // 1 = lưu được, 0 = sai ràng buộc

// cho display đọc
const char* tuning_item_name(void);
int         tuning_item_value(void);
int         tuning_value(int i);         // 0 = Đỏ, 1 = Xanh, 2 = Vàng
int         tuning_has_error(void);

#endif
