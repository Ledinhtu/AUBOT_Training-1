
# Nextion

## Mode
- Transparent Data Mode
- Address mode
- Protocol Reparse mode
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
    2. MCU gửi command: ví dụ `wept 30,20ÿÿÿ` hoặc `addt 1,0,320ÿÿÿ`.
    3. Nextion yêu cầu 5ms để chuẩn bị cho transparent mode data transfer.
    4. Nextion gửi "Ready" `0xFF 0xFF 0xFF 0xFF Return Data`.
    5. MCU gửi số lượng raw bytes đã thông báo trước đó (`20`) tới Nextion.
    6. Nextion nhận raw bytes từ MCU tới khi nhận đủ số lượng đã được thông báo.
    7. Nextion gửi "Finished" `0xFD 0xFF 0xFF 0xFF Return Data`.
    8. MCU và Nextion có thể tiến hành các command tiếp theo.
    > NOTE: Nextion sẽ chờ ở bước 5 cho tới khi nhận đủ số raw byte:
        - Trong suốt thời gian này, Nextion không thể thực thi bất kì command nào khác và có thể treo nếu MCU không gửi đủ số byte được chỉ định trong command parameter.
        - Số lượng data bị giới hạn bởi serial buffer (tất cả command + terminations + data < 1024).

- **Address mode**:
    ```
    // Nextion 3 byte termination as per NIS 1.1
    uint8_t ndt[3]= {255,255,255};

    // Turn Address Mode on and set Address to 2556
    Serial.print("addr=2556");
    Serial.write(ndt,3);

    // ref t0 on the Nextion with address 2556 0x09FC
    // Address is sent in little endian order of lowest first
    Serial.write(0xFC);
    Serial.write(0x09);
    Serial.print("ref t0");
    Serial.write(ndt,3);

    // turn off Address Mode for all and set Address to 0 using broadcast 65535
    Serial.write(0xFF);
    Serial.write(0xFF);
    Serial.print("addr=0");
    Serial.write(ndt,3);
    ```

- **Protocol Reparse mode**:
    - Là một kỹ thuật nâng cao cho phép user định nghĩa incoming protocol và incoming serial data riêng của họ.
    - Send `DRAKJHSUYDGBNCJHGJKSHBDNÿÿÿ` thông qua serial để exit active mode serially.




