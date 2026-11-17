#ifndef INC_LCD_H_
#define INC_LCD_H_

void lcd_init(void);
void lcd_clear(void);
void lcd_set_cursor(int row, int col);   // row 0..1, col 0..15
void lcd_print(const char *s);

#endif
