#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cmath>
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
    virtual double calculatePrice(int durationMinutes) const = 0;
};


// =====================================================
// NormalPricing
// =====================================================
class NormalPricing : public PricingStrategy
{
public:
    double calculatePrice(int durationMinutes) const override
    {
        int hours = ceil(durationMinutes / 60.0);
        return hours * 10;
    }
};


// =====================================================
// VipPricing
// =====================================================
class VipPricing : public PricingStrategy
{
public:
    double calculatePrice(int durationMinutes) const override
    {
        int hours = ceil(durationMinutes / 60.0);
        return hours * 20;
    }
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
    time_t checkInTime;
    time_t checkOutTime;
    bool isActive;

    // The database functions take the time as a string
    string toText(time_t t)
    {
        char buf[20];
        strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&t));
        return buf;
    }

public:
    ParkingSession()
    {
        id = 0;
        reservationId = 0;
        checkInTime = 0;
        checkOutTime = 0;
        isActive = false;
    }
    ParkingSession(int reservationId)
    {
        id = 0;
        this->reservationId = reservationId;
        checkInTime = 0;
        checkOutTime = 0;
        isActive = false;
    }

    int getId() const { return id; }

    void checkIn(Database& db)
    {
        if (isActive)
        {
            cout << "Already checked in." << endl;
            return;
        }
        time_t now = time(0);
        if (db.insertSession(reservationId, toText(now), &id))
        {
            checkInTime = now;
            isActive = true;
        }
    }

    void checkOut(Database& db)
    {
        if (!isActive)
        {
            cout << "Error: no check-in found." << endl;
            return;
        }
        time_t now = time(0);
        if (now < checkInTime)
        {
            cout << "Error: negative duration." << endl;
            return;
        }
        if (db.closeSession(id, toText(now)))
        {
            checkOutTime = now;
            isActive = false;
        }
    }

    int getDurationMinutes() const
    {
        if (checkInTime == 0)
            return -1;
        time_t end = isActive ? time(0) : checkOutTime;
        return ceil(difftime(end, checkInTime) / 60.0);
    }
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
    Payment()
    {
        id = 0;
        sessionId = 0;
        amount = 0;
        status = PaymentStatus::Pending;
    }
    Payment(int sessionId, double amount)
    {
        id = 0;
        this->sessionId = sessionId;
        this->amount = amount;
        status = PaymentStatus::Pending;
    }

    double calculateAmount(const ParkingSession& session, const PricingStrategy& strategy)
    {
        int minutes = session.getDurationMinutes();
        if (minutes < 0)
            return 0;
        amount = strategy.calculatePrice(minutes);
        return amount;
    }

    bool processPayment(Database& db)
    {
        if (!db.insertPayment(sessionId, amount, &id))
            return false;
        if (!db.markPaymentAsPaid(id))
            return false;
        status = PaymentStatus::Paid;
        return true;
    }
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
