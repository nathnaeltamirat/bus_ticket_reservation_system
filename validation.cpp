#include <iostream>
using namespace std;
bool age_validate(int age) {
    if ( age <= 10 || age >=90){
        return false;
    }
}
bool name_validate(string name) {
    if (name.empty() || name.length() < 2 || name.length() > 50) {
        return false;
    }
}
bool phone_no_validate(string phone_no) {
    if (phone_no.empty() ) {
        return false;
    }
}
bool gender_validate(char gender) {
    gender = tolower(gender);
    if (gender == 'm' || gender == 'f' ) {
        return false;
    }}