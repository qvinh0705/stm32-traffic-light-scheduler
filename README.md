# Đèn giao thông 2 tuyến trên XNUCLEO-F103RB

BTL môn Vi xử lý – Vi điều khiển (CO3009), nhóm `<XX>`.

| Họ và tên | MSSV |
|---|---|
| `<Họ tên>` | `<MSSV>` |
| `<Họ tên>` | `<MSSV>` |
| `<Họ tên>` | `<MSSV>` |

Hệ thống đèn giao thông cho ngã tư 2 tuyến, gồm 3 chế độ Tự động, Bằng tay, Chỉnh thời gian, hiển thị nhiệt độ và độ ẩm (DHT20) trên LCD. Toàn bộ chạy trên scheduler O(1).

## Cấu trúc thư mục

```
Core/
├── Inc/, Src/
│   ├── main.c                     # khởi tạo, ngắt timer, đăng ký task
│   ├── scheduler.*                # scheduler O(1)
│   ├── software_timer.* button.* traffic_light.* lcd.* dht20.*   # module phần cứng
│   ├── global.* display.*
│   └── fsm_mode.* fsm_automatic.* fsm_manual.* fsm_tuning.*      # máy trạng thái
Drivers/                           # HAL do CubeMX sinh ra
<ten-du-an>.ioc
```

## Kết nối phần cứng

| Thiết bị | Khe GROVE |
|---|---|
| Đèn tuyến 1 | D3 – D4 |
| Đèn tuyến 2 | D5 – D6 |
| Nút 1, 2 | D7 – D8 |
| Nút 3, 4 | D9 – D10 |
| DHT20, LCD | Khe I2C (đỏ) |

## Build và nạp

1. Clone repo:
   ```bash
   git clone https://github.com/<tai-khoan>/<ten-repo>.git
   ```
2. Mở STM32CubeIDE, chọn **File → Import → Existing Projects into Workspace**, trỏ tới thư mục repo.
3. Build: `Ctrl + B`.
4. Cắm USB vào cổng ST-Link của mạch, chọn **Run → Run As → STM32 C/C++ Application**.

> Nếu mạch không nạp được: kiểm tra file `.ioc` có **SYS → Debug = Serial Wire**.

## Cách sử dụng

Khi khởi động, hệ thống vào chế độ Tự động (mặc định Đỏ 7 s, Xanh 5 s, Vàng 2 s).

| Nút | Tự động | Bằng tay | Chỉnh thời gian |
|---|---|---|---|
| Nút 1 (MODE) | Sang Bằng tay | Sang Chỉnh thời gian | Lưu và về Tự động |
| Nút 2 (NEXT) | – | Chuyển trạng thái đèn kế tiếp | Chọn đèn cần chỉnh |
| Nút 3 (+) | – | – | Tăng 1 s (giữ để tăng nhanh) |
| Nút 4 (−) | – | – | Giảm 1 s (giữ để giảm nhanh) |

Khi chỉnh thời gian, cả 2 tuyến chuyển Đỏ. Giá trị chỉ được lưu khi **Đỏ = Xanh + Vàng**, nếu sai LCD báo `ERR` và giữ nguyên giá trị cũ.

## Bản nộp

Tag `v1.0-final`.