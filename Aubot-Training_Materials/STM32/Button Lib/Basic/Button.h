/**
  ******************************************************************************
  * @file    Button.h
  * @brief   File header cho thư viện xử lý nút nhấn, chương trình cơ bản chỉ sử dụng cho 1 nút nhấn hoạt động.
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef __BUTTON_H__
#define __BUTTON_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdio.h>

/* Define macros -------------------------------------------------------------*/
// #define DEBOUNCE_DELAY 20
// #define TIME_BETWEEN_TWO_PRESS 600

// Khai báo hàm
/**
  * @brief  Hàm lấy trạng thái của Input pin.
  * @note Hàm này cần được định nghĩa lại phù hợp với từng phần cứng, được nhấn trả về 1, nhả nút trả về 0
  * @param  None.
  * @retval Giá trị trạng thái của nút nhấn.
  */
uint8_t get_InputStatus(void);

/**
  * @brief  Hàm cấu hình trạng thái GPIO là Input.
  * @note Hàm này cần được định nghĩa lại phù hợp với từng phần cứng
  * @param  None.
  * @retval Giá trị của thời gian hoạt động của phần cứng, hàm millis() với Arduino, hàm xGetTickCount() với FreeRTOS.
  */
uint32_t get_Button_Millis(void);

/**
  * @brief  Hàm cấu hình trạng thái GPIO là Input.
  * @note Hàm này cần được định nghĩa lại phù hợp với từng phần cứng
  * @param  None.
  * @retval None.
  */
void init_InputGPIO(void);
/**
  * @brief  Hàm khởi tạo thông số cho nút bấm.
  * @param  buttonPressTime tham số quản lý thời gian coi là nhấn nhả.
  * @param  buttonHoldTime tham số quản lý thời gian coi là nhấn giữ .
  * @param  timeBetweenTwoPress tham số thời gian tối đa giữa 2 lần bấm (phục vụ double click) .
  * @retval None.
  */
void init_Button(uint16_t debounceTime, uint16_t buttonHoldTime, uint16_t timeBetweenTwoPress);

// Hàm xử lý trạng thái đầu vào của nút nhấn
/**
  * @brief  Hàm xử lý tín hiệu đầu vào của nút nhấn, hàm cần được gọi trong vòng Loop của chương trình.
  * @param  None.
  * @retval None.
  */
void buttonHandler(void);

// Khai báo các hàm xử lý sự kiện cho từng trạng thái nút nhấn
/**
  * @brief  Hàm xử lý sự kiện nhấn nhả nhanh.
  * @note Hàm này cần được định nghĩa lại phù hợp với từng ứng dụng cụ thể
  * @param  None.
  * @retval None.
  */
void pressShortButton(void);

/**
  * @brief  Hàm xử lý sự kiện nhấn nút.
  * @note Hàm này cần được định nghĩa lại phù hợp với từng ứng dụng cụ thể
  * @param  None.
  * @retval None.
  */
void pressButton(void);

/**
  * @brief  Hàm xử lý sự kiện nhả nút.
  * @note Hàm này cần được định nghĩa lại phù hợp với từng ứng dụng cụ thể
  * @param  None.
  * @retval None.
  */
void releaseButton(void);

/**
  * @brief  Hàm xử lý sự kiện giữ nút nút.
  * @note Hàm này cần được định nghĩa lại phù hợp với từng ứng dụng cụ thể
  * @param  None.
  * @retval None.
  */
void holdButton(void);

/**
  * @brief  Hàm xử lý sự kiện nhấn nút.
  * @note Hàm này cần được định nghĩa lại phù hợp với từng ứng dụng cụ thể
  * @param  None.
  * @retval None.
  */
void doubleClickButton(void);

#ifdef __cplusplus
}
#endif

#endif // __BUTTON_H__
