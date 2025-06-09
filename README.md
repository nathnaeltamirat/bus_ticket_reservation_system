# bus_ticket_reservation_system

## Overview
A console-based ticket reservation system that allows users to:
** Book bus tickets
** Cancel reservations
** View reservations - to get a ticket
** View Dashboard (admin use only)

Data will be stored using text files, and the system will run entirely from the terminal/command line.

### Booking a seat
Required Inputs
```bash
"name"
"phone_number"
"Gender " 
"Age " 
"Date"
"Origin and Destination Availble Routes (addis bahirdar || addis diredewa || addis  jima)"
"Bus seat"
```
If all everything sucesfull
```bash
"Seat saved succesfully  please save this ticket id in secure place ********************"
```

### Cancel Reservation
Required Inputs
```bash
"Origin and Destination Availble Routes (addis bahirdar || addis diredewa || addis  jima)"
"ticket_id"
"Bus seat"
```
If all everything sucesfull
```bash
"Cancelled Sucesffuly"
```
### View Reservation
Required Inputs
```bash
"Origin and Destination Availble Routes (addis bahirdar || addis diredewa || addis  jima)"
"ticket_id"
```
If all everything sucesfull
```bash
"Ticket generate Sucesffully on ticket.txt"
```
Output
```bash
"        Individual Ticket
Name: abebe
Age: 30
phone_no: 99999999
Ticket_id: 17494967569496
Date of reservation: 9/9/1000
Seat number: 9"
```

## View Dashboard - Admin
Default passowrd - 
```bash 
admin123 
```

### View All Booking
```bash
"=== ALL BOOKINGS ===

Route: addis to bahirdar
Name           Seat      Ticket ID      Gender    Phone          Date
          --------------------------------------------------------------------------------
abebe          9         1749497164829  m         999999999      9/9/1000

Total bookings across all routes: 1"
```

### Search Booking
Instruction
```bash
"Enter T or S"
```
Output
```bash
"Enter Ticket ID: 1749497164829
 Booking Found: abebe (Seat 9)"
```
### Export Booking
Instruction
```bash
"NONE"
```
Output
```bash
"on booking_report.txt
========== Booking Report ==========
Ticket ID         Seat No   Name              Gender         Phone          
---------------------------------------------------------------------------
1749497164829      9         abebe             m           999999999      

"
```
### Delete booking
Remove all booking with a simple confirmation