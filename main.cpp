#include<iostream>
#include<iomanip>
#include<fstream>
#include <set>
#include <vector>
#include <ctime>
#include <string>
#include <cstdlib>
#include <sstream>

using namespace std;

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
    cout << "Enter your name: ";
    cin >> p.name;
    cout << "Enter your phone_no: ";
    cin >> p.phone_no;
    cout << "Enter Gender (m or f)";
    cin >> p.gender;
    cout << "Enter your age: ";
    cin >> p.age;
    cout << "Enter the day, month and year of reversed date respectively: ";
    cin >> d.day >> d.month >> d.year;
    p.date_of_reservation = d;
    p.ticket_id = generateUniqueID();
    return p;

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

    throw runtime_error("Bus not found");
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
void saving_seat(int toggle){
    fstream f1,f2,f3;
    f1.open("routes/addis_bahir.txt",ios::in|ios::out|ios::trunc);
    f2.open("routes/addis_dire.txt",ios::in|ios::out|ios::trunc);
    f3.open("routes/addis_jima.txt",ios::in|ios::out|ios::trunc);
    bus_data& b = get_bus("addis","bahir");
    bus_data& d = get_bus("addis","dire");
    bus_data& j = get_bus("addis","jima");

    int day,month,year,age;
    if(toggle == 0){
        for(auto a = b.customers.begin(); a!= b.customers.end(); a++){
            f1 << a->name << " " << a->age << " " << a->gender << " "
            << a->phone_no << " " << a->ticket_id << " " << a->seat << " "
            << a->date_of_reservation.day << " "
            << a->date_of_reservation.month << " "
            << a->date_of_reservation.year << endl;

        }
    }
    if(toggle == 1){
        for(auto a = d.customers.begin(); a!= d.customers.end(); a++){
            f2 << a->name << " " << a->age << " " << a->gender << " "
            << a->phone_no << " " << a->ticket_id << " " << a->seat << " "
            << a->date_of_reservation.day << " "
            << a->date_of_reservation.month << " "
            << a->date_of_reservation.year << endl;
        }
    }
    if(toggle == 2){
        for(auto a = j.customers.begin(); a!= j.customers.end(); a++){
            f3 << a->name << " " << a->age << " " << a->gender << " "
            << a->phone_no << " " << a->ticket_id << " " << a->seat << " "
            << a->date_of_reservation.day << " "
            << a->date_of_reservation.month << " "
            << a->date_of_reservation.year << endl;
        }
    }
    
}
bool seat_reservation() {
    string origin, destination;
    int seat;
    passenger_data p = customer_create();
    cout << "Enter the origna and destination of the buses respectively: ";
    cin >> origin >> destination;
    bus_data& b = get_bus(origin,destination);
    if (check_full(b,50)){
        cout << "Sorry there is no avialable seats for this bus" << endl;
        return 1;
    }
    do{
    cout << "Choose Seat from 1 - 50:";
    cin >> seat;
    }while(!check_seat_availability(b,seat));
    cout << "out of loop" << endl;
    b.seat[seat] = 1;
    p.seat = seat;
    b.customers.push_back(p);
    int toggle;
    if(b.origin == "addis" && b.destination == "bahir"){
        toggle = 0;
    }else if(b.origin == "addis" && b.destination == "dire"){
        toggle = 1;
    }else if (b.origin == "addis" && b.destination == "jima"){
        toggle = 2;
    }
    saving_seat(toggle);
    return true;
};
bool cancel_reservation() {
    string ticket_id,origin,destination;
    int toggle;
    cout << "Enter ticket_id: ";
    cin >> ticket_id;
    cout << "Enter the origna and destination of the buses respectively: ";
    cin >> origin >> destination;
    bus_data& b = get_bus(origin,destination);
    fstream f1,f2,f3;
    f1.open("routes/addis_bahir.txt",ios::in|ios::out);
    f2.open("routes/addis_dire.txt",ios::in|ios::out);
    f3.open("routes/addis_jima.txt",ios::in|ios::out);
    if(b.origin == "addis" && b.destination == "bahir"){
        toggle = 0;
    }else if(b.origin == "addis" && b.destination == "dire"){
        toggle = 1;
    }else if (b.origin == "addis" && b.destination == "jima"){
        toggle = 2;
    }
    if(toggle == 0){
        for(auto a = b.customers.begin(); a!= b.customers.end(); a++){
            if (a->ticket_id == ticket_id){
                continue;
            }

            f1 << a->name << " " << a->age << " " << a->gender << " "
            << a->phone_no << " " << a->ticket_id << " " << a->seat << " "
            << a->date_of_reservation.day << " "
            << a->date_of_reservation.month << " "
            << a->date_of_reservation.year << endl;

        }
    }
    if(toggle == 1){
        for(auto a = b.customers.begin(); a!= b.customers.end(); a++){
            if (a->ticket_id == ticket_id){
                continue;
            }

            f2 << a->name << " " << a->age << " " << a->gender << " "
            << a->phone_no << " " << a->ticket_id << " " << a->seat << " "
            << a->date_of_reservation.day << " "
            << a->date_of_reservation.month << " "
            << a->date_of_reservation.year << endl;
        }
    }
    if(toggle == 2){
        for(auto a = b.customers.begin(); a!= b.customers.end(); a++){
            if (a->ticket_id == ticket_id){
                continue;
                }

            f3 << a->name << " " << a->age << " " << a->gender << " "
            << a->phone_no << " " << a->ticket_id << " " << a->seat << " "
            << a->date_of_reservation.day << " "
            << a->date_of_reservation.month << " "
            << a->date_of_reservation.year << endl;
        }
    }

    f1.close();
    f2.close();
    f3.close();

}
void view_all_reservations() {
    //naod
}

void admin_dashboard() {
    //robel
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
    bus_data& b = get_bus("addis","bahir");
    bus_data& d = get_bus("addis","dire");
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
    route1.destination = "dire";
    route2.origin = "addis";
    route2.destination = "bahir";
    route3.origin = "addis";
    route3.destination = "jima";
    sheger.push_back(route1);
    sheger.push_back(route2);
    sheger.push_back(route3);
    readData();
    int choice;
    cout << "Enter 1 for seat reservation or 2 to cancel reservation: ";
    cin >> choice;
    if (choice == 1){
    seat_reservation();
    }else{
        cancel_reservation();
    }

}


