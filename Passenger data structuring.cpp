‎#include <iostream>
‎#include <iomanip>
‎#include <fstream>
‎#include <set>
‎#include <string>
‎using namespace std;
‎
‎struct Date {
‎    int day, month, year;
‎};
‎
‎struct PassengerData {
‎    string name, phone_no, ticket_id;
‎    int age, seat_number;
‎    char gender;
‎    Date date_of_reservation;
‎};
‎
‎struct BusInfo {
‎    string bus_number;
‎    string driver_name;
‎    int total_seats;
‎    string departure_time;
‎    string arrival_time;
‎};
‎
‎struct TripInfo {
‎    string start_point;
‎    string end_point;
‎    PassengerData passenger;
‎    BusInfo bus;
‎};
‎
‎void seat_reservation() {
‎    // nati
‎}
‎
‎void cancel_reservation() {
‎    // naod
‎}
‎
‎void view_all_reservations() {
‎    // naod
‎}
‎
‎void check_seat_availability() {
‎    // lelisa
‎}
‎
‎void admin_dashboard() {
‎    // robel
‎}
‎
‎void age_validate() {
‎    // robel
‎}
‎
‎void name_validate() {
‎    // robel
‎}
‎
‎void phone_no_validate() {
‎    // robel
‎}
‎
‎void gender_validate() {
‎    // robel
‎}
‎
‎void validate_main_menu_choice() {
‎    // robel
‎}
‎
‎void mainMenu() {
‎    int choice;
‎    do {
‎        cout << "\n=== Bus Ticket Reservation System ===\n";
‎        cout << "1. Book a Seat\n";
‎        cout << "2. Cancel Reservation\n";
‎        cout << "3. View All Reservations\n";
‎        cout << "4. Check Seat Availability\n";
‎        cout << "5. View Dashboard (Admin Use Only)\n";
‎        cout << "6. Exit\n";
‎        cout << "Enter choice: ";
‎        cin >> choice;
‎        cin.ignore();
‎
‎        switch (choice) {
‎            case 1: seat_reservation(); break;
‎            case 2: cancel_reservation(); break;
‎            case 3: view_all_reservations(); break;
‎            case 4: check_seat_availability(); break;
‎            case 5: admin_dashboard(); break;
‎            case 6: cout << "Exiting...\n"; break;
‎            default: cout << "Invalid choice.\n";
‎        }
‎    } while (choice != 6);
‎}
‎
‎int main() {
‎    mainMenu();
‎    return 0;
‎}
‎
