#include <iostream>
#include <string>
using namespace std;

class Employee
{
private:
    int id;
    string username;
    string password;
    string name;

public:
    // Default Constructor
    Employee()
    {
        id = 0;
        username = "";
        password = "";
        name = "";
    }

    // Parameterized Constructor
    Employee(int id, string username, string password, string name)
    {
        this->id = id;
        this->username = username;
        this->password = password;
        this->name = name;
    }

    // Getter for ID
    int getId() const
    {
        return id;
    }

    // Getter for Username
    string getUsername() const
    {
        return username;
    }

    // Setter for Name
    void setName(const string& name)
    {
        this->name = name;
    }

    // Login Function
    bool login(const string& username, const string& password)
    {
        return (this->username == username &&
                this->password == password);
    }
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


// =====================================================
// Vehicle (Abstract Base Class)
// =====================================================
class Vehicle
{
protected:
    int id;
    int customerId;
    string plateNumber;
    string model;

public:
    // ---- Constructors ----
    Vehicle();
    // TODO: Vehicle(int id, int customerId, string plateNumber, string model);
    virtual ~Vehicle() {}

    // ---- Getters / Setters ----
    // TODO: int getId() const;
    // TODO: string getPlateNumber() const;

    // ---- Pure Virtual (Polymorphism) ----
    virtual string getVehicleType() const = 0;
    virtual void displayInfo() const = 0;
};


// =====================================================
// Car (inherits Vehicle)
// =====================================================
class Car : public Vehicle
{
private:
    int numberOfDoors;

public:
    // ---- Constructors ----
    Car();
    // TODO: Car(int id, int customerId, string plateNumber, string model, int numberOfDoors);

    // ---- Overrides ----
    // TODO: string getVehicleType() const override;
    // TODO: void displayInfo() const override;
};


// =====================================================
// Motorcycle (inherits Vehicle)
// =====================================================
class Motorcycle : public Vehicle
{
private:
    int engineCC;

public:
    // ---- Constructors ----
    Motorcycle();
    // TODO: Motorcycle(int id, int customerId, string plateNumber, string model, int engineCC);

    // ---- Overrides ----
    // TODO: string getVehicleType() const override;
    // TODO: void displayInfo() const override;
};


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
    Reservation();
    // TODO: Reservation(int customerId, int vehicleId, int slotId, string date, string startTime, string endTime);

    // ---- Getters / Setters ----
    // TODO: int getId() const;
    // TODO: ReservationStatus getStatus() const;

    // ---- Behavior ----
    // TODO: bool hasConflict() const;   // check overlapping reservations
    // TODO: bool save();
    // TODO: bool cancel();
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
