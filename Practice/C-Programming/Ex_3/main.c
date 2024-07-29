#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>  

/*!
 *  @brief Phan tich chuoi IPv4 thanh cac octet.
 *  @param ipaddr: Chuoi IP v4.
 *  @param  a, b, c, d: Con tro de luu tru cac octets.
 *  @retval Ma loi:
 *          -2: Hanh dong khong xac dinh.
 *          -1: Tham so khong hop le.
 *           0: Phan tich thanh cong, khong co loi, cac octet da tach duoc luu trong cac tham so a, b, c, d.
 */
int32_t ip4_addr_parse(uint8_t *ipaddr, uint8_t *a, uint8_t *b, uint8_t *c, uint8_t *d)
{
    uint8_t dots = 0;
    uint32_t num = 0;
    uint8_t len = 0;
    char *token;
    char ip_copy[16];

    if ((ipaddr==NULL) || (a==NULL) || (b==NULL) || (c==NULL))
    {
        return -1;
    }

    len = strlen((char*)ipaddr);
    if ((len > 16) || (len < 7))
    {
        return -1;
    }
    
    strcpy(ip_copy, (char*)ipaddr);
    token = strtok(ip_copy, ".");
    
    while (token != NULL) {
    
        for (int i = 0; token[i] != '\0'; i++) {
            if ((token[i] < '0') || (token[i] > '9')) 
                return -1;
        }
        
        num = atoi(token);
        if (num < 0 || num > 255) 
            return -1;

        switch (dots)
        {
            case 0:
                *a = num;
                break;
            case 1:
                *b = num;
                break;
            case 2:
                *c = num;
                break;
            case 3:
                *d = num;
                break;
            default:
                return -2;
        }
        
        dots++;
        
        token = strtok(NULL, ".");
    }

    if (dots != 4)
        return -1;

    return 0;
}


int main(int argc, char* argv[])
{
    char ipadrr[100] = "";
    uint8_t num[4] = {0};
    int32_t ret = 0;

    while (1)
    {
        printf("Enter IPv4 address: ");
        scanf("%s", ipadrr);

        ret = ip4_addr_parse((uint8_t*)ipadrr, &num[0], &num[1], &num[2], &num[3]);
        if (ret != 0) {
            printf("Invalid Parameter.\n");

        } else {
            for (uint8_t i = 0; i < 4; i++)
            {
                printf(" %d", num[i]);
            }
            printf("\n");
        }
        
    }
    
    return 0;
}