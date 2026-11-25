#include "main.h"
#include "lcd.h"

extern I2C_HandleTypeDef hi2c1;

#define LCD_ADDR   (0x21 << 1)           // địa chỉ 7-bit dịch trái cho HAL
#define LCD_BL     0x08                  // bật đèn nền
#define LCD_EN     0x04
#define LCD_RS     0x01

static void lcd_send(uint8_t value, uint8_t rs) {
    uint8_t hi = value & 0xF0;
    uint8_t lo = (value << 4) & 0xF0;
    uint8_t buf[4] = {
        hi | LCD_BL | LCD_EN | rs,  hi | LCD_BL | rs,   // nửa cao: EN lên rồi xuống
        lo | LCD_BL | LCD_EN | rs,  lo | LCD_BL | rs,   // nửa thấp
    };
    HAL_I2C_Master_Transmit(&hi2c1, LCD_ADDR, buf, 4, 100);
}

static void lcd_cmd (uint8_t c) { lcd_send(c, 0); }
static void lcd_data(uint8_t d) { lcd_send(d, LCD_RS); }

void lcd_init(void) {
    HAL_Delay(50);          // chờ LCD khởi động
    lcd_cmd(0x33);          // chuyển sang chế độ 4-bit
    lcd_cmd(0x32);
    lcd_cmd(0x28);          // 4-bit, 2 dòng, font 5x8
    lcd_cmd(0x0C);          // bật màn hình, tắt con trỏ
    lcd_cmd(0x06);          // in xong tự dịch sang phải
    lcd_clear();
}

void lcd_clear(void) {
    lcd_cmd(0x01);
    HAL_Delay(2);           // lệnh clear cần khoảng 1,5 ms
}

void lcd_set_cursor(int row, int col) {
    lcd_cmd((row == 0 ? 0x80 : 0xC0) + col);
}

void lcd_print(const char *s) {
    while (*s) lcd_data(*s++);
}
