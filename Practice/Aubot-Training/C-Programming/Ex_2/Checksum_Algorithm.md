# Checksum Algorithm

- Reference:
    1. [Cyclic Redundancy Check Computation: An Implementation Using the TMS320C54x](https://www.ti.com/lit/an/spra530/spra530.pdf?ts=1721705653636&ref_url=https%253A%252F%252Fwww.google.com%252F)


## 1. Cyclic Redundancy Check (CRC)
- Reference:
    1. [Cyclic Redundancy Check Computation: An Implementation Using the TMS320C54x](https://www.ti.com/lit/an/spra530/spra530.pdf?ts=1721705653636&ref_url=https%253A%252F%252Fwww.google.com%252F)

### 1.1. Introduction

- **Error correction codes**:
    - Cung cấp phương tiện để phát hiện và sửa lỗi do kênh truyền gây ra.
    - Gồm 2 loại chính là:
        1. **Block codes**
            - Bao gồm một tập các **vector** có chiều dài cố định, được gọi là **code word**, chiều dài kí hiệu là **n**.
            - Mỗi phần tử của *code word* được chọn từ **q** phần tử alphabet:
                - Ví dụ, alphabet gồm 0 và 1, binary codes.

            - Có 2^n *code works* trong *binary block code* có chiều dài **n**.
            - Từ 2^n code works này có thể chọn ra M = 2^k code work (k < n) để tạo một **code**.
            - Một block của *k* bits thông tin được map tới một *code work* có chiều dài *n* được chọn từ tập M = 2^k các code work:
                - Được gọi là ***(n, k) code***
                - Rate of the code: ***k/n***

            - Các encoding và decoding function liên quan đến các phép toán số học cộng và nhân được thực hiện trên các code work:
                - Các phép toán này thực hiện theo các quy ước của *algebraic field*.
                - Với binary code: trường là hữu hạn và có 2 phần tử (0 và 1) và có tên  GF(2) (Galois Field).

            - Smallest hamming distance: d_min
                - hamming distance = số bit khác nhau giữa 2 vector (phép XOR)

            - Ví dụ:
                - `m_i`: k-bits information word.
                - `c_i`: n-bits code word, output của encoder:
                    ```
                    c_i = m_i*G (i = 0,1,...,2^k - 1)
                    ```
                - `G`: generator matrix of dimension k*n.
                    - *linear block code* tương đương *systematic code*.
                    - Luôn luôn có thể tìm thấy ma trận G từ *code word* được tạo tởi *k* bit thông tin, theo sau bởi *n-k* parity check bits: 
                        ```
                        G = [I_k, P]
                        ```
                        - `I_k`: ma trận đơn vị k*k.
                        - `P`: ma trận k*(n-k) để kiểm tra parity.

                - `H`: parity check matrix (n-k)*k --> `G*H^T = 0` và nếu code là **systematic**:
                    ```
                    H = [P^T, I_(n-k)]
                    ```
                
                - Vì tất cả code word là tổng tuyến tính của các hàng trong G nên:
                    ```
                    c_i*H^T = 0 với mọi I (i = 0,1,...,2^k - 1)
                    ```

                - Nếu một *code work c* bị lỗi trong quá trình chuyền thì *receiver word c'*:
                    ```
                    c' = c + e
                    ```
                    - `e`: a non-zero error pattern.
                    - *syndrome s* là vector (n-k) chiều:
                        ```
                        s = c'*H^T = (c+e)*H^T = c*H^t + e&H^T = e*H^T
                        ```
                        - *syndrome* là nonzero và phụ thuộc vào code vector.
                        - Nếu *error pattern* là một *code vector* thì error không thể phát hiện.
                
                - Quá trình decoding sẽ sử dụng *standard array decoder* dựa trên *lookup table* để liên kết mỗi *syndrone* với một *error pattern*:
                    - Phương pháp này trở nên bất khả thi khi (n-k) tăng.

                - *Cyclic codes* là một tập con của *Linear block codes* với một *algebraic structure* cho phép encoding để triển khai với một *linear feedback shift register* và decoding mà không cần sử dụng *standard array decoders*.
                    - Vì thế phần lớn *block code* ngày này là *cyclic* hoặc gần với *cyclic code*, các vector là polynomials.
                    - Trong cyclic code, tất cả *code word polynomials* là bội số của *generator polynomial* `g(x)` bậc (n-k).

                    - Polynomal này được chọn để làm ước số của `x^n +1` để một *cyclic shift* của một *code vector* là một *code vector* khác.

                    - Mội messeage polynomial `m_i(x)` có thể được map tới một *code word polynomial* `c(x)`:

                        ```systematic form

                        c_i(x) = m_i(x)*x^(n-k) - r_i(x) với (i=0,1...,2^k-1)
                        ```
                        - `r_i(x)` là phần dư của phép chia `m_i(x)*x^(n-k)` cho `g(x)`.

                - Bước đầu tiên của decoding là xác định xem *receive word* `c'(x)` có phải là bội của `g(x)` hay không:
                    - Thực hiện bằng cách chia `c'(x)` với `g(x)` và kiểm tra phần dư `r(x)`.
                    - Vì đa thức chia (*polynomial division*) là một toán tử tuyến tính (*linear operation*) nên symdrome `g(x)` chỉ phụ thuộc và *error pattern*.
                    - Nguyên lí của CRC:
                        - Nếu `r(x)` là all-zero polynomial thì quá trình truyền có thể không có lỗi hoặc có lỗi nhưng không phát hiện được.
                        - Nếu `r(x)` là non-zero thì ít nhất có xảy ra một lỗi.
                    - Các code mạnh hơn cố gắng sửa lỗi và sử dụng *syndrome* để xác định vị trí lỗi và giá trị của nhiều lỗi.


        2. **Convolutional codes**

-  Cyclic redundancy check (CRC) codes <<  Cyclic codes << Linear block codes

### 1.2. CRC Coding

- *CRC codes* là một tập con của *Cyclic codes* và sử dụng *Systematic codes*.
    - Quy ước bit bên trái nhất đại diện cho bậc cao nhất của đa thức (polynomial).
    - `m(x)`: message polynomial.
    - `c(x)`: code word polynomial.
    - `g(x)`: generator polynomial.
    - `c'(x)`: received message.

    ```
    c(x) = m(x)*g(x) = m(x)*x^(n-k) + r(x)  /* systematic form */

    r(x) = m(x)*x^(n-k) % g(x)              /* CRC bits */
    ```

    - Transmitted message `c(x)` chứa k bits thông tin, theo sau bởi (n-k) CRC bits:
    ```
    c(x) =  [m_(k-1)*x^(n-1) + .. + m_0*x^(n-k)] + [r_(n-k-1)*x^(n-k-1) + ... + r_0]
    ```

    - Quá trình decode, kiểm tra phần dư của phép chia `c'(x)` với `g(x)`:
        - Nếu là all-zero polynomial thì quá trình truyền có thể không có lỗi hoặc có lỗi nhưng không phát hiện được.
        - Nếu là non-zero thì ít nhất có xảy ra một lỗi.

### 1.3. Thuật toán cho tính toán CRC

#### 1.3.1. Bitwise Algorithm (CRCB)

- Bitwise algorithm (CRCB) là một các triển khai phần mềm đơn giản tương tự phương pháp phần cứng sử dụng linear feedback shift register (LFSR)

- Thuật toán phần mềm:
    1. CRC <-- 0
    2. Dịch bit tiếp theo của message vào CRC, nếu bit ngoài cùng bên trái của CRC bằng 1 thì  CRC <-- CRC XOR G. (G = Generator polynomial)
    3. Lặp lại bước 2 cho tới khi đã dịch tất cả các bit của message mở rộng (m'(x) = x_alpha * c(x) + b(x)).

- Có thể tăng tốc độ tính bằng cách dịch nhiều bit cùng lúc để làm giảm số lần lặp nhưng không được lớn hơn bậc của G.
- Sử dụng các giá trị được tính toán trước (**lookup table**) giúp tăng đáng kể tốc độ nhưng sẽ đánh đổi bằng bộ nhớ.

#### 1.3.2. Lookup Table Algorithms

- Code word: `c(x) = x^(n-k)*m(x) + r(x) = a(x)*g(x) + r(x)`
    - Với `r(x)` là CRC polynomial của input message `m(x)`.

- Mở rộng message bằng `alpha` bits: `m'(x) = x^alpha * c(x) + b(x)`
    - Với `b(x) = b_(alpha-1)*x^(alpha-1) + ... + b_0` là alpha-bit mới được thêm.

- CRC của message mở rộng - `r'(x)`:
    ```
    x^(n-k)*m'(x) = x^(n-k)*[x^alpha*c(x) + b(x)] = x^(n-k)*b(x) + x^alpha*a(x)*g(x) + x^alpha*r(x)

    r'(x) = x^(n-k)*m'(x) % g(x) = R_(g(x))[x^(n-k)*m'(x)] = R_(g(x))[x^(n-k)*b(x) +  x^alpha*r(x)]
    ```
