#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;


struct Booking {
    string ticketID;
    int seatNo;
    string name;
    string gender;
    string phone;
};

vector<Booking> bookings;

void showDashboard();
void viewAllBookings();
void searchBooking();
void exportBookings();
void resetBookings();
void pauseAndClear();

int main() {
    showDashboard();
    return 0;
}

void showDashboard() {
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
                viewAllBookings();
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
void viewAllBookings() {
    cout << "\nAll Bookings:\n";
    if (bookings.empty()) {
        cout << "No bookings available.\n";
        return;
    }

    cout << left << setw(12) << "Ticket ID" << setw(10) << "Seat No" 
         << setw(15) << "Name" << setw(10) << "Gender" << setw(15) << "Phone\n";
    cout << "-------------------------------------------------------------\n";

    for (const auto& b : bookings) {
        cout << setw(12) << b.ticketID << setw(10) << b.seatNo
             << setw(15) << b.name << setw(10) << b.gender << setw(15) << b.phone << "\n";
    }
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
        for (const auto& b : bookings) {
            if (b.ticketID == id) {
                cout << " Booking Found: " << b.name << " (Seat " << b.seatNo << ")\n";
                found = true;
                break;
            }
        }
    } else if (type == 'S' || type == 's') {
        cout << "Enter Seat Number: ";
        cin >> seat;
        for (const auto& b : bookings) {
            if (b.seatNo == seat) {
                cout << " Booking Found: " << b.name << " (Ticket ID: " << b.ticketID << ")\n";
                found = true;
                break;
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
    report << left << setw(12) << "Ticket ID" << setw(10) << "Seat No" 
           << setw(15) << "Name" << setw(10) << "Gender" << setw(15) << "Phone\n";
    report << "-------------------------------------------------------------\n";

    for (const auto& b : bookings) {
        report << setw(12) << b.ticketID << setw(10) << b.seatNo
               << setw(15) << b.name << setw(10) << b.gender << setw(15) << b.phone << "\n";
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
        bookings.clear();
        cout << "All bookings have been reset.\n";
    } else {
        cout << "Operation cancelled.\n";
    }
}
