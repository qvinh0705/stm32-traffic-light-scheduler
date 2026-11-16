#include "main.h"
#include "dht20.h"

extern I2C_HandleTypeDef hi2c1;

#define DHT20_ADDR  (0x38 << 1)

static int temp_x10 = 0, hum_x10 = 0;

void dht20_trigger(void) {
    uint8_t cmd[3] = { 0xAC, 0x33, 0x00 };
    HAL_I2C_Master_Transmit(&hi2c1, DHT20_ADDR, cmd, 3, 100);
}

int dht20_read(void) {
    uint8_t d[7];
    if (HAL_I2C_Master_Receive(&hi2c1, DHT20_ADDR, d, 7, 100) != HAL_OK) return 0;
    if (d[0] & 0x80) return 0;                       // bit 7 = 1: chưa đo xong

    uint32_t hum_raw  = ((uint32_t)d[1] << 12) | ((uint32_t)d[2] << 4) | (d[3] >> 4);
    uint32_t temp_raw = ((uint32_t)(d[3] & 0x0F) << 16) | ((uint32_t)d[4] << 8) | d[5];

    // Công thức datasheet: RH = raw/2^20 × 100 ;  T = raw/2^20 × 200 − 50
    hum_x10  = (int)((hum_raw  * 1000UL) >> 20);
    temp_x10 = (int)((temp_raw * 2000UL) >> 20) - 500;
    return 1;
}

int dht20_temp_x10(void) { return temp_x10; }
int dht20_hum_x10 (void) { return hum_x10;  }
