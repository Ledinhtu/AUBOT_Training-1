#

## Bài 1: Sử dụng 2 mạch Main với chip STM32F407ZET6 được gọi là mạch A và mạch B.
- Mạch A kết nối với 3 nút nhấn vật lý.
- Mạch B kết nối với màn hình HMI Nextion và bộ RTC.
- Mạch A và B kết nối với nhau bằng Can bus.

- Cụ thể:
	- Mạch A gồm 3 nút nhấn: Nút nhấn xử lý (P button), nút nhấn tăng (U Button), nút nhấn giảm (D button).
	- Mạch B sử dụng bộ RTC để lưu giữ giá trị thời gian hiện tại và hiển thị lên màn hình nextion (hiển thị giờ, phút, giây).
	- Nhấn double-click nút P ở mạch A, màn hình đổi sang trạng thái chỉnh sửa thời gian, nhấn double-click nút P lần nữa sẽ về trạng thái hiển thị bình thường.
		- Nếu đang ở trạng thái chỉnh sửa: Bấm nút tăng, giảm để di chuyển đến vị trí số hiển thị muốn sửa.
			- Bấm nút P (nhấn nhả nhanh) để chỉnh sửa số hiển thị được chọn, bấm nút tăng/ giảm để thay đổi.
		- Nếu nút tăng/giảm được nhấn nhả nhanh thì chỉ thay đổi 1 đơn vị.  Nếu nhấn giữ thì tăng tốc độ thay đổi lên 4 đơn vị/ 1 giây.
			- Bấm nút P (nhấn nhả nhanh) lần nữa để hoàn thành việc chỉnh sửa số hiển thị được chọn.
	- Nhấn double-click nút P ở mạch A lần nữa để hoàn tất việc chỉnh sửa thời gian. Lưu giá trị mới vào bộ RTC trên mạch B và hiển thị lên màn hình Nextion.

> Kiến thức cần có:
>	- Xử lý dữ liệu nhiều trạng thái từ nút nhấn.
>	- Lập trình ngoại vi GPIOs (Nút nhấn), TIMER (Xử lý nút nhấn), CAN (Kết nối 2 mạch), UART (Màn hình nextion), I2C (Bộ RTC).
>	- Yêu cầu sử dụng DMA để truyền nhận dữ liệu.
>	- Lập trình giao diện Nextion (Hiển thị thời gian, giao diện hiển thị và chỉnh sửa).

## Bài 2: Làm quen màn hình HMI Nextion

### Level 1: Tạo lại giao diện chính cho AGV T500 gồm các nút nhấn điều khiển trạng thái Run, Stop, Rẽ trái/phải ở giao lộ. Hiển thị trạng thái của Agv như pin, tốc độ, thẻ RFID.
> Kiến thức cần có: Khả năng tạo giao diện HMI, giao tiếp UART với mạch Main.

### Level 2: Tạo màn hình với 5 nút nhấn ứng với 5 đèn có số thứ tự từ 1 đến 5. Thêm nút Start/Stop
- Hoạt động: Ở trạng thái dừng, bấm 5 nút nhấn theo thứ tự bất kì. Sau khi bấm nút Start thì đèn có thứ tự tương ứng sẽ sáng (lưu ý xử lý trường hợp chưa bấm đủ 5 nút, bấm 1 nút nhiều lần và cả trường hợp bấm nhiều hơn 5 nút thì chỉ nhận 5 nút cuối cùng).

- Ví dụ: Bấm nút 1, 3, 2, 4, 3, 5 thì sau khi bấm Start, đèn sẽ sáng theo thứ tự 3, 2, 4, 3, 5 và lặp lại liên tục đến khi bấm Stop thì về trạng thái dừng.
Hiển thị danh sách 5 nút đã được nhấn.

- Kiến thức cần có: Khả năng tạo giao diện HMI, giao tiếp UART với mạch Main, khả năng xử lý hàng đợi FIFO.

### Level 3:
- Nhà hàng tự động với Agv.
- Sử dụng 3 màn hình Nextion (có thể dùng phần mềm Nextion ở chế độ Debug mà không cần màn hình thực)
- Một màn hình làm server, hai màn còn lại làm Client.
- Server có thể tạo ra danh sách các món ăn và gửi tới màn hình của Client.
- Client có giao diện chọn/hủy món, sau khi chốt thì danh sách sẽ được hiển thị trên màn của server.

> Kiến thức cần có: Khả năng tạo giao diện HMI, giao tiếp UART giữa nhiều hơn 2 thiết bị, khả năng xử lý hàng đợi FIFO.