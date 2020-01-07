#ifndef MATAM_3_VEHICLEENTRY_H
#define MATAM_3_VEHICLEENTRY_H

#include "Time.h"
#include "ParkingLotTypes.h"
#include "ParkingSpot.h"

using namespace ParkingLotUtils;

namespace MtmParkingLot{
    
    // todo: comment
    class VehicleEntry {
        Time entranceTime;
        LicensePlate licensePlate;
        int penalty;      
        ParkingSpot parkingSpot;
        VehicleType vehicleType;

        public:
        VehicleEntry(Time parkingTime, LicensePlate licensePlate,
        VehicleType parkingBlock,int parkingNumber,VehicleType vehicleType)
            :entranceTime(parkingTime),licensePlate(licensePlate),
            penalty(0),parkingSpot(parkingBlock,parkingNumber),
            vehicleType(vehicleType){}

        ParkingSpot getParkingSpot(){return parkingSpot;} 
        Time getEntranceTime(){return entranceTime;}
        int calculateTotalFee(Time exitTime);  
        VehicleType getVehicleType(){return vehicleType;}
        void addPenalty(int penaltyToAdd){penalty+=penaltyToAdd;}
    };

}

#endif //MATAM_3_VEHICLEENTRY_H
