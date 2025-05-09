#include<iostream>
#include<iomanip>
#include<fstream>
#include <set>
#include <vector>
using namespace std;

int count = 0;
struct date {
    int day ,month ,year;

};
struct passenger_data {
    string name ,phone_no,ticket_id ;
    int age ;
    char gender  ;
    date date_of_reservation;
};
struct bus_data{
    string  origin,destination;
    vector<passenger_data> customers;
    string seat[50] = {0};
};
void customer_create(){
    passenger_data p;
    date d;
    count += 1;
    cout << "Enter your name: ";
    cin >> p.name;
    cout << "Enter your phone_no: ";
    cin >> p.phone_no;
    cout << "Enter your age: ";
    cin >> p.age;
    cout << "Enter the day, month and year of reversed date respectively: ";
    cin >> d.day >> d.month >> d.year;
    p.ticket_id = count;

}
void seat_reservation() {
    
    //nati
}
void cancel_reservation() {
    //naod
}
void view_all_reservations() {
    //naod
}
void check_seat_availability() {
    //lelisa
}
void admin_dashboard() {
    //robel
}
void age_validate() {
    //robel
}
void name_validate() {
    //robel
}
void phone_no_validate() {
    //robel
}
void gender_validate() {
    //robel
}
void mainMenu() {
    int choice;
    do {
        cout << "\n=== Bus Ticket Reservation System ===\n";
        cout << "1. Book a Seat\n";
        cout << "2. Cancel Reservation\n";
        cout << "3. View All Reservations\n";
        cout << "4. Check Seat Availability\n";
        cout << "5. View dashboard(admin use only)";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: seat_reservation(); break;
            case 2: cancel_reservation(); break;
            case 3: view_all_reservations(); break;
            case 4: check_seat_availability(); break;
            case 5: admin_dashboard(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 6);
}
void validate_main_menu_choice() {
    //robel
}
int main() {
    vector<bus_data> sheger;
    bus_data first;
    first.origin = "Addis Ababa";
    first.destination = "DireDewa";


    mainMenu();
}


