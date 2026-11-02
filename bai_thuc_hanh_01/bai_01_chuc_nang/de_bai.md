# ĐỀ BÀI THỰC HÀNH 01: HỆ THỐNG QUẢN LÝ BÃI ĐỖ XE

## 1. Yêu cầu chung
Xây dựng một chương trình quản lý bãi đỗ xe bằng ngôn ngữ C++ áp dụng các nguyên lý của **Lập trình hướng đối tượng (OOP)**. Chương trình cần quản lý các phương tiện ra/vào bãi, tự động tính phí gửi xe dựa trên loại xe, khung giờ cao điểm, thời gian gửi và hỗ trợ xuất báo cáo thống kê.

---

## 2. Mô tả các lớp đối tượng (Class Design)

### Lớp `Car` (Xe / Phương tiện gửi)
Quản lý thông tin chi tiết về từng xe gửi trong bãi.
- **Thuộc tính (Private):**
  - `carID`: Mã định danh của xe (Số nguyên).
  - `carType`: Loại xe (`Car`, `Motorcycle`, `Bicycle`).
  - `hourIn`: Giờ vào bãi (Số nguyên từ `0` đến `23`).
  - `parkTime`: Thời gian đỗ xe tính theo giờ (Số nguyên từ `1` đến `23`).
  - `parkingFee`: Phí đỗ xe tính toán (Số thực).
  - `isParked`: Trạng thái đỗ xe (Đúng/Sai).
- **Phương thức (Public):**
  - Các hàm khởi tạo (Constructors), Getter/Setter.
  - `modifiedCarType()`: Chuẩn hóa chuỗi nhập loại xe thành dạng chuẩn: `Car`, `Motorcycle`, `Bicycle` hoặc `Unknown`.
  - `isValidCarTypeInput()`: Hàm tĩnh (static) kiểm tra tính hợp lệ của loại xe nhập vào.
  - `calculateParkingFee()`: Tính toán phí đỗ xe theo công tắc tính phí quy định.
  - `displayCarInfo()`: In thông tin chi tiết của xe.

#### 📏 Quy tắc tính phí đỗ xe (`calculateParkingFee`):
1. **Giá gốc mỗi giờ (Base Rate):**
   - Xe hơi (`Car`): 6.000 VND / giờ.
   - Xe máy (`Motorcycle`): 4.000 VND / giờ.
   - Xe đạp (`Bicycle`): 2.000 VND / giờ.
2. **Hệ số giờ đỗ:**
   - **Giờ cao điểm** (Khung giờ `6h - 9h` và `15h - 18h`): Đơn giá 2 giờ đầu tăng **30%** (+30% base rate).
   - **Giờ thấp điểm**: Đơn giá 2 giờ đầu giảm **5%** (-5% base rate).
   - **Từ giờ thứ 3 trở đi**: Áp dụng đơn giá giảm **10%** so với giá gốc (-10% base rate) cho toàn bộ số giờ vượt quá 2 giờ đầu.

---

### Lớp `ParkingLot` (Bãi đỗ xe)
Quản lý thông tin và tập hợp xe trong một bãi đỗ.
- **Thuộc tính (Private):**
  - `lotID`: Mã bãi đỗ xe.
  - `size`: Kích thước bãi đỗ (`S`, `M`, `L`).
  - Quản lý tối đa 3 xe (`car1`, `car2`, `car3`) và các biến cờ trạng thái (`hasCar1`, `hasCar2`, `hasCar3`).
- **Phương thức (Public):**
  - `getCapacity()`: Trả về sức chứa tối đa dựa theo `size` (`S` = 1 xe, `M` = 2 xe, `L` = 3 xe).
  - `addCar(const Car&)`: Thêm xe vào bãi (nếu bãi còn chỗ).
  - `findCar(int carID)`: Tìm kiếm xem xe có trong bãi hay không.
  - `removeCar(int carID)`: Xóa/lấy xe ra khỏi bãi theo mã ID.
  - `displayParkingLotInfo()`: In thông tin bãi đỗ và danh sách xe đang đỗ.
  - `listCarsByType(string type)`: Liệt kê các xe thuộc loại cụ thể.
  - `getFeeStatsByType(...)`: Tính tổng tiền và số lượng xe theo loại phục vụ báo cáo.

---

### Lớp `UI` (Giao diện người dùng)
Quản lý danh sách tối đa 3 bãi đỗ xe (`lot1`, `lot2`, `lot3`) và tương tác menu console với người dùng.
- Tự động kiểm tra trùng lặp `Lot ID` và `Car ID` trong toàn hệ thống.
- Kiểm tra tính hợp lệ của dữ liệu đầu vào (khung giờ, thời gian đỗ, loại xe, kích thước bãi).

---

## 3. Yêu cầu giao diện Menu tương tác

Chương trình cung cấp menu tương tác liên tục cho người dùng lựa chọn các chức năng:

```text
================ HE THONG QUAN LY BAI DO XE ================
1. Tao bai do xe moi
2. Them xe vao bai
3. Xoa bai do xe
4. Xoa xe khoi bai
5. Hien thi cac bai do xe
6. Hien thi xe trong bai cu the
7. Liet ke danh sach phuong tien theo tung loai xe
8. Hien thi phi do xe trung binh cua cac loai xe
9. Thoat
===========================================================
