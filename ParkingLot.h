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

    UniqueArray<string> parkingLots[3]; //todo: change to const or smthing

    map<LicensePlate,VehicleEntry> parkedVehicles;

    public:
        ParkingLot(unsigned int parkingBlockSizes[]):parkingLots{
            UniqueArray<string>(parkingBlockSizes[VehicleType::MOTORBIKE]),
            UniqueArray<string>(parkingBlockSizes[VehicleType::HANDICAPPED]),
            UniqueArray<string>(parkingBlockSizes[VehicleType::CAR])
        }{}
        ~ParkingLot();
        ParkingResult enterParking(VehicleType vehicleType,
                LicensePlate licensePlate, Time entranceTime);

        ParkingResult exitParking(LicensePlate licensePlate, Time exitTime);

        ParkingResult getParkingSpot(LicensePlate licensePlate,
                ParkingSpot& parkingSpot) const;
        
        map<LicensePlate,VehicleEntry> getParkedVehicles() const {
            return this->parkedVehicles;
        }

        void inspectParkingLot(Time inspectionTime);

        friend ostream& operator<<(ostream& os, const ParkingLot& parkingLot);

    private:
        pair<VehicleType,int> 
        tryFindSpotForHandicapped(LicensePlate licensePlate, Time entranceTime);

        void exitVehicleFromLot(LicensePlate licensePlate);

    };

}

#endif //MTMPARKINGLOT_PARKINGLOT_H
