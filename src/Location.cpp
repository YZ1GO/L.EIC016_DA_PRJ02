#include "Location.h"

Location::Location() {};

Location::Location(int id, double longitude, double latitude) {
    this->id = id;
    this->longitude = longitude;
    this->latitude = latitude;
}

int Location::getId() {
    return this->id;
}

double Location::getLongitude() {
    return this->longitude;
}

double Location::getLatitude() {
    return this->latitude;
}
