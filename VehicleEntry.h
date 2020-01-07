#ifndef MATAM_3_VEHICLEENTRY_H
#define MATAM_3_VEHICLEENTRY_H

#include "Time.h"
#include "ParkingLotTypes.h"

using namespace ParkingLotUtils;

namespace MtmParkingLot{
    
    // todo: comment
    class VehicleEntry {
        int penalty;
        Time entranceTime;
        LicensePlate licensePlate;
        ParkingSpot parkingSpot;

        public:
        VehicleEntry(Time parkingTime, LicensePlate licensePlate)
        :entranceTime(parkingTime),licensePlate(licensePlate),penalty(0){}; 

        ParkingSpot getParkingSpot(){return parkingSpot;};   
        Time getEntranceTime(){return entranceTime;};  
        int calculateTotalFee(Time exitTime);  
    };

}

#endif //MATAM_3_VEHICLEENTRY_H
