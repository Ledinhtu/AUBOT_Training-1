#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>

char *received_frames_buffer =  "|0x98|0x05|0x12||0x01||0x06||0xAC||0x04||0x99|";
// char *received_frames_buffer =  "|0x98|0x05|0x12||0x01||0x06||0xAC||0x04||0x99|\n"
//                                 "|0x98|0x03|0x02||0x15||0x1A||0x99|\n"
//                                 "|0x98|0x08|0x08||0x11||0x10||0x00||0x09||0x11||0xAA||0xBB||0x99|\n";

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



int32_t frame_parse(uint8_t *raw_frame, frame_typdedef *frame){

    char *token;
    int32_t ret = -1;

    uint8_t num = 0;

    char* str = (char*)calloc(strlen((char*)raw_frame)+1, sizeof(char));
    if (str == NULL)
    {
        ret = -2;
        goto end;
    }
    
    strcpy(str, (char*)raw_frame);

    /* Start Byte */
    token = strtok((char*)str, "|0x");
    while (token != NULL)
    {
        for (int i = 0; token[i] != '\0'; i++) {
            if ((token[i] < '0') && (token[i] > '9') && (token[i] < 'a') && (token[i] > 'z') && (token[i] < 'A') && (token[i] > 'Z')) 
                return -1;
        }

        num = strtol(token, &token, 16);
        
        if (num == 0x98) {
            frame->start_byte = 0x98;
            ret = 0;
            break;
        } 

        token = strtok(NULL, "|0x");
    }
    
    if (ret != 0)
    {
        return ret;
    }
    
    /* Length Byte */
    token = strtok(NULL, "|0x");
    for (int i = 0; token[i] != '\0'; i++) {
        if ((token[i] < '0') && (token[i] > '9') && (token[i] < 'a') && (token[i] > 'z') && (token[i] < 'A') && (token[i] > 'Z'))
            return -1;
    }

    num = strtol(token, &token, 16);
    frame->length_byte = num;

    frame->data_byte = (uint8_t*)calloc(frame->length_byte, sizeof(uint8_t));
    if (frame->data_byte == NULL)
    {
        ret = -2;
        goto end;
    }
    
    /* Data Bytes */
    for (uint8_t i = 0; i < frame->length_byte; i++)
    {
        token = strtok(NULL, "|0x");

        if (token == NULL)
        {
            ret = -1;
            goto free_data;
        }
        
        for (int i = 0; token[i] != '\0'; i++) {
            if ((token[i] < '0') && (token[i] > '9') && (token[i] < 'a') && (token[i] > 'z') && (token[i] < 'A') && (token[i] > 'Z')) {
                ret = -1 ;
                goto free_data;
            }
        }

        num = strtol(token, &token, 16);
        frame->data_byte[i] = num;

    }

    /* Stop Byte */
    token = strtok(NULL, "|0x");
    for (int i = 0; token[i] != '\0'; i++) {
        if ((token[i] < '0') && (token[i] > '9') && (token[i] < 'a') && (token[i] > 'z') && (token[i] < 'A') && (token[i] > 'Z')) {
            ret = -1 ;
            goto free_data;
        }
    }
    num = strtol(token, &token, 16);
    if (num != 0x99)
    {
        ret = -1;
        goto free_data;
    }
    frame->end_byte = 0x99;

    token = strtok(NULL, "|0x");
    if (token != NULL)
    {
        ret = -1;
        goto free_data;
    }

    goto free_str_cpy;
free_data:
    free(frame->data_byte);
    frame->data_byte = NULL;

free_str_cpy:
    if (str != NULL) {
        free(str);
    }
    str = NULL;
    
end:
    return ret;
}


int main(int argc, char* argv[])
{
    int32_t ret = 0;
    printf("Received Frames: \n%s\n", received_frames_buffer);

    // char *token = strtok(received_frames_buffer, "\n");

    // while (token != NULL)
    // {
        frame_typdedef frame;
        ret = frame_parse((uint8_t *)received_frames_buffer, &frame);
        printf("Ret = %d\n", ret);
        if (ret == 0)
        {
            for (uint8_t i = 0; i < frame.length_byte; i++)
            {
                printf(" 0x%02x", frame.data_byte[i]);
            }
        }
        // token = strtok(NULL, "\n");
    // }
    

    return ret;
}