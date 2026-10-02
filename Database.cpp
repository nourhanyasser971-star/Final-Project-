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

bool Database::insertCustomer(const string& name, const string& phone, const string& email) {
    string query = "INSERT INTO customer (name, phone, email) VALUES ('" +
                   name + "', '" + phone + "', '" + email + "');";
    return executeQuery(query);
}

bool Database::updateCustomer(int customerId, const string& name, const string& phone, const string& email) {
    string query = "UPDATE customer SET name = '" + name +
                   "', phone = '" + phone +
                   "', email = '" + email +
                   "' WHERE customer_id = " + to_string(customerId) + ";";
    return executeQuery(query);
}

bool Database::deleteCustomer(int customerId) {
    string query = "DELETE FROM customer WHERE customer_id = " + to_string(customerId) + ";";
    return executeQuery(query);
}
vector<Customer> Database::getAllCustomers() {
    vector<Customer> customersList;
    string query = "SELECT customer_id, name, phone, email FROM customer;";

    return customersList;
}

    // ---- Vehicle ----
    // TODO: bool insertVehicle(/* Vehicle params */);
    // TODO: /* list */ getVehiclesByCustomer(int customerId);

    // ---- Zone / ParkingSlot ----
    // TODO: /* list */ getAllZones();
    // TODO: /* list */ getSlotsByZone(int zoneId);
    // TODO: bool updateSlotStatus(int slotId, int newStatus);

    // ---- Reservation ----
    // TODO: bool insertReservation(/* Reservation params */);
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
