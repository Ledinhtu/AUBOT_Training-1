#include <string.h>
#include "agv.h"

static int32_t parse_version(uint8_t *version)
{
    if (strlen((char*)version) != LENGTH_VERSION) {
        return -1;
    }
    
    char *str = (char*)version;

    if ((str[0] != 'A') || (str[1] != 'B')) {
        return -1;
    }
    
    for (uint8_t i = 2; i < LENGTH_VERSION; i++)
    {
        if ((str[i] < '0') || ((str[i] > '9')))
        {
            return -1;
        }  
    }
    
    return 0;
}

int32_t agv_init(agv_typdedef *agv, uint8_t *version, uint8_t battery, uint32_t current_speed, uint8_t *RFID_code)
{
    int32_t ret = 0;

    ret = agv_set_version(agv, version);
    if (ret)
    {
        return ret;
    }
    
    ret = agv_set_battery(agv, battery);
    if (ret)
    {
        return ret;
    }

    ret = agv_set_current_speed(agv, current_speed);
    if (ret)
    {
        return ret;
    }

    ret = agv_set_RFID_code(agv, RFID_code);
    if (ret)
    {
        return ret;
    }

    return ret;
}

int32_t agv_set_version(agv_typdedef *agv, uint8_t *version)
{
    if ((agv == NULL) || (version == NULL) || parse_version(version) !=0 )
    {
        return -1;
    }

    if (strcpy((char*)agv->version, (char*)version) == NULL)
    {
        return -2;
    }
    
    return 0;
}

int32_t agv_set_battery(agv_typdedef *agv, uint8_t battery)
{
    if (agv == NULL)
    {
        return -1;
    }

    agv->battery = battery;
    return 0;
}

int32_t agv_set_current_speed(agv_typdedef *agv, uint32_t current_speed)
{
    if (agv == NULL)
    {
        return -1;
    }

    agv->current_speed = current_speed;
    return 0;
}

int32_t agv_set_RFID_code(agv_typdedef *agv, uint8_t *RFID_code)
{
    if ((agv == NULL) || (RFID_code == NULL) || (strlen((char*)RFID_code) >= LENGTH_RFID_BUF))
    {
        return -1;
    }

    if (strcpy((char*)agv->RFID_code, (char*)RFID_code) == NULL)
    {
        return -2;
    }
    
    return 0;
}

uint8_t* agv_get_version(agv_typdedef *agv)
{
    if (agv == NULL)
    {
        return NULL;
    }
    
    return agv->version;
}

int32_t agv_get_battery(agv_typdedef *agv)
{
    if (agv == NULL)
    {
        return -1;
    }
    return agv->battery;
}

int32_t agv_get_current_speed(agv_typdedef *agv)
{
    if (agv == NULL)
    {
        return -1;
    }    
    return agv->current_speed;
}

uint8_t* agv_get_RFID_code(agv_typdedef *agv)
{
    if (agv == NULL)
    {
        return NULL;
    }  
    return agv->RFID_code;
}
