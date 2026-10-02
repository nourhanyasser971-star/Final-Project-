#include <iostream>
#include <string>
using namespace std;

class Database
{
private:
    // TODO: connection object/handle (e.g. libpq PGconn*)
    bool connected;

public:
    // ---- Constructors ----
    Database();
    // TODO: ~Database(); // make sure to disconnect safely

    // ---- Connection Management ----
    // TODO: bool connect(const string& host, const string& dbname,
    //                    const string& user, const string& password, int port);
    // TODO: void disconnect();
    // TODO: bool isConnected() const;

    // ---- Generic Query Helpers ----
    // TODO: bool executeQuery(const string& sql);
    // TODO: /* ResultType */ selectQuery(const string& sql);

    // ---- Employee ----
    // TODO: bool insertEmployee(/* Employee params */);
    // TODO: bool validateLogin(const string& username, const string& password);

    // ---- Customer ----
    // TODO: bool insertCustomer(/* Customer params */);
    // TODO: bool updateCustomer(/* Customer params */);
    // TODO: bool deleteCustomer(int customerId);
    // TODO: /* list */ getAllCustomers();

    // ---- Vehicle ----
    // TODO: bool insertVehicle(/* Vehicle params */);
    // TODO: /* list */ getVehiclesByCustomer(int customerId);

    // ---- Zone / ParkingSlot ----
    // TODO: /* list */ getAllZones();
    // TODO: /* list */ getSlotsByZone(int zoneId);
    // TODO: bool updateSlotStatus(int slotId, int newStatus);

    // ---- Reservation ----
  // داخل تعريف الـ class Database في Database.cpp:

public:
    // ---- Reservation ----
    bool insertReservation(int customerId, int vehicleId, int slotId, const string& date, const string& startTime, const string& endTime)
    {
        // SQL الافتراضي:
        // string sql = "INSERT INTO reservation (customer_id, vehicle_id, slot_id, reserve_date, start_time, end_time, status) "
        //              "VALUES (" + to_string(customerId) + ", " + to_string(vehicleId) + ", " + to_string(slotId) + ", '" + date + "', '" + startTime + "', '" + endTime + "', 'Pending');";
        
        // return executeQuery(sql);
        return true; 
    }

    bool hasConflictingReservation(int slotId, const string& date, const string& startTime, const string& endTime)
    {
        // SQL الافتراضي للتحقق من تقاطع الأوقات لنفس الموقف (slot_id) وفي نفس اليوم (reserve_date)
        // string sql = "SELECT COUNT(*) FROM reservation WHERE slot_id = " + to_string(slotId) + 
        //              " AND reserve_date = '" + date + "'" +
        //              " AND status != 'Cancelled'" +
        //              " AND (start_time < '" + endTime + "' AND end_time > '" + startTime + "');";
        
        // int count = selectQueryCount(sql);
        // return count > 0;
        return false;
    }

    bool cancelReservation(int reservationId)
    {
        // SQL الافتراضي:
        // string sql = "UPDATE reservation SET status = 'Cancelled' WHERE reservation_id = " + to_string(reservationId) + ";";
        
        // return executeQuery(sql);
        return true;
    }
    // TODO: bool hasConflictingReservation(int slotId, const string& date,
    //                                      const string& startTime, const string& endTime);
    // TODO: bool cancelReservation(int reservationId);

    // ---- ParkingSession ----
    // TODO: bool insertSession(int reservationId, const string& checkInTime);
    // TODO: bool closeSession(int sessionId, const string& checkOutTime);

    // ---- Payment ----
    // TODO: bool insertPayment(int sessionId, double amount);
    // TODO: bool markPaymentAsPaid(int paymentId);
};
