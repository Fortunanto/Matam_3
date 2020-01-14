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
        VehicleEntry(){};
        VehicleEntry(Time parkingTime, LicensePlate licensePlate,
        VehicleType parkingBlock,int parkingNumber,VehicleType vehicleType)
            :entranceTime(parkingTime),licensePlate(licensePlate),
            penalty(0),parkingSpot(parkingBlock,parkingNumber),
            vehicleType(vehicleType){}

        friend bool operator<(const VehicleEntry& ve1, const VehicleEntry& ve2);

        ParkingSpot getParkingSpot() const{return parkingSpot;}
        Time getEntranceTime() const{return entranceTime;}
        LicensePlate getLicensePlate() const {return licensePlate;}
        int calculateTotalFee(Time exitTime) const;  
        VehicleType getVehicleType() const{return vehicleType;}
        void addPenalty (int penaltyToAdd){this->penalty+=penaltyToAdd;}
        int getPenalty(){return this->penalty;}

    };

}

#endif //MATAM_3_VEHICLEENTRY_H
