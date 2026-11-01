## 📌 Tính Năng Chính

- **Quản lý bãi đỗ xe:** Tạo mới bãi đỗ với các kích thước (S - 1 xe, M - 2 xe, L - 3 xe) và xóa bãi đỗ[cite: 1].
- **Quản lý xe gửi:** Thêm xe mới vào bãi tự động, kiểm tra trùng mã ID, lấy xe ra khỏi bãi[cite: 1].
- **Phân loại phương tiện:** Hỗ trợ chuẩn hóa và phân loại các loại xe (`Car`, `Motorcycle`, `Bicycle`)[cite: 1].
- **Tính phí gửi xe linh hoạt:**
  - Tự động điều chỉnh mức giá theo giờ cao điểm (6h-9h & 15h-18h: +30%, giờ thấp điểm: -5%)[cite: 1].
  - Giảm 10% đơn giá áp dụng cho từ giờ thứ 3 trở đi[cite: 1].
- **Báo cáo & Thống kê:** Hiển thị danh sách bãi đỗ, lọc phương tiện theo loại và tính chi phí trung bình theo loại xe[cite: 1].

---

## 🏗 Kiến Trúc Lớp (Class Architecture)

Chương trình được thiết kế theo các lớp OOP cơ bản[cite: 1]:

1. **`Car`**: Quản lý thông tin từng phương tiện (ID, loại xe, giờ vào, thời gian gửi, phí gửi xe)[cite: 1].
2. **`ParkingLot`**: Quản lý tập hợp xe trong một bãi đỗ cụ thể, hỗ trợ các thao tác thêm/xóa/tìm kiếm xe[cite: 1].
3. **`UI`**: Quản lý giao diện menu tương tác người dùng, điều phối hoạt động giữa các bãi đỗ xe[cite: 1].

---

## 🚀 Hướng Dẫn Biên Dịch Và Chạy

### Yêu cầu môi trường
- Trình biên dịch C++ hỗ trợ **C++11** trở lên (g++, clang++, MSVC)[cite: 1].

### Các bước thực hiện

1. **Biên dịch mã nguồn:**
   ```bash
   g++ -std=c++11 Bai_thuc_hanh_01.cpp -o parking_app