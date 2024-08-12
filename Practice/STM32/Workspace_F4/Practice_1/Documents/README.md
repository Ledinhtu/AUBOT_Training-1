
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

- **DMA controller**
	- 2 DMA Controller
	- DMA Controller là kết hợp của "Dual AHB master bus architecture" và "FIFO độc lập":
		- Dual AHB master bus architecture:
			- 1 bus để truy cập memory.
			- 1 bus để truy cập peripheral.
		- FIFO:
			- Four-word depth 32 first-in, first-out memory buffers cho mỗi Stream.
			- FIFO Mode:
				1. FIFO mode:
				2. Direct mode:
	
	- DMA mode:
		1. Circular mode:
			- Handle circular buffers and continuous data flows (e.g. ADC scan mode).

		2. Double buffer mode:
			- Circular mode is automatically enabled.

		3. Increment mode:
			- Hữu dụng khi peripheral source hoặc destination data được truy cập thông qua a single register.

	- Direction Transfer modes:
		1. Peripheral-to-memory Mode.
		2. Memory-to-peripheral Mode.
		3. Memory-to-memory Mode.

	- Single and burst transfers:

- **DMA transactions**:
	- Mỗi transaction bao gồm 3 operations:
		1. Loading từ peripheral data register hoặc location in memory thông qua DMA_SxPAR hoặc DMA_SxM0AR register.
		2. Lưu trữ data đã load từ peripheral data register hoặc location in memory thông qua DMA_SxPAR hoặc DMA_SxM0AR register.
		3. Giảm dần DMA_SxNDTR register - chứa số transaction sẽ phải thực hiện.

- **DMA Stream**:
	- Mỗi DMA có *8 Streams*:
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
	- Mỗi Stream có thể có tới 8 Channels (Requests).
	- Mỗi stream quản lí các request truy cập memory cho 1 hoặc nhiều peripheral.

	- Mỗi Stream có một *Arbiter* để quản lí mức độ ưu tiên giữa các DMA request.

	- Mỗi Stream có thể cấu hình để thực hiện:
		1. *Regular type transactions*:
			- Memory-to-Peripherals transfer.
			- Peripherals-to-Memory transfer.
			- Memory-to-memory transfer.
			
		2. *Double-buffer type transactions*:
			- Sử dụng 2 memory pointer cho memory (trong khi DMA đang read/write from/to a buffer, application có thể write/read to/from the other buffer).

- **Arbiter**:
	- Mỗi Stream có một *Arbiter* để quản lí mức độ ưu tiên giữa các DMA request.
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
			- Nếu 2 request có cùng software priority level, thì lower number stream sẽ có mức priority hơn higher number.

- **Source, destination address and Transfer mode**:

	| Bits DIR[1:0] of the DMA_SxCR register	| Direction			| Source address	|  Destination address	|
	|-------------------------------------------|-------------------|-------------------|-----------------------|
	|				00						|Peripheral-to-memory	| DMA_SxPAR			| DMA_SxM0AR			|
	|				01						|Memory-to-peripheral	| DMA_SxM0AR		| DMA_SxPAR				|
	|				10						|Memory-to-memory		| DMA_SxPAR			| DMA_SxM0AR			|
	|				11						| reserved				|					|						|

	- *Peripheral-to-memory mode*:

	- *Memory-to-peripheral mode*:

	- *Memory-to-memory mode*:

- **DMA interrupts**:
	- DMA interrupt requests table:
		| Interrupt event		| Event flag		| Enable control bit	|
		|-----------------------|-------------------|-----------------------|
		| Half-transfer			|	HTIF			|	HTIE				|
		| Transfer complete		|	TCIF			| 	TCIE				|
		| Transfer error		|	TEIF			| 	TEIE				|
		| FIFO overrun/underrun	|	FEIF			| 	FEIE				|
		| Direct mode error		|	DMEIF			| 	DMEIE				|


