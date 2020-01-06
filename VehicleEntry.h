#ifndef MATAM_3_VEHICLEENTRY_H
#define MATAM_3_VEHICLEENTRY_H

#include "Time.h"
#include "ParkingLotTypes.h"

using namespace ParkingLotUtils;

// todo: comment
class VehicleEntry {
    public:
    VehicleEntry(Time parkingTime, LicensePlate licensePlate)
    :parkingTime(parkingTime),licensePlate(licensePlate){};
    Time parkingTime;
    LicensePlate licensePlate;
};



#endif //MATAM_3_VEHICLEENTRY_H
