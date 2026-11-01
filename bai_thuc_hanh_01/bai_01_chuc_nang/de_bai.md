# ĐỀ BÀI THỰC HÀNH 01: HỆ THỐNG QUẢN LÝ BÃI ĐỖ XE

## 1. Yêu cầu chung
Xây dựng một chương trình quản lý bãi đỗ xe bằng ngôn ngữ C++ áp dụng các nguyên lý của **Lập trình hướng đối tượng (OOP)**[cite: 1]. Chương trình cần quản lý các phương tiện ra/vào bãi, tự động tính phí gửi xe dựa trên loại xe, khung giờ cao điểm, thời gian gửi và hỗ trợ xuất báo cáo thống kê[cite: 1].

---

## 2. Mô tả các lớp đối tượng (Class Design)

### Lớp `Car` (Xe / Phương tiện gửi)
Quản lý thông tin chi tiết về từng xe gửi trong bãi[cite: 1].
- **Thuộc tính (Private):**
  - `carID`: Mã định danh của xe (Số nguyên)[cite: 1].
  - `carType`: Loại xe (`Car`, `Motorcycle`, `Bicycle`)[cite: 1].
  - `hourIn`: Giờ vào bãi (Số nguyên từ `0` đến `23`)[cite: 1].
  - `parkTime`: Thời gian đỗ xe tính theo giờ (Số nguyên từ `1` đến `23`)[cite: 1].
  - `parkingFee`: Phí đỗ xe tính toán (Số thực)[cite: 1].
  - `isParked`: Trạng thái đỗ xe (Đúng/Sai)[cite: 1].
- **Phương thức (Public):**
  - Các hàm khởi tạo (Constructors), Getter/Setter[cite: 1].
  - `modifiedCarType()`: Chuẩn hóa chuỗi nhập loại xe thành dạng chuẩn: `Car`, `Motorcycle`, `Bicycle` hoặc `Unknown`[cite: 1].
  - `isValidCarTypeInput()`: Hàm tĩnh (static) kiểm tra tính hợp lệ của loại xe nhập vào[cite: 1].
  - `calculateParkingFee()`: Tính toán phí đỗ xe theo công tắc tính phí quy định[cite: 1].
  - `displayCarInfo()`: In thông tin chi tiết của xe[cite: 1].

#### 📏 Quy tắc tính phí đỗ xe (`calculateParkingFee`):
1. **Giá gốc mỗi giờ (Base Rate):**
   - Xe hơi (`Car`): 6.000 VND / giờ[cite: 1].
   - Xe máy (`Motorcycle`): 4.000 VND / giờ[cite: 1].
   - Xe đạp (`Bicycle`): 2.000 VND / giờ[cite: 1].
2. **Hệ số giờ đỗ:**
   - **Giờ cao điểm** (Khung giờ `6h - 9h` và `15h - 18h`): Đơn giá 2 giờ đầu tăng **30%** (+30% base rate)[cite: 1].
   - **Giờ thấp điểm**: Đơn giá 2 giờ đầu giảm **5%** (-5% base rate)[cite: 1].
   - **Từ giờ thứ 3 trở đi**: Áp dụng đơn giá giảm **10%** so với giá gốc (-10% base rate) cho toàn bộ số giờ vượt quá 2 giờ đầu[cite: 1].

---

### Lớp `ParkingLot` (Bãi đỗ xe)
Quản lý thông tin và tập hợp xe trong một bãi đỗ[cite: 1].
- **Thuộc tính (Private):**
  - `lotID`: Mã bãi đỗ xe[cite: 1].
  - `size`: Kích thước bãi đỗ (`S`, `M`, `L`)[cite: 1].
  - Quản lý tối đa 3 xe (`car1`, `car2`, `car3`) và các biến cờ trạng thái (`hasCar1`, `hasCar2`, `hasCar3`)[cite: 1].
- **Phương thức (Public):**
  - `getCapacity()`: Trả về sức chứa tối đa dựa theo `size` (`S` = 1 xe, `M` = 2 xe, `L` = 3 xe)[cite: 1].
  - `addCar(const Car&)`: Thêm xe vào bãi (nếu bãi còn chỗ)[cite: 1].
  - `findCar(int carID)`: Tìm kiếm xem xe có trong bãi hay không[cite: 1].
  - `removeCar(int carID)`: Xóa/lấy xe ra khỏi bãi theo mã ID[cite: 1].
  - `displayParkingLotInfo()`: In thông tin bãi đỗ và danh sách xe đang đỗ[cite: 1].
  - `listCarsByType(string type)`: Liệt kê các xe thuộc loại cụ thể[cite: 1].
  - `getFeeStatsByType(...)`: Tính tổng tiền và số lượng xe theo loại phục vụ báo cáo[cite: 1].

---

### Lớp `UI` (Giao diện người dùng)
Quản lý danh sách tối đa 3 bãi đỗ xe (`lot1`, `lot2`, `lot3`) và tương tác menu console với người dùng[cite: 1].
- Tự động kiểm tra trùng lặp `Lot ID` và `Car ID` trong toàn hệ thống[cite: 1].
- Kiểm tra tính hợp lệ của dữ liệu đầu vào (khung giờ, thời gian đỗ, loại xe, kích thước bãi)[cite: 1].

---

## 3. Yêu cầu giao diện Menu tương tác

Chương trình cung cấp menu tương tác liên tục cho người dùng lựa chọn các chức năng[cite: 1]:

```text
================ PARKING MANAGEMENT SYSTEM ================
1. Create New Parking Lot           (Tạo bãi đỗ xe mới)
2. Add Car to Lot                  (Thêm xe vào bãi đỗ)
3. Remove a Parking Lot            (Xóa một bãi đỗ xe)
4. Remove Car from Lot             (Lấy xe ra khỏi bãi)
5. Display All Parking Lots        (Hiển thị danh sách tất cả các bãi)
6. Display Cars in Specific Lot    (Hiển thị danh sách xe trong 1 bãi cụ thể)
7. List Vehicles by Type           (Liệt kê danh sách xe theo loại)
8. View Average Parking Fee Report (Xem báo cáo chi phí trung bình theo loại xe)
9. Exit                            (Thoát chương trình)
===========================================================