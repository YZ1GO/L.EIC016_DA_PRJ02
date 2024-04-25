#include "Location.h"

using namespace std;

Location::Location() {};

Location::Location(int id, double longitude, double latitude) {
    this->id = id;
    this->coordinates.longitude = longitude;
    this->coordinates.latitude = latitude;
}

int Location::getId() {
    return this->id;
}

Coordinates Location::getCoordinates() {
    return this->coordinates;
}
