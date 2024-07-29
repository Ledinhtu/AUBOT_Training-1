// Button.c

#include "Button.h"

/**
 * Global variables
**/
uint16_t __debounceTime = 20; //Default value
uint16_t __buttonHoldTime = 2000; //Default value
uint16_t __timeBetweenTwoPress = 600; //Default value

// Biến quản lý trạng thái chống dội phím
uint32_t lastDebounceTime = 0;
uint8_t debounceButtonState = 0;
uint8_t lastDebounceButtonState = 0;

// Biến đếm số lần click (Hỗ trợ sự kiện One-click; Double-click;....)
uint8_t ShortPressCount = 0;

static uint8_t lastButtonState = 0;

// Cờ quản lý các sự kiện với nút nhấn
static uint8_t isShortPressDetected = 0;
static uint8_t isPressDetected = 0;
static uint8_t isReleaseDetected = 0;
static uint8_t isHoldDetected = 0;
static uint8_t isDoubleClickDetected = 0;

// Biến lưu trữ thời gian hoạt động của nút bấm
static uint32_t lastPressTime = 0;
static uint32_t lastReleaseTime = 0;

/**
  * @brief  Hàm lấy trạng thái của Input pin.
  * @note Hàm này cần được định nghĩa lại phù hợp với từng phần cứng, được nhấn trả về 1, nhả nút trả về 0
  * @param  None.
  * @retval Giá trị trạng thái của nút nhấn.
  */
__attribute__((weak)) uint8_t get_InputStatus(void) {
    return 0;
}

/**
  * @brief  Hàm cấu hình trạng thái GPIO là Input.
  * @note Hàm này cần được định nghĩa lại phù hợp với từng phần cứng
  * @param  None.
  * @retval Giá trị của thời gian hoạt động của phần cứng, hàm millis() với Arduino, hàm xGetTickCount() với FreeRTOS.
  */
__attribute__((weak)) uint32_t get_Button_Millis(void) {
    return 0;
}

/**
  * @brief  Hàm cấu hình trạng thái GPIO là Input.
  * @note Hàm này cần được định nghĩa lại phù hợp với từng phần cứng
  * @param  None.
  * @retval None.
  */
__attribute__((weak)) void init_InputGPIO(void) {

}

/**
  * @brief  Hàm khởi tạo thông số cho nút bấm.
  * @param  buttonPressTime tham số quản lý thời gian coi là nhấn nhả.
  * @param  buttonHoldTime tham số quản lý thời gian coi là nhấn giữ .
  * @param  timeBetweenTwoPress tham số thời gian tối đa giữa 2 lần bấm (phục vụ double click) .
  * @retval None.
  */
void init_Button(uint16_t debounceTime, uint16_t buttonHoldTime, uint16_t timeBetweenTwoPress) {
    __debounceTime = debounceTime;
    __buttonHoldTime = buttonHoldTime;
    __timeBetweenTwoPress = timeBetweenTwoPress;
}

// Hàm xử lý trạng thái đầu vào của nút nhấn
/**
  * @brief  Hàm xử lý tín hiệu đầu vào của nút nhấn, hàm cần được gọi trong vòng Loop của chương trình.
  * @param  None.
  * @retval None.
  */
void buttonHandler(void) {
    uint8_t buttonState = get_InputStatus();

    if(lastButtonState != buttonState) {
        lastDebounceTime = get_Button_Millis();
    }
    //Từ lúc ghi nhận trạng thái nút nhấn thay đổi, ta cần đợi 1 khoảng thời gian để tín hiệu ổn định (tức thời gian lớn hơn __debounceTime) sau đó mới lấy trạng thái nút nhấn
    if(get_Button_Millis() - lastDebounceTime > __debounceTime) {
        if(debounceButtonState != buttonState) {
            debounceButtonState = buttonState;
            if(debounceButtonState) {
                lastPressTime =  get_Button_Millis();
                isPressDetected = 1;
            }
        }
    }

    //Kiểm tra số lần bấm nút
    if(isPressDetected == 1 && debounceButtonState == 0){
        uint32_t checkPressTime = get_Button_Millis() - lastPressTime;
        
        if(checkPressTime < __buttonHoldTime && isShortPressDetected == 0) {
            ShortPressCount++; //Biến lưu số lần press (Click)          
        }
    }
		
    //Hàm kiểm tra sự kiện nhấn nút
    if(lastDebounceButtonState == 0 && debounceButtonState == 1) {
        isPressDetected = 1;
        pressButton();
    }

    //Hàm kiểm tra sự kiện nhả nút
    if(lastDebounceButtonState == 1 && debounceButtonState == 0) {
        releaseButton();
        lastReleaseTime = get_Button_Millis();
    }

    if(debounceButtonState == 0) {
        //Reset cờ phát hiện sự kiện
        isShortPressDetected = 0;
        isPressDetected = 0;
        isReleaseDetected = 0;
        isHoldDetected = 0;
        isDoubleClickDetected = 0;

        if(get_Button_Millis() - lastReleaseTime >= __timeBetweenTwoPress){
            //Hàm kiểm tra sự kiện nhấn nhả nhanh
            if(ShortPressCount == 1) {
                isShortPressDetected = 1;
                pressShortButton();
            }
            //Hàm kiểm tra sự kiện double click
            else if(ShortPressCount == 2) {
                doubleClickButton();
                isDoubleClickDetected = 1;
            }

            ShortPressCount = 0;
        }
    }
    //Hàm kiểm tra sự kiện nhấn giữ
    else {
        uint32_t checkPressTime = get_Button_Millis() - lastPressTime;
        if (isHoldDetected == 0 && checkPressTime >= __buttonHoldTime) {
            isHoldDetected = 1;
            holdButton();
        }
    }
    
    lastDebounceButtonState = debounceButtonState;

    lastButtonState = buttonState;
}

/**
  * @brief  Hàm xử lý sự kiện nhấn nhả nhanh.
  * @note Hàm này cần được định nghĩa lại phù hợp với từng ứng dụng cụ thể
  * @param  None.
  * @retval None.
  */
__attribute__((weak)) void pressShortButton(void) {

}

/**
  * @brief  Hàm xử lý sự kiện nhấn nút.
  * @note Hàm này cần được định nghĩa lại phù hợp với từng ứng dụng cụ thể
  * @param  None.
  * @retval None.
  */
__attribute__((weak)) void pressButton(void) {

}

/**
  * @brief  Hàm xử lý sự kiện nhả nút.
  * @note Hàm này cần được định nghĩa lại phù hợp với từng ứng dụng cụ thể
  * @param  None.
  * @retval None.
  */
__attribute__((weak)) void releaseButton(void) {

}

/**
  * @brief  Hàm xử lý sự kiện giữ nút nút.
  * @note Hàm này cần được định nghĩa lại phù hợp với từng ứng dụng cụ thể
  * @param  None.
  * @retval None.
  */
__attribute__((weak)) void holdButton(void) {

}

/**
  * @brief  Hàm xử lý sự kiện nhấn nút.
  * @note Hàm này cần được định nghĩa lại phù hợp với từng ứng dụng cụ thể
  * @param  None.
  * @retval None.
  */
__attribute__((weak)) void doubleClickButton(void) {

}