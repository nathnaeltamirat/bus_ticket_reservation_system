void age_validate() {
    if (age.empty() || age <= 10 || age >=90){
        return false;
    }
}
void name_validate() {
    if (name.empty() || name.length() < 2 || name.length() > 50) {
        return false;
    }
}
void phone_no_validate() {
    if (phone_no.empty() || !isdigit(phone_no) || ) {
        return false;
    }
}
void gender_validate() {
    gender = tolower(gender);
    if (gender.empty() || gender == m || gender == f ) {
        return false;
    }}