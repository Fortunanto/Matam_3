#ifndef MTMPARKINGLOT_PARKINGLOT_H
#define MTMPARKINGLOT_PARKINGLOT_H

#include "ParkingLotTypes.h"
#include "Time.h"
#include "ParkingSpot.h"

#include "UniqueArray.h"
#include "VehicleEntry.h"

#include <map>

namespace MtmParkingLot {

    using namespace ParkingLotUtils;
    using std::ostream;
    using namespace std;

    class ParkingLot {

    UniqueArray<string> **parkingLots;

    map<LicensePlate,VehicleEntry> parkedVehicles;

    public:
        ParkingLot(unsigned int parkingBlockSizes[]);
        ~ParkingLot();
        ParkingResult enterParking(VehicleType vehicleType,
                LicensePlate licensePlate, Time entranceTime);

        ParkingResult exitParking(LicensePlate licensePlate, Time exitTime);

        ParkingResult getParkingSpot(LicensePlate licensePlate,
                ParkingSpot& parkingSpot) const;

        void inspectParkingLot(Time inspectionTime);

        friend ostream& operator<<(ostream& os, const ParkingLot& parkingLot);

    private:
        pair<VehicleType,int> 
        tryFindSpotForHandicapped(LicensePlate licensePlate, Time entranceTime);

    };

}

#endif //MTMPARKINGLOT_PARKINGLOT_H
