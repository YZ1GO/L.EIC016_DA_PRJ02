#ifndef FEUP_DA_02_LOCATION_H
#define FEUP_DA_02_LOCATION_H

class Location {
private:
    int id;
    double longitude;
    double latitude;
public:
    Location();
    Location(int id, double longitude, double latitude);
    int getId();
    double getLongitude();
    double getLatitude();
    bool operator==(const Location& other) const {
        return id == other.id;
    }
};

#endif //FEUP_DA_02_LOCATION_H
