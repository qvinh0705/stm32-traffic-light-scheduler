#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#define NUM_BUTTONS 4

void button_init(void);
void button_scan(void);              // gọi mỗi 10 ms
int  button_is_pressed(int i);       // 1 nếu vừa nhấn (tự xóa cờ)
int  button_is_long_pressed(int i);  // 1 khi giữ 1 s, sau đó lặp lại mỗi 200 ms
void button_clear_all(void) ;
#endif
