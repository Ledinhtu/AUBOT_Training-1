
# Nextion

## Mode
- Transparent Data Mode
- Enhanced Models

## Nextion Instruction Set

### General Rules and Practices

- Tất cả các instruction thông qua serial đều kết thúc với 3 bytes là `0xFF 0xFF 0xFF`:
    - Ví dụ:
        ```
        byte ndt[3] = {255,255,255}; write(ndt,3); or print(“\xFF\xFF\xFF”); or print(“ÿÿÿ”)
        ```
- Tất cả các instruction và parameter đều sử dụng ASCII.
- Tất cả các instruction đều dùng chữ cái thường.
- Parameter không có dấu cách trừ khi được yêu cầu.
- ...

- Ví dụ:
    1. MCU gửi tới Nextion.
    2. MCU gửi command: ví dụ ` wept 30,20ÿÿÿ` hoặc `addt 1,0,320ÿÿÿ`.
    3. Nextion yêu cầu



