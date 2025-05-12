#include<iostream>
#include<iomanip>
#include<fstream>
#include <set>
#include <vector>
#include <ctime>
#include <string>
#include <cstdlib>
#include <sstream>
#include <algorithm>

using namespace std;
bool age_validate(int age);
bool name_validate(const string& name);
bool phone_no_validate(const string& phone_no);
bool gender_validate(char gender);
void seat_reservation();
void cancel_reservation();
void view_reservations();
void admin_dashboard();

bool age_validate(int age) {
    return (age >10 && age <90);
}
bool name_validate(const string& name) {
    if (name.length() < 2 || name.length() > 50) {
        return false;
    }

    for (char c : name) {
        if (!isalpha(c) && c != ' ') {
            return false;
        }
    }
    return true;
}
bool phone_no_validate(const string& phone_no) {
    if (phone_no.length() != 9 || phone_no.substr(0, 1) != "9") {
        return false;
    }

    for (char c : phone_no) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}
bool gender_validate(char gender) {
    gender = tolower(gender);
    return (gender == 'm' || gender == 'f' );
}

string generateUniqueID() {
    // Use current time as seed
    srand(time(0));

    // Get current timestamp
    time_t now = time(0);

    // Generate a random number
    int random_part = rand() % 10000; // 4-digit

    // Convert time to string
    stringstream ss;
    ss << now << random_part;

    return ss.str();
}
int count = 0;
struct date {
    int day ,month ,year;

};
struct passenger_data {
    string name ,phone_no ;
    string ticket_id;
    int age ;
    char gender;
    int seat;
    date date_of_reservation;
};
struct bus_data{
    string  origin,destination;
    vector<passenger_data> customers;
    int seat[50] = {0};
};
vector<bus_data> sheger;
passenger_data customer_create(){
    passenger_data p;
    date d;
    int val = time(0);
    cin.ignore();
  
    while (true) {
        cout << "Enter your name: ";
        getline(cin, p.name);
        if (name_validate(p.name)) break;
        cout << "Invalid name! Please use only letters and spaces (2-50 characters).\n";
    }
    
    while (true) {
        cout << "Enter your phone number (9 digits starting with 9): +251";
        cin >> p.phone_no;
        if (phone_no_validate(p.phone_no)) break;
        cout << "Invalid phone number! Please enter a 10-digit number starting with 9.\n";
        cin.clear();
        cin.ignore();
    }
    
    while (true) {
        cout << "Enter Gender (m or f): ";
        cin >> p.gender;
        if (gender_validate(p.gender)) break;
        cout << "Invalid gender! Please enter 'm' or 'f'.\n";
        cin.clear();
        cin.ignore();
    }
    
    
    while (true) {
        cout << "Enter your age (11-89): ";
        cin >> p.age;
        if (age_validate(p.age)) break;
        cout << "Invalid age! Please enter an age between 11 and 89.\n";
        cin.clear();
        cin.ignore(100, '\n');
    }
    cin >> d.day >> d.month >> d.year;
    p.date_of_reservation = d;
    p.ticket_id = generateUniqueID();
    cin.ignore();
    return p;

}

void mainMenu() {
    int choice;
    do {
        cout << "\n=== Bus Ticket Reservation System ===\n";
        cout << "1. Book a Seat\n";
        cout << "2. Cancel Reservation\n";
        cout << "3. View Reservations - To get a ticket\n";
        cout << "4. View dashboard(admin use only)\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: seat_reservation(); break;
            case 2: cancel_reservation(); break;
            case 3: view_reservations(); break;
            case 4: admin_dashboard(); break;
            case 5: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 5);
}
bool check_seat_availability(bus_data &b,int s){
   return b.seat[s] == 0;
}
 
bus_data& get_bus(string origin, string destination) {
    for (auto& bus : sheger) {
        if (bus.origin == origin && bus.destination == destination) {
            return bus; 
        }
    }
    throw runtime_error("No bus found in this route");

    
}
bool check_full(bus_data b, int seat_size){
    int remaining_seat = 0;
    for (int i=1; i < seat_size; i++){
        if(b.seat[i] == 0){
            remaining_seat ++;
        }
        
    }
    if (remaining_seat == 0){
        return true;
    }
    return false;

}
bool saving_seat(int toggle){
    string path,origin,destination;
    fstream f;
    if (toggle == 0) path = "routes/addis_bahir.txt";
    else if (toggle == 1) path = "routes/addis_dire.txt";
    else if (toggle == 2) path = "routes/addis_jima.txt";

    if (toggle == 0) destination = "bahirdar";
    else if (toggle == 1) destination = "diredewa";
    else if (toggle == 2) destination = "jima";

    bus_data& b = get_bus("addis",destination);
    f.open(path,ios::out|ios::trunc);
    if(toggle == 0){
        for(auto a = b.customers.begin(); a!= b.customers.end(); a++){
            f << a->name << " " << a->age << " " << a->gender << " "
            << a->phone_no << " " << a->ticket_id << " " << a->seat << " "
            << a->date_of_reservation.day << " "
            << a->date_of_reservation.month << " "
            << a->date_of_reservation.year << endl;

        }
    }
    f.close();
    return true;
}
void seat_reservation() {
    string origin, destination;
    int seat;
    passenger_data p = customer_create();
    cout << "Enter the origna and destination of the buses respectively: ";
    cin >> origin >> destination;
    bus_data& b = get_bus(origin,destination);
    if (check_full(b,50)){
        cout << "Sorry there is no avialable seats for this bus" << endl;
        mainMenu();
    }
    do{
    cout << "Choose Seat from 1 - 50:";
    cin >> seat;
    }while(!check_seat_availability(b,seat));
    b.seat[seat] = 1;
    p.seat = seat;
    b.customers.push_back(p);
    int toggle;
    if(b.origin == "addis" && b.destination == "bahirdar"){
        toggle = 0;
    }else if(b.origin == "addis" && b.destination == "diredewa"){
        toggle = 1;
    }else if (b.origin == "addis" && b.destination == "jima"){
        toggle = 2;
    }
    if (saving_seat(toggle)) cout << "Seat saved succesfully" << endl;
    mainMenu();
};
void cancel_reservation() {
    string ticket_id,origin,destination,path;
    int toggle,check;
    bool found = false;
    fstream f1;
    do {
        cout << "Do you want to cancel reservation(continue 1) or exit(-1): ";
        cin >> check;
        if(check == -1){
            break;
        }
       cout << "Enter the origna and destination of the buses respectively: ";
        cin >> origin >> destination;
        bus_data& b = get_bus(origin,destination);
        cout << "Enter ticket_id: ";
        cin >> ticket_id;
        auto oldzie = b.customers.size();
        b.customers.erase(
                remove_if(b.customers.begin(), b.customers.end(), [&](const passenger_data& c) {
                return c.ticket_id == ticket_id;
            }),
            b.customers.end()
        );
        found = oldzie > b.customers.size();
        if(b.origin == "addis" && b.destination == "bahirdar"){
            toggle = 0;
                    }else if(b.origin == "addis" && b.destination == "diredewa"){
            toggle = 1;
        }else if (b.origin == "addis" && b.destination == "jima"){
            toggle = 2;
        }
        if (toggle == 0) path = "routes/addis_bahir.txt";
        else if (toggle == 1) path = "routes/addis_dire.txt";
        else if (toggle == 2) path = "routes/addis_jima.txt";
        f1.open(path,ios::in|ios::out|ios::trunc);
        for(auto a = b.customers.begin(); a!= b.customers.end(); a++){
        
            f1 << a->name << " " << a->age << " " << a->gender << " "
            << a->phone_no << " " << a->ticket_id << " " << a->seat << " "
            << a->date_of_reservation.day << " "
            << a->date_of_reservation.month << " "
            << a->date_of_reservation.year << endl;
        }
        if(!found){
            cout << "Not Found please try again " << endl;   
        }else{
            cout << "Cancelled Sucesffuly" << endl;
        }
    }while(!found);

    f1.close();

}
void view_reservations() {
    string ticket_id,origin,destination,path;
    int toggle,check;
    bool found = false;
    fstream f1;
    do {
        cout << "Do you want to see reservation(continue 1) or exit(-1): ";
        cin >> check;
        if(check == -1){
            break;
        }
       cout << "Enter the origna and destination of the buses respectively: ";
        cin >> origin >> destination;
        bus_data& b = get_bus(origin,destination);
        cout << "Enter ticket_id: ";
        cin >> ticket_id;
        f1.open("ticket.txt",ios::out|ios::trunc);
        auto it = find_if(b.customers.begin(), b.customers.end(), [&](const passenger_data& c) {
            return c.ticket_id == ticket_id;
        });
        if(it != b.customers.end()){
            found = true;
        for(auto a = b.customers.begin(); a!= b.customers.end(); a++){
            if (a->ticket_id == ticket_id){
                f1 << setw(25) << "Individual Ticket" << endl;
                f1 << "Name: " << a->name << endl;
                f1 << "Age: " << a->age << endl;
                f1 << "phone_no: " << a->phone_no << endl;
                f1 << "Ticket_id: " << a->ticket_id << endl;
                f1 << "Date of reservation: " << a->date_of_reservation.day << "/" << a->date_of_reservation.month<< "/" << a->date_of_reservation.year << endl;
                f1 << "Seat number: " << a->seat << endl;
            }

        }
        cout << "Ticket generate Sucesffully on ticket.txt" << endl;
        };
        if(!found) cout << "Ticket Not found Try again" << endl;
    }while(!found);
    f1.close();
}



void admin_dashboard();
void view_bookings();
void searchBooking();
void exportBookings();
void resetBookings();
void pauseAndClear();

void admin_dashboard() {
    string password;
    cout << "Enter admin password: ";
    cin >> password;
    
    if (password != "admin123") {
        cout << "Invalid password. Access denied.\n";
        return;
    }
    int choice;

    while (true) {
        cout << "\n========== ADMIN DASHBOARD ==========\n";
        cout << "1. View All Bookings\n";
        cout << "2. Search Booking by Ticket ID / Seat No\n";
        cout << "3. Export Bookings to Report File\n";
        cout << "4. Reset All Bookings\n";
        cout << "5. Logout\n";
        cout << "=====================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                view_bookings();
                break;
            case 2:
                searchBooking();
                break;
            case 3:
                exportBookings();
                break;
            case 4:
                resetBookings();
                break;
            case 5:
                cout << "\n Logging out...\n";
                return;
            default:
                cout << " Invalid option. Try again.\n";
        }
       return;
    }
    
}

// CASE 1 
void view_bookings() {
    cout << "\n=== ALL BOOKINGS ===\n";  
    int totalBookings =0;                                
    for (const auto& bus : sheger) {
        if (bus.customers.empty())
            continue;
        totalBookings += bus.customers.size();    
        cout << "\nRoute: " << bus.origin << " to " << bus.destination << "\n";
        cout << left << setw(15) << "Name" << setw(10) << "Seat" 
             << setw(15) << "Ticket ID" << setw(10) << "Gender" 
             << setw(15) << "Phone" << setw(15) << "Date\n";
        cout << string(80, '-') << endl;

        int counter = 1;
        for (const auto& cust : bus.customers) {
            cout << setw(15) << cust.name << setw(10) << cust.seat 
                 << setw(15) << cust.ticket_id << setw(10) << cust.gender 
                 << setw(15) << cust.phone_no 
                 << cust.date_of_reservation.day << "/" 
                 << cust.date_of_reservation.month << "/" 
                 << cust.date_of_reservation.year << endl;
        }
    }
    if (totalBookings == 0) {
        cout << "\nNo bookings found in the system.\n";
    } else {
        cout << "\nTotal bookings across all routes: " << totalBookings << endl;
    }
    
    // Pause to view results
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}
// case 2
void searchBooking() {
    string id;
    int seat;
    char type;
    cout << "\nSearch Booking\n";
    cout << "Search by (T)icket ID or (S)eat No? ";
    cin >> type;

    bool found = false;
    if (type == 'T' || type == 't') {
        cout << "Enter Ticket ID: ";
        cin >> id;
        for(const auto& bus : sheger){
            for (const auto& cust : bus.customers) {
                if (cust.ticket_id == id) {
                    cout << " Booking Found: " << cust.name << " (Seat " << cust.seat << ")\n";
                    found = true;
                    break;
                }
            }
        }
    } 
    else if (type == 'S' || type == 's') {
        cout << "Enter Seat Number: ";
        cin >> seat;
        for(const auto& bus : sheger){
            for (const auto& cust : bus.customers) {
            if (cust.seat == seat) {
                cout << " Booking Found: " << cust.name << " (Ticket ID: " << cust.ticket_id << ")\n";
                found = true;
                break;
            }
        }
    }   
    } else {
        cout << "Invalid option.\n";
        return;
    }

    if (!found) {
        cout << " Booking not found.\n";
    }
}



// Case 3
void exportBookings() {
    ofstream report("booking_report.txt");
    if (!report) {
        cout << " Failed to create report file.\n";
        return;
    }

    report << "========== Booking Report ==========\n";
    report << left
           << setw(18) << "Ticket ID"
           << setw(10) << "Seat No"
           << setw(18) << "Name"
           << setw(15) << "Gender"
           << setw(15) << "Phone"
           << "\n";

    report << string(75, '-') << "\n";

    // Data Rows
    for (const auto& bus : sheger) {
        for (const auto& cust : bus.customers) {
            report << left
                   << setw(18) << cust.ticket_id<<" "
                   << setw(10) << cust.seat
                   << setw(18) << cust.name
                   << setw(12) << cust.gender
                   << setw(15) << cust.phone_no
                   << "\n";
        }
    }
    report.close();
    cout << "Report exported to booking_report.txt\n";
}

// CASE 4
void resetBookings() {
    char confirm;
    cout << "\nAre you sure you want to delete ALL bookings? (y/n): ";
    cin >> confirm;


    if (confirm == 'y' || confirm == 'Y') {
        for (auto& bus : sheger){
            bus.customers.clear();
            for(int i = 0; i<50; i++){
                bus.seat[i] = 0;
            }
        }
        cout << "All bookings have been reset.\n";
    } 
    else {
        cout << "Operation cancelled.\n";
    }
}

passenger_data saving_data(string name,int age,char gender,string phone_number,string ticket_id,int seat,int day,int month,int year){
        passenger_data p;
        p.name = name;
        p.age = age;
        p.gender = gender;
        p.phone_no = phone_number;
        p.ticket_id = ticket_id;
        p.date_of_reservation.day = day;
        p.date_of_reservation.month = month;
        p.date_of_reservation.year = year;
        p.seat = seat;
        return p;
}
void readData(){
    fstream f1,f2,f3;
    f1.open("routes/addis_bahir.txt",ios::in|ios::out);
    f2.open("routes/addis_dire.txt",ios::in|ios::out);
    f3.open("routes/addis_jima.txt",ios::in|ios::out);
    bus_data& b = get_bus("addis","bahirdar");
    bus_data& d = get_bus("addis","diredewa");
    bus_data& j = get_bus("addis","jima");
    //name age gender phone_number ticket_id day month year
    string name,phone_number,ticket_id;
    char gender;
    int day,month,year,age,seat;
    while(f1 >> name >> age >> gender >> phone_number >> ticket_id >> seat >> day >> month >> year ){
        b.seat[seat] = 1;
        passenger_data p = saving_data(name,age,gender,phone_number,ticket_id,seat,day,month,year);
        b.customers.push_back(p);
    }
    while(f2 >> name >> age >> gender >> phone_number >> ticket_id >> seat >> day >> month >> year ){
        d.seat[seat] = 1;
        passenger_data p = saving_data(name,age,gender,phone_number,ticket_id,seat,day,month,year);
        d.customers.push_back(p);
    }
    while(f3 >> name >> age >> gender >> phone_number >> ticket_id >> seat >> day >> month >> year ){
        j.seat[seat] = 1;
        passenger_data p = saving_data(name,age,gender,phone_number,ticket_id,seat,day,month,year);
        j.customers.push_back(p);
    }
    f1.close();
    f2.close();
    f3.close();
}

int main() {
    bus_data route1,route2,route3;
    route1.origin = "addis";
    route1.destination = "bahirdar";
    route2.origin = "addis";
    route2.destination = "diredewa";
    route3.origin = "addis";
    route3.destination = "jima";
    sheger.push_back(route1);
    sheger.push_back(route2);
    sheger.push_back(route3);
    readData();
    mainMenu();

}


