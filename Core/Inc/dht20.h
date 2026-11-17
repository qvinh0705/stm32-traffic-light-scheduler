#ifndef INC_DHT20_H_
#define INC_DHT20_H_

void dht20_trigger(void);        // gửi lệnh đo
int  dht20_read(void);           // đọc kết quả, trả về 1 nếu OK
int  dht20_temp_x10(void);       // nhiệt độ × 10, ví dụ 305 = 30.5 °C
int  dht20_hum_x10(void);        // độ ẩm × 10

#endif
