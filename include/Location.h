#ifndef FEUP_DA_02_LOCATION_H
#define FEUP_DA_02_LOCATION_H

struct Coordinates {
    double longitude;
    double latitude;
};

class Location {
private:
    int id;
    Coordinates coordinates;
public:
    Location();
    Location(int id, double longitude, double latitude);
    int getId();
    Coordinates getCoordinates();
};

#endif //FEUP_DA_02_LOCATION_H
