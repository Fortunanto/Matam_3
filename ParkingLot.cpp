#include "ParkingLot.h"
#include "UniqueArray.h"
#include "ParkingLotPrinter.h"

using std::ostream;

using namespace ParkingLotUtils;
using namespace MtmParkingLot;

const int AMOUNT_OF_VEHICLE_TYPES = 3;

ParkingLot::ParkingLot(unsigned int parkingBlockSizes[]) {
    // todo: handle allocation exception?
    this->parkingLots = new UniqueArray<string>*[AMOUNT_OF_VEHICLE_TYPES];
    for (int i = 0; i < AMOUNT_OF_VEHICLE_TYPES; i++) {
        this->parkingLots[i] =  new UniqueArray<string>(parkingBlockSizes[i]);
    }
}

ParkingLot::~ParkingLot() {
    // todo: handle idk exceptions?
    for (int i = 0; i < AMOUNT_OF_VEHICLE_TYPES; i++) {
        delete parkingLots[i];

    }

    //todo: maybe delete map?
}

ParkingResult ParkingLot::enterParking(VehicleType vehicleType,
             LicensePlate licensePlate,
             Time entranceTime) {
    
    VehicleEntry entry(entranceTime,licensePlate);

    switch (vehicleType)
    {        
        case VehicleType::MOTORBIKE:
            this->parkingLots[VehicleType::MOTORBIKE]->insert(entry);
            break;    
        default:
            break;
        }


    return ParkingResult::SUCCESS;
}

ParkingResult ParkingLot::exitParking(LicensePlate licensePlate, Time exitTime){

    VehicleEntry leavingVehicle = this->parkedVehicles[licensePlate];
    ParkingLotPrinter::printVehicle(cout,
                                    leavingVehicle.getParkingSpot()
                                    .getParkingBlock(),
                                    licensePlate,
                                    leavingVehicle.getEntranceTime());

    ParkingLotPrinter::printExitSuccess(cout,
                                        leavingVehicle.getParkingSpot(),
                                        exitTime,5);

    return ParkingResult::SUCCESS;
}

ostream& operator<<(ostream& os, const ParkingLot& parkingLot){
    
    ParkingLotPrinter::printParkingLotTitle(os);
    

    return os;
}






