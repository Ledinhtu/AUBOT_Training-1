#ifndef AGV_H___
#define AGV_H___

#include <stdio.h>
#include <stdint.h>

#define LENGTH_VERSION 6
#define LENGTH_RFID_BUF 10

typedef struct {
    uint8_t version[10];
    uint8_t battery;
    uint32_t current_speed;
    uint8_t RFID_code[10];

} agv_typdedef;

int32_t agv_init(agv_typdedef *agv, uint8_t *version, uint8_t battery, uint32_t current_speed, uint8_t *RFID_code);

int32_t agv_set_version(agv_typdedef *agv, uint8_t *version);
int32_t agv_set_battery(agv_typdedef *agv, uint8_t battery);
int32_t agv_set_current_speed(agv_typdedef *agv, uint32_t current_speed);
int32_t agv_set_RFID_code(agv_typdedef *agv, uint8_t *RFID_code);

uint8_t* agv_get_version(agv_typdedef *agv);
int32_t agv_get_battery(agv_typdedef *agv);
int32_t agv_get_current_speed(agv_typdedef *agv);
uint8_t* agv_get_RFID_code(agv_typdedef *agv);

#endif /* AGV_H___ */