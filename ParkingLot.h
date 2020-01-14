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

    UniqueArray<string> parkingLots[VehicleType::LAST+1]; //todo: change to const or smthing

    map<LicensePlate,VehicleEntry> parkedVehicles;

    public:
        ParkingLot(unsigned int parkingBlockSizes[]):parkingLots{
            UniqueArray<string>(parkingBlockSizes[VehicleType::MOTORBIKE]),
            UniqueArray<string>(parkingBlockSizes[VehicleType::HANDICAPPED]),
            UniqueArray<string>(parkingBlockSizes[VehicleType::CAR])
        }{}
        ParkingResult enterParking(VehicleType vehicleType,
                LicensePlate licensePlate, Time entranceTime);

        ParkingResult exitParking(LicensePlate licensePlate, Time exitTime);

        ParkingResult getParkingSpot(LicensePlate licensePlate,
                ParkingSpot& parkingSpot) const;
        
        map<LicensePlate,VehicleEntry> getParkedVehicles() const {
            return this->parkedVehicles;
        }

        void inspectParkingLot(Time inspectionTime);

        friend ostream& operator<<(ostream& os, ParkingLot const& parkingLot);

    private:
        /**
         * Tries to find a spot for a handicapped vehicle.
         * Will first try to park in the handicapped block,
         * if no place is available there will try to park in the cars block.
         * @param licensePlate
         * @param entranceTime
         * @return A pair where the first member is the block that the handicapped has parked in.
         *         The second member is the number in that block.
         *
         *         The second member value will be FAILED_TO_INSERT_TO_UNIQUE_ARRAY if no parking was available at all.
         */
        pair<VehicleType,int> 
        tryFindSpotForHandicapped(LicensePlate licensePlate, Time entranceTime);
        
        /**
         * Tries to insert a vehicle to the lot.
         *   
         * @return A pair where the first member is the block that the handicapped has parked in.
         *         The second member is the number in that block.
         *
         *         The second member value will be FAILED_TO_INSERT_TO_UNIQUE_ARRAY if no parking was available at all.
         */
        pair<VehicleType,int> tryInsertToParkingLot(VehicleType vehicleType,
                LicensePlate licensePlate,
                Time entranceTime);

        /**
         * Physically removes a vehicle from the parking lot.
         *
         * @param licensePlate
         */
        void exitVehicleFromLot(LicensePlate licensePlate);

    };

}

#endif //MTMPARKINGLOT_PARKINGLOT_H
