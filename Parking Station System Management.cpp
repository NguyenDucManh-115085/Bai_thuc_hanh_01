#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cctype>

using namespace std;

//Lớp xe
class Car {
private:
    int carID;
    string carType;
    int hourIn;
    int parkTime; 
    double parkingFee;
    bool isParked;
public:
    Car(): carID(0), carType(""), hourIn(0), parkTime(0), parkingFee(0.0), isParked(false) {}
    Car(int ID, string type, int hour, int duration): carID(ID), carType(type), hourIn(hour), parkTime(duration), parkingFee(0.0), isParked(true) {
        this->carType = modifiedCarType();
        calculateParkingFee();    
    }
    //Nhận vào
    int getCarID() const {return carID;}
    string getCarType() const {return carType;}
    int getHourIn() const {return hourIn;}
    int getParkTime() const {return parkTime;}
    bool getIsParked() const { return isParked; }    
    double getParkingFee() const { return parkingFee; }    
    //Gán giá trị    
    void setCarID(int ID) {carID = ID;}    
    void setCarType(string type) {
        carType = type; 
        carType = modifiedCarType();}    
    void setHourIn(int hour) { hourIn = hour; }    
    void setParkTime(int time) {parkTime = time;}    
    void setParkingFee(double fee) {parkingFee = fee;} 
    void setIsParked(bool parked) {isParked = parked;}
    //Hàm chuẩn hóa loại xe
    string modifiedCarType() {
        string temp = carType;
        transform(temp.begin(), temp.end(), temp.begin(), ::tolower);        
        if (temp == "car"){
            return "Car";
        }

        if (temp == "motorcycle" || temp == "motorbike"){
            return "Motorcycle";
        } 

        if (temp == "bicycle"){ 
            return "Bicycle";
        }      
        else{
        return "Unknown";
        }
    }
    //Hàm xác định xe hợp lệ
    static bool isValidCarTypeInput(const string& type) {        
        string temp = type;        
        transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
        return (temp == "car" || temp == "motorcycle" || temp == "motorbike" || temp == "bicycle");}
    //Hàm tính phí gửi xe
    double calculateParkingFee() {
        if (!isParked) {            
            parkingFee = 0.0;            
            return 0.0;        
        }
        
        double baseRate = 0.0;
        if (carType == "Car") {
            baseRate = 6.0;
        }
        else if (carType == "Motorcycle") {
            baseRate = 4.0;
        }
        else if (carType == "Bicycle") {
            baseRate = 2.0;
        }
        
        // Khung giờ cao điểm: Sáng (6-9) & Chiều Tối (15-18)
        bool isPeakHour = (hourIn >= 6 && hourIn <= 9) || (hourIn >= 15 && hourIn <= 18);
        // Đơn giá 2 giờ đầu (+30% cao điểm / -5% thấp điểm)
        double rateFirst2Hours = isPeakHour ? baseRate * 1.30 : baseRate * 0.95;
        // Đơn giá từ giờ thứ 3 (-10%)
        double rateAfter2Hours = baseRate * 0.90;

        if (parkTime <= 2) {            
            parkingFee = parkTime * rateFirst2Hours;
        }
        else {            
            parkingFee = (2 * rateFirst2Hours) + ((parkTime - 2) * rateAfter2Hours);
        }
        return parkingFee;    
    }
    //Thông tin xe
    void displayCarInfo() const {
        if (!isParked) {
            return;
        }

        cout <<"Car ID: "<<carID<<endl;
        cout <<"Car Type: "<<carType <<endl;
        cout <<"Hour In: "<<hourIn<<endl;
        cout <<"Park Time: "<<parkTime<<endl;
        cout <<fixed<<setprecision(2)<<"Parking Fee: VND"<<parkingFee<<endl;
        cout <<"Is Parked: "<<(isParked ? "Yes" : "No")<<endl;
    }
};
//Lớp bãi đỗ xe
class ParkingLot {
    private:
        int lotID;    
        char size;    
        Car car1, car2, car3;    
        bool hasCar1, hasCar2, hasCar3;
    public:
        ParkingLot(): lotID(0), size(' '), hasCar1(false), hasCar2(false), hasCar3(false) {}
        ParkingLot(int lotID, char size): lotID(lotID), size(toupper(size)), hasCar1(false), hasCar2(false), hasCar3(false) {}

        int getLotID() const {
            return lotID; 
        }
        char getSize() const { 
            return size; 
        }
        int getCapacity() const {        
            if (size == 'S') {return 1;}        
            if (size == 'M') {return 2;}        
            if (size == 'L') {return 3;}        
            return 0;    
        } 
         int getNumCars() const {        
            int cnt = 0;        
            if (hasCar1) {cnt++;}        
            if (hasCar2) {cnt++;}        
            if (hasCar3) {cnt++;}        
            return cnt;    
        }
        //Thêm xe
        bool addCar(const Car& car) {
            int cap = getCapacity();

            if (getNumCars() >= cap) {return false;}

            if (!hasCar1 && cap >= 1) {            
                car1 = car;            
                hasCar1 = true;            
                return true;        
            }
            if (!hasCar2 && cap >= 2) {            
                car2 = car;            
                hasCar2 = true;            
                return true;        
            }
            if (!hasCar3 && cap >= 3) {            
                car3 = car;            
                hasCar3 = true;            
                return true;        
            }
            return false;
        }
        // Tìm xe
        bool findCar(int carID) const {
            if (hasCar1 && car1.getCarID() == carID) {return true;}
            if (hasCar2 && car2.getCarID() == carID) {return true;}
            if (hasCar3 && car3.getCarID() == carID) {return true;}
            return false;
        }
        //Xóa xe
        bool removeCar(int carID) {
            if (hasCar1 && car1.getCarID() == carID) {            
                hasCar1 = false;            
                return true;        
            }
            if (hasCar2 && car2.getCarID() == carID) {            
                hasCar2 = false;            
                return true;        
            }
            if (hasCar3 && car3.getCarID() == carID) {            
                hasCar3 = false;            
                return true;        
            }
            return false;
        }
        //Thông tin bãi đỗ xe
        void displayParkingLotInfo() const {
            cout <<"Parking Lot ID: "<<lotID<<endl;
            cout <<"Capacity: "<<getCapacity()<<endl;
            cout <<"Number of Cars: "<<getNumCars()<<endl;

            if (hasCar1) {cout << "Car 1:" << endl;            
            car1.displayCarInfo();cout << endl;}
            if (hasCar2) {cout << "Car 2:" << endl;            
            car2.displayCarInfo();cout << endl;}
            if (hasCar3) {cout << "Car 3:" << endl;            
            car3.displayCarInfo();cout << endl;}
        }
        // Liệt kê xe theo loại
        void listCarsByType(const string& type) const {
            if (hasCar1 && car1.getCarType() == type) {
                cout <<" [Lot "<<lotID<< "]";            
                car1.displayCarInfo();        
            }
            if (hasCar2 && car2.getCarType() == type) {
                cout <<" [Lot "<<lotID<< "]";            
                car2.displayCarInfo();        
            }
            if (hasCar3 && car3.getCarType() == type) {
                cout <<" [Lot "<<lotID<< "]";            
                car3.displayCarInfo();        
            }
        }
        //Báo cáo tóm tắt phí đỗ trung bình
        void getFeeStatsByType(const string& type, double& totalFee, int& count) const {
            if (hasCar1 && car1.getCarType() == type) {
                totalFee += car1.getParkingFee();            
                count++;        
            }
            if (hasCar2 && car2.getCarType() == type) {
                totalFee += car2.getParkingFee();            
                count++;        
            }
            if (hasCar3 && car3.getCarType() == type) {
                totalFee += car3.getParkingFee();            
                count++;        
            }
        }
};
//UI
class UI {
    private:    
    ParkingLot lot1, lot2, lot3;
    bool hasLot1, hasLot2, hasLot3;
    
    bool isCarInSystem(int carID) const {
        if (hasLot1 && lot1.findCar(carID)) {return true;}
        if (hasLot2 && lot2.findCar(carID)) {return true;}
        if (hasLot3 && lot3.findCar(carID)) {return true;}
        return false;
    }
    public:
    UI(): hasLot1(false), hasLot2(false), hasLot3(false) {}

    //1: Tạo bãi đỗ xe mới
    void createParkingLot() {
        if (hasLot1 && hasLot2 && hasLot3) {
            cout <<"Error: Maximum capacity of 3 parking lots reached!\n";            
            return;        
        }

        int id;        
        char size;

        cout <<"Enter Lot ID: ";
        cin >> id;
        if ((hasLot1 && lot1.getLotID() == id) || (hasLot2 && lot2.getLotID() == id) || (hasLot3 && lot3.getLotID() == id)) {
             cout <<"Error: Lot ID already exists!\n";
             return;
        }

        cout <<"Enter Lot Size (S/M/L): ";
        cin >> size;
        size = toupper(size);
        if (size != 'S' && size != 'M' && size != 'L') {
            cout <<"Error: Invalid lot size!\n";
            return;
        }
        
        if (!hasLot1) {lot1 = ParkingLot(id, size);            
            hasLot1 = true;
        }
        else if (!hasLot2) {lot2 = ParkingLot(id, size);            
            hasLot2 = true;
        }
        else if (!hasLot3) {lot3 = ParkingLot(id, size);            
            hasLot3 = true;
        }

        cout <<"Parking Lot created successfully!\n";
    }
    //2: Thêm xe vào bãi đỗ
    void addCarToLot() {
        if (!hasLot1 && !hasLot2 && !hasLot3) {
            cout <<"Error: No parking lots available in the system!\n";
            return;
        }

        int id, hour, duration;
        string type;

        cout <<"Enter Car ID: ";
        cin >> id;
        if (isCarInSystem(id)) {
            cout <<"Error: Car ID already exists in the system!\n";
            return;
        }

        cout <<"Enter Vehicle Type (Car / Motorcycle / Bicycle): ";
        cin >> type;
        if (!Car::isValidCarTypeInput(type)) {
            cout <<"Error: Invalid vehicle type!\n";
            return;
        }

        cout << "Enter Entry Hour (0 - 23): ";
        cin >> hour;
        if (hour < 0 || hour > 23) {
            cout <<"Error: Entry hour must be between 0 and 23!\n";
            return;
        }

        cout << "Enter Parking Duration (1 - 23): ";
        cin >> duration;
        if (duration < 1 || duration > 23) { 
            cout <<"Error: Parking duration must be between 1 and 23!\n";
            return;
        }

        Car car(id, type, hour, duration);
        if (hasLot1 && lot1.addCar(car)) {
            cout <<"Added car to Lot ID "<<lot1.getLotID()<<endl;
            return;
        }
        if (hasLot2 && lot2.addCar(car)) {
            cout <<"Added car to Lot ID "<<lot2.getLotID()<<endl;
            return;
        }
        if (hasLot3 && lot3.addCar(car)) {
            cout <<"Added car to Lot ID "<<lot3.getLotID()<<endl;
            return;
        }
        else {
            cout <<"Error: All available parking lots are full!\n";    
        }
    }
    //3: Xóa bãi đỗ xe
    void removeParkingLot() {
        int id;
        cout <<"Enter Lot ID to remove: ";
        cin >> id;

        if (hasLot1 && lot1.getLotID() == id) {
        hasLot1 = false;           
        lot1 = ParkingLot();            
        cout <<"Removed Lot ID "<<id<<endl;           
        return;        
        }
        if (hasLot2 && lot2.getLotID() == id) {
        hasLot2 = false;           
        lot2 = ParkingLot();            
        cout <<"Removed Lot ID "<<id<<endl;           
        return;        
        }
        if (hasLot3 && lot3.getLotID() == id) {
        hasLot3 = false;           
        lot3 = ParkingLot();            
        cout <<"Removed Lot ID "<<id<<endl;           
        return;        
        }
        else {
            cout <<"Error: Lot ID not found!\n";
        }
    }
    //4: Lấy xe ra khỏi bãi
    void removeCarFromLot() {
        int id;
        cout <<"Enter Car ID to remove: "; 
        cin >> id;

        if (hasLot1 && lot1.removeCar(id)) {
            cout <<"Removed Car ID "<<id<<" from Lot "<<lot1.getLotID()<<endl;
            return;        
        }
        if (hasLot2 && lot2.removeCar(id)) {
            cout <<"Removed Car ID "<<id<<" from Lot "<<lot2.getLotID()<<endl;
            return;        
        }
        if (hasLot3 && lot3.removeCar(id)) {
            cout <<"Removed Car ID "<<id<<" from Lot "<<lot3.getLotID()<<endl;
            return;        
        }
        else {
            cout <<"Error: Car ID not found!\n";
        }
    }
    //5: Hiển thị danh sách tất cả các bãi đỗ
    void displayAllLots() {
        if (!hasLot1 && !hasLot2 && !hasLot3) {
            cout <<"System has no parking lots!\n";
            return;        
        }

        cout <<"\n=== PARKING LOT LIST ===\n";
        if (hasLot1) {lot1.displayParkingLotInfo();}
        if (hasLot2) {lot2.displayParkingLotInfo();}
        if (hasLot3) {lot3.displayParkingLotInfo();}
    }
    //6: Hiển thị danh sách xe theo bãi cụ thể
    void displayCarsInLot() {
        int id;
        cout <<"Enter Lot ID to view: ";
        cin >> id;

        if (hasLot1 && lot1.getLotID() == id) { 
            lot1.displayParkingLotInfo();
            return;        
        }
        if (hasLot2 && lot2.getLotID() == id) { 
            lot2.displayParkingLotInfo();
            return;        
        }
        if (hasLot3 && lot3.getLotID() == id) { 
            lot3.displayParkingLotInfo();
            return;        
        }
        else {
            cout <<"Error: Lot ID not found!\n";
        }
    }
    //7: Liệt kê xe theo loại
    void listCarsByType() {
        string type;
        cout <<"Enter Vehicle Type (Car / Motorcycle / Bicycle): ";
        cin >> type;

        if (!Car::isValidCarTypeInput(type)) {
            cout <<"Error: Invalid vehicle type!\n";
            return;
        }

        Car temp(0, type, 0, 0);
        string normalizedType = temp.getCarType();
        cout <<"\n=== LIST OF VEHICLES (TYPE: "<< normalizedType<< ") ===\n";

        if (hasLot1) {lot1.listCarsByType(normalizedType);}
        if (hasLot2) {lot2.listCarsByType(normalizedType);}
        if (hasLot3) {lot3.listCarsByType(normalizedType);}
    }
    //8: Báo cáo tóm tắt phí đỗ trung bình
    void displayAverageFeeReport() { 
        string types[3] = {"Car", "Motorcycle", "Bicycle"};
        cout <<"\n=== AVERAGE PARKING FEE REPORT ===\n";
        for (int i = 0; i < 3; ++i) {
            double totalFee = 0.0;
            int count = 0;

            if (hasLot1) {lot1.getFeeStatsByType(types[i], totalFee, count);}
            if (hasLot2) {lot2.getFeeStatsByType(types[i], totalFee, count);}
            if (hasLot3) {lot3.getFeeStatsByType(types[i], totalFee, count);}

            cout <<"Type: "<< types[i]<<" | Count: "<< count;
            if (count > 0) {
                cout <<" | Avg Fee: VND "<<fixed<<setprecision(2)<<(totalFee / count)<<endl;
            }
            else {
                cout <<" | Avg Fee: 0.0 VND"<<endl;
            }
        }
    }
    //Menu
    void runMenu() {
        int choice = 0;
        do {
        cout <<"\n================ PARKING MANAGEMENT SYSTEM ================\n";
        cout <<"1. Create New Parking Lot\n";            
        cout <<"2. Add Car to Lot\n";            
        cout <<"3. Remove a Parking Lot\n";            
        cout <<"4. Remove Car from Lot\n";            
        cout <<"5. Display All Parking Lots\n";            
        cout <<"6. Display Cars in Specific Lot\n";
        cout <<"7. List Vehicles by Type\n";            
        cout <<"8. View Average Parking Fee Report\n";
        cout <<"9. Exit\n";            
        cout <<"Enter your choice (1-9): ";
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout <<"Invalid input! Please enter a number between 1 and 9.\n";
            continue;
        }
        switch (choice) {
            case 1: createParkingLot();
            break;
            case 2: addCarToLot();
            break;
            case 3: removeParkingLot();
            break;
            case 4: removeCarFromLot();
            break;
            case 5: displayAllLots();
            break;
            case 6: displayCarsInLot();
            break;
            case 7: listCarsByType();
            break;
            case 8: displayAverageFeeReport();
            break;
            case 9: 
            cout <<"Exiting the system. Goodbye!\n";
            break;
            default: 
            cout <<"Invalid choice! Please try again!\n";
            break;
        }
    } while (choice != 9);
    }
};
//Main
int main() {
    UI ui;
    ui.runMenu();
    return 0;
}