
#include <stdio.h>
#include <string.h>

#include "agv.h"

#define DEBUG

#define AGV_ARR_LENGTH 2
#define BUF_LENGTH  100

#define AGV_VERSION "AB2023"
#define AGV_RFID_CODE "IMUS"

/*!
 *  @brief Kiem tra AGV co cac thong so phu hop hay khong.
 *
 *  @param agv: Con tro toi agv_typdedef structure tuong ung cho doi tuong can kiem tra.
 * 
 *  @retval Ma loi:
 *              -1: Tham so khong hop le
 *              1:  AGV chua tham so khong hop le.
 *              0:  AGV co tat ca cac tham so hop le.
 */
int8_t check_agv(agv_typdedef *agv)
{
    if (agv == NULL)
    {
        return -1;
    }
    
    if ((strcmp((char*)agv->version, AGV_VERSION) >= 0) && 
        (agv->battery > 35) && 
        (agv->current_speed >= 20 && agv->current_speed <=25) && 
        (strcmp((char*)agv->RFID_code, AGV_RFID_CODE) == 0))
    {
        return 0;
    }
    
    return 1;
}


agv_typdedef agv_arr[AGV_ARR_LENGTH];

int main(int argc, char* argv[])
{
    int32_t ret = 0;
    uint8_t version[BUF_LENGTH];
    uint8_t battery;
    uint32_t current_speed;
    uint8_t RFID_code[BUF_LENGTH];

#ifdef DEBUG
    printf("Hello.\n");

    agv_init(&agv_arr[0], (uint8_t *)"AB2023", 35, 25, (uint8_t *)"IMUS");

    printf("TEST: %s %d %d %s\n",  agv_get_version(&agv_arr[0]),
                            agv_get_battery(&agv_arr[0]),
                            agv_get_current_speed(&agv_arr[0]),
                            agv_get_RFID_code(&agv_arr[0]));

#endif /* DEBUG */

    for (uint8_t i = 0; i < AGV_ARR_LENGTH; i++)
    {
        printf("Enter parameter for AGV %d:\n", i+1);

        while (1)   /* version */
        {
            printf("\tEnter version: ");
            scanf("%s", version);
            printf("\n");
            if (!agv_set_version(&agv_arr[i], version)) {
                break;
            }
            printf("\tInvalid version parameter!\n");
        }

        while (1) /* Battery */
        {
            printf("\tEnter Battery: ");
            scanf("%hhd", &battery);
            printf("\n");
            if (!agv_set_battery(&agv_arr[i], battery)) {
                break;
            }
            printf("\tInvalid Battery parameter!\n");
        }

        while (1)  /* Current speed */
        {
            printf("\tEnter current speed: ");
            scanf("%d", &current_speed);
            printf("\n");
            if (!agv_set_current_speed(&agv_arr[i], current_speed)) {
                break;
            }
            printf("\tInvalid current speed parameter!\n");
        }

        while (1) /* RFID code */
        {
            printf("\tEnter RFID code: ");
            scanf("%s", RFID_code);
            printf("\n");
            if (!agv_set_RFID_code(&agv_arr[i], RFID_code)) {
                break;
            }
            printf("\tInvalid RFID code parameter!\n");
        }
          
    }


    for (uint8_t i = 0; i < AGV_ARR_LENGTH; i++)
    {
        if(check_agv(&agv_arr[i]) == 0)
        {
            printf("AGV %d is valid.\n", i+1);
        }

    }
    

#ifdef DEBUG   
    for (uint8_t i = 0; i < AGV_ARR_LENGTH; i++)
    {
        printf("AGV %d: %s %d %d %s\n",  i+1,
                            agv_get_version(&agv_arr[i]),
                            agv_get_battery(&agv_arr[i]),
                            agv_get_current_speed(&agv_arr[i]),
                            agv_get_RFID_code(&agv_arr[i]));

    }
    
#endif /* DEBUG */
    return ret;
}

