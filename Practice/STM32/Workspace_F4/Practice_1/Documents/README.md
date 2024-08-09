
## Timer

- STM32F407ZET6 có 14 timer chia làm 3 type:
	1. Advanced-control timers (TIM1, TIM8):
	2. General-purpose timers (TIMx):
		- TIM2, TIM3, TIM4, TIM5
		- TIM9, TIM10, TIM11, TIM12, TIM13, and TIM14
	3. Basic timers TIM6 and TIM7

## USART

## DMA
- Direct memory access (DMA) giúp chuyển dữ liệu tốc độ cao giữa peripheral với memory, giữa memory với memory mà không cần sự tham gia của CPU.

- DMA controller là kết hợp của "Dual AHB master bus architecture" và "FIFO độc lập":
	- Dual AHB master bus architecture:
		- 1 bus để truy cập memory.
		- 1 bus để truy cập peripheral.

- 2 DMA Controller:
	- Mỗi DMA có **8 Streams**:
		```Channel selection

							+---\		
		REQ_STRx_CH7 ------>|	|
		REQ_STRx_CH6 ------>|	|
		REQ_STRx_CH5 ------>|	|
		REQ_STRx_CH4 ------>|	|
							|	|-------> REQ_STREAMx
		REQ_STRx_CH3 ------>|	|
		REQ_STRx_CH2 ------>|	|
		REQ_STRx_CH1 ------>|	|
		REQ_STRx_CH0 ------>|	|
							+---/
							  ^
							  |
						  CHSEL[2:0] = DMA_SxCR[27:25]	


		```
		- Mỗi stream quản lí các request truy cập memory cho 1 hoặc nhiều peripheral.
		- Mỗi Stream có thể có tới 8 Channels (Requests).

	- Mỗi Stream có một **Arbiter** để quản lí mức độ ưu tiên giữa các DMA request:
		- Arbiter thực hiện:
			- Quản lí 8 DMA request dựa trên priotity cho mỗi 2 AHB master ports (memory và peripheral ports) của chúng.
			- Khởi chạy peripheral/memory access sequences.

		- Priorities được quản lí trong 2 stages:
			1. Software:
				- Mỗi Stream priority được cấu hình thông qua DMA_SxCR register.
				- 4 levels:
					- Very high priority.
					- High priority.
					- Medium priority.
					- Low priority.
			2. Hardware:
				- Nếu 2 request có cùng software priority level, thì stream lower number sẽ có mức priority hơn higher number.

- DMA transactions:
	- Mỗi transaction bao gồm 3 operations:
		1. Loading từ peripheral data register hoặc location in memory thông qua DMA_SxPAR hoặc DMA_SxM0AR register.
		2. Lưu trữ data đã load từ peripheral data register hoặc location in memory thông qua DMA_SxPAR hoặc DMA_SxM0AR register.
		3. Giảm dần DMA_SxNDTR register - chứa số transaction sẽ phải thực hiện.


