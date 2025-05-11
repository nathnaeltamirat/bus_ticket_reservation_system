

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
