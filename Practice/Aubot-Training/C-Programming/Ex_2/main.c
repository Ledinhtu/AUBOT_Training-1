#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define CRC8_POLYNOMIAL 0x07 // x^8 + x^2 + x + 1

typedef struct {
    uint8_t start_byte;
    uint8_t length_byte;
    uint8_t *data_byte;
    uint8_t end_byte;
} frame_typdedef;

typedef enum {
    IDLE,
    RECEIVE_LENGTH_BYTE,
    RECEIVE_DATA,
} frame_state;

int32_t CRC_CheckSum(uint8_t length_byte, uint8_t *data_byte)
{
    uint8_t crc = 0;
    for (uint8_t i = 0; i < length_byte; i++) {
        crc ^= data_byte[i];
        for (uint8_t j = 0; j < 8; j++) {
            if (crc & 0x80)
                crc = (crc << 1) ^ CRC8_POLYNOMIAL;
            else
                crc <<= 1;
        }
    }
    return crc;
}

int main(int argc, char* argv[])
{


}