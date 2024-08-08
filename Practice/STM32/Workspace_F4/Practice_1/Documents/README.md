
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
	- Mỗi DMA có 8 Streams.
	- Mỗi stream quản lí các request truy cập memory cho 1 hoặc nhiều peripheral.
	- Mỗi Stream có thể có tới 8 Channels (Requests).
	- Mỗi Stream có một Arbiter để quản lí mức độ ưu tiên giữa các DMA request.

- 


