#include <iostream>
#include <string>
#include <vector>
using namespace std;

// =====================================================
// Employee
// =====================================================
class Employee
{
private:
    int id;
    string username;
    string password;
    string name;

public:
    // ---- Constructors ----
    Employee();
    // TODO: Employee(int id, string username, string password, string name);

    // ---- Getters / Setters ----
    // TODO: int getId() const;
    // TODO: string getUsername() const;
    // TODO: void setName(const string& name);

    // ---- Behavior ----
    // TODO: bool login(const string& username, const string& password);
};


// =====================================================
// Customer
// =====================================================
class Customer
{
private:
    int id;
    string name;
    string phone;
    string email;

public:
    // ---- Constructors ----
    Customer();
    // TODO: Customer(int id, string name, string phone, string email);

    // ---- Getters / Setters ----
    // TODO: int getId() const;
    // TODO: string getName() const;
    // TODO: void setPhone(const string& phone);

    // ---- Behavior ----
    // TODO: bool save();      // insert/update in DB via Database class
    // TODO: bool remove();    // delete from DB
};

// ---------------------------------------------------------------------
// Vehicle (Abstract Base Class)
// ---------------------------------------------------------------------
class Vehicle
{
protected:
    int id;
    int customerId;
    string plateNumber;
    string model;

public:
    Vehicle() : id(0), customerId(0), plateNumber(""), model("") {}

    Vehicle(int id, int customerId, string plateNumber, string model)
        : id(id), customerId(customerId),
          plateNumber(plateNumber), model(model) {}

    virtual ~Vehicle() {}

    // ---- Getters / Setters ----
    int getId() const { return id; }
    int getCustomerId() const { return customerId; }
    string getPlateNumber() const { return plateNumber; }
    string getModel() const { return model; }
    void setId(int newId) { id = newId; }

    // ---- Pure Virtual (Polymorphism) ----
    virtual string getVehicleType() const = 0;
    virtual void displayInfo() const = 0;

    virtual int getExtraAttribute() const = 0;
};

// ---------------------------------------------------------------------
// Car
// ---------------------------------------------------------------------
class Car : public Vehicle
{
private:
    int numberOfDoors;

public:
    Car() : Vehicle(), numberOfDoors(4) {}

    Car(int id, int customerId, string plateNumber, string model, int numberOfDoors)
        : Vehicle(id, customerId, plateNumber, model),
          numberOfDoors(numberOfDoors) {}

    string getVehicleType() const override { return "Car"; }

    int getExtraAttribute() const override { return numberOfDoors; }

    void displayInfo() const override
    {
        cout << "[Car] ID: " << id
             << " | Plate: " << plateNumber
             << " | Model: " << model
             << " | Doors: " << numberOfDoors << endl;
    }
};

// ---------------------------------------------------------------------
// Motorcycle
// ---------------------------------------------------------------------
class Motorcycle : public Vehicle
{
private:
    int engineCC;

public:
    Motorcycle() : Vehicle(), engineCC(0) {}

    Motorcycle(int id, int customerId, string plateNumber, string model, int engineCC)
        : Vehicle(id, customerId, plateNumber, model),
          engineCC(engineCC) {}

    string getVehicleType() const override { return "Motorcycle"; }

    int getExtraAttribute() const override { return engineCC; }

    void displayInfo() const override
    {
        cout << "[Motorcycle] ID: " << id
             << " | Plate: " << plateNumber
             << " | Model: " << model
             << " | Engine: " << engineCC << "cc" << endl;
    }
};

// ---------------------------------------------------------------------
// Factory: بتبني الكائن الصحيح من صف الداتابيز.
// نوع جديد (مثلاً Truck) = تضيف سطر هنا بس، والباقي ما يتغيرش.
// ---------------------------------------------------------------------
inline Vehicle* createVehicle(const string& type, int id, int customerId,
                              const string& plate, const string& model, int extra)
{
    if (type == "Car")        return new Car(id, customerId, plate, model, extra);
    if (type == "Motorcycle") return new Motorcycle(id, customerId, plate, model, extra);
    return nullptr;
}


// =====================================================================
// الجزء الثاني: انسخه داخل class Database في Database.cpp
// (يحتاج #include <vector> و <memory>)
// =====================================================================
//
// جدول الداتابيز المقترح:
//
// CREATE TABLE vehicle (
//     vehicle_id    SERIAL PRIMARY KEY,
//     customer_id   INT NOT NULL REFERENCES customer(customer_id),
//     plate_number  VARCHAR(20) NOT NULL UNIQUE,
//     model         VARCHAR(50),
//     vehicle_type  VARCHAR(20) NOT NULL,   -- 'Car' / 'Motorcycle'
//     extra_value   INT                      -- doors or engine cc
// );
//
// الدوال دي بتفترض وجود الـ helpers التالية في Database (من M1):
//   bool executeQuery(const string& sql);
//   vector<vector<string>> selectQuery(const string& sql);   // كل صف = vector من النصوص
//
// ملاحظة أمان: الأفضل في الآخر تستخدم PQexecParams (prepared statements)
// بدل دمج النصوص، escapeSql هنا حل مؤقت ضد الـ SQL injection.

    // ---- Helper: تهريب علامة ' ----
    static string escapeSql(const string& s)
    {
        string out;
        for (char c : s)
        {
            if (c == '\'') out += "''";
            else out += c;
        }
        return out;
    }

    // ---- Edge case: customer_id غير موجود ----
    bool customerExists(int customerId)
    {
        string sql = "SELECT COUNT(*) FROM customer WHERE customer_id = "
                     + to_string(customerId) + ";";
        auto rows = selectQuery(sql);
        return !rows.empty() && stoi(rows[0][0]) > 0;
    }

    // ---- Edge case: plate number مكرر ----
    bool plateExists(const string& plate)
    {
        string sql = "SELECT COUNT(*) FROM vehicle WHERE plate_number = '"
                     + escapeSql(plate) + "';";
        auto rows = selectQuery(sql);
        return !rows.empty() && stoi(rows[0][0]) > 0;
    }

    // ---- insertVehicle ----
    // بتاخد Vehicle& (polymorphism): تشتغل مع Car و Motorcycle وأي نوع جديد.
    bool insertVehicle(const Vehicle& v)
    {
        if (!connected) return false;

        if (v.getPlateNumber().empty())
        {
            cout << "Error: plate number is empty." << endl;
            return false;
        }
        if (!customerExists(v.getCustomerId()))
        {
            cout << "Error: customer " << v.getCustomerId() << " does not exist." << endl;
            return false;
        }
        if (plateExists(v.getPlateNumber()))
        {
            cout << "Error: plate number already registered." << endl;
            return false;
        }

        string sql =
            "INSERT INTO vehicle (customer_id, plate_number, model, vehicle_type, extra_value) VALUES ("
            + to_string(v.getCustomerId()) + ", '"
            + escapeSql(v.getPlateNumber()) + "', '"
            + escapeSql(v.getModel()) + "', '"
            + escapeSql(v.getVehicleType()) + "', "
            + to_string(v.getExtraAttribute()) + ");";

        return executeQuery(sql);
    }

    // ---- getVehiclesByCustomer ----
    // بترجع vector<unique_ptr<Vehicle>> => الذاكرة تتحرر لوحدها
    vector<unique_ptr<Vehicle>> getVehiclesByCustomer(int customerId)
    {
        vector<unique_ptr<Vehicle>> result;
        if (!connected) return result;

        string sql =
            "SELECT vehicle_id, customer_id, plate_number, model, vehicle_type, extra_value "
            "FROM vehicle WHERE customer_id = " + to_string(customerId)
            + " ORDER BY vehicle_id;";

        for (const auto& row : selectQuery(sql))
        {
            Vehicle* v = createVehicle(row[4],               // type
                                       stoi(row[0]),         // id
                                       stoi(row[1]),         // customer_id
                                       row[2],               // plate
                                       row[3],               // model
                                       stoi(row[5]));        // extra
            if (v) result.emplace_back(v);
        }
        return result;
    }

// =====================================================================
// مثال اختبار (في main مؤقتاً)
// =====================================================================
//
// // Vehicle v;                          // ❌ compile error: abstract
// vector<unique_ptr<Vehicle>> list;
// list.push_back(make_unique<Car>(1, 1, "ABC-123", "Toyota", 4));
// list.push_back(make_unique<Motorcycle>(2, 1, "XYZ-789", "Yamaha", 250));
// for (auto& v : list) v->displayInfo();   // output مختلف لكل نوع
// db.insertVehicle(*list[0]);
// auto vehicles = db.getVehiclesByCustomer(1);
// =====================================================
// Zone
// =====================================================
class Zone
{
private:
    int id;
    string name;

public:
    // ---- Constructors ----
    Zone()
    {
        id = 0;
        name = "";
    }
    // TODO: Zone(int id, string name);
    Zone(int id, string name)
    {
        this->id = id;
        this->name = name;
    }
    // ---- Getters / Setters ----
    // TODO: int getId() const;
    int getId() const
    {
        return id;
    }
    // TODO: string getName() const;
    string getName() const
    {
        return name;
    }
};


// =====================================================
// ParkingSlot
// =====================================================
enum class SlotStatus
{
    Available,
    Reserved,
    Occupied
};

class ParkingSlot
{
private:
    int id;
    int zoneId;
    string slotCode; // e.g. A01
    SlotStatus status;

public:
    // ---- Constructors ----
    ParkingSlot()
    {
        id = 0;
        zoneId = 0;
        slotCode = "";
    }
    ParkingSlot(int id, int zoneId, string slotCode)
    {
        this->id = id;
        this->zoneId = zoneId;
        this->slotCode = slotCode;
    }

    // ---- Getters / Setters ----
    SlotStatus getStatus() const
    {
        return status;
    }
    void setStatus(SlotStatus newStatus)
    {
        status = newStatus ;
    }

    // ---- Behavior ----
     bool isAvailable() const
     {
         if(status == SlotStatus::Available)
           return true;
         else
            return false;
     }
};


// =====================================================
// PricingStrategy (Abstract) - Strategy Pattern
// =====================================================
class PricingStrategy
{
public:
    virtual ~PricingStrategy() {}
    // TODO: virtual double calculatePrice(int durationMinutes) const = 0;
};


// =====================================================
// NormalPricing
// =====================================================
class NormalPricing : public PricingStrategy
{
public:
    // TODO: double calculatePrice(int durationMinutes) const override;
};


// =====================================================
// VipPricing
// =====================================================
class VipPricing : public PricingStrategy
{
public:
    // TODO: double calculatePrice(int durationMinutes) const override;
};


// =====================================================
// Reservation
// =====================================================
// =====================================================
// Reservation
// =====================================================
enum class ReservationStatus
{
    Pending,
    Confirmed,
    Cancelled
};

class Reservation
{
private:
    int id;
    int customerId;
    int vehicleId;
    int slotId;
    string date;
    string startTime;
    string endTime;
    ReservationStatus status;

public:
    // ---- Constructors ----
    Reservation()
    {
        id = 0;
        customerId = 0;
        vehicleId = 0;
        slotId = 0;
        date = "";
        startTime = "";
        endTime = "";
        status = ReservationStatus::Pending;
    }

    Reservation(int customerId, int vehicleId, int slotId, string date, string startTime, string endTime)
    {
        this->id = 0;
        this->customerId = customerId;
        this->vehicleId = vehicleId;
        this->slotId = slotId;
        this->date = date;
        this->startTime = startTime;
        this->endTime = endTime;
        this->status = ReservationStatus::Pending;
    }

    // ---- Getters / Setters ----
    int getId() const
    {
        return id;
    }

    ReservationStatus getStatus() const
    {
        return status;
    }


    bool hasConflict() const
    {


        return false;
    }

    bool save()
  {
        return true;
    }

    bool cancel()
    {
        this->status = ReservationStatus::Cancelled;


        return true;
    }
};

// =====================================================
// ParkingSession
// =====================================================
class ParkingSession
{
private:
    int id;
    int reservationId;
    string checkInTime;
    string checkOutTime;
    bool isActive;

public:
    // ---- Constructors ----
    ParkingSession();
    // TODO: ParkingSession(int reservationId);

    // ---- Behavior ----
    // TODO: void checkIn();
    // TODO: void checkOut();
    // TODO: int getDurationMinutes() const;
};


// =====================================================
// Payment
// =====================================================
enum class PaymentStatus
{
    Pending,
    Paid
};

class Payment
{
private:
    int id;
    int sessionId;
    double amount;
    PaymentStatus status;

public:
    // ---- Constructors ----
    Payment();
    // TODO: Payment(int sessionId, double amount);

    // ---- Behavior ----
    // TODO: bool processPayment();
    // TODO: double calculateAmount(const ParkingSession& session, const PricingStrategy& strategy);
};


// =====================================================
// MAIN
// =====================================================
int main()
{
    // TODO: Initialize Database connection

    // TODO: Initialize GUI (ImGui window + main loop)

    // TODO: Show Login Screen first, then Dashboard after successful login

    cout << "Parking Management System - Starting..." << endl;

    return 0;
}
