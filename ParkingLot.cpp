#include "ParkingLot.h"
#include "UniqueArray.h"
#include "ParkingLotPrinter.h"

using std::ostream;

using namespace ParkingLotUtils;
using namespace MtmParkingLot;

const int AMOUNT_OF_VEHICLE_TYPES = 3;

const int FAILED_TO_INSERT_TO_UNIQUE_ARRAY = -1;
const int FAILED_TO_FIND_SPOT_FOR_HANDICAPPED = -1;

const int PENALTY_HOUR_LIMIT = 24;
const int PENALTY_FEE = 250;

// ----------------- helper funcs ----------------------------

int tryInsertToUniqueArray(UniqueArray<string>& arr,
                           LicensePlate licensePlate){
    try {
           return (int)(arr.insert(licensePlate));
        }
        catch (UniqueArray<string>::UniqueArrayIsFullException& e){           
            return FAILED_TO_INSERT_TO_UNIQUE_ARRAY;
        }
}

void printParkFailure(VehicleType vehicleType, LicensePlate licensePlate,
                        Time entranceTime){
                            // todo: maybe add endl?
    ParkingLotPrinter::printVehicle(cout,vehicleType,licensePlate,entranceTime);
    cout << " , ";
    ParkingLotPrinter::printEntryFailureNoSpot(cout);
}

void printParkSuccess(VehicleType vehicleType, LicensePlate licensePlate,
                        Time entranceTime,ParkingSpot parkingSpot){
    ParkingLotPrinter::printVehicle(cout,vehicleType,licensePlate,entranceTime);
    cout << " , ";
    ParkingLotPrinter::printParkingSpot(cout,parkingSpot);
}

// ---------- implementation - helper funcs -----------------

pair<VehicleType,int> ParkingLot::
    tryFindSpotForHandicapped(LicensePlate licensePlate, Time entranceTime){
    int blockInLot;

    blockInLot =
         tryInsertToUniqueArray(*this->parkingLots[VehicleType::HANDICAPPED],
                                licensePlate);

    if (blockInLot != FAILED_TO_INSERT_TO_UNIQUE_ARRAY){
        return make_pair(VehicleType::HANDICAPPED,blockInLot);
    }

    blockInLot =
         tryInsertToUniqueArray(*this->parkingLots[VehicleType::CAR],
                                licensePlate);

    if (blockInLot != FAILED_TO_INSERT_TO_UNIQUE_ARRAY){
        return make_pair(VehicleType::CAR,blockInLot);
    }

    return make_pair(VehicleType::HANDICAPPED,
                                 FAILED_TO_FIND_SPOT_FOR_HANDICAPPED);
}

void ParkingLot::exitVehicleFromLot(LicensePlate licensePlate){
    ParkingSpot vehicleSpot = this->parkedVehicles.at(licensePlate)
                                                  ->getParkingSpot();

    this->parkingLots[vehicleSpot.getParkingBlock()]->remove(licensePlate);
    this->parkedVehicles.erase(licensePlate);
}

// ---------- implementation ----------------------------

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
    VehicleType parkingBlock;
    int numberInLot;

    if (vehicleType == VehicleType::HANDICAPPED){
        tie(parkingBlock,numberInLot) = 
            this->tryFindSpotForHandicapped(licensePlate,entranceTime);             
    }
    else {
        numberInLot = 
            tryInsertToUniqueArray(*this->parkingLots[vehicleType],
                                   licensePlate);
        parkingBlock = vehicleType;
    }

    if (numberInLot == FAILED_TO_FIND_SPOT_FOR_HANDICAPPED ||
        numberInLot == FAILED_TO_INSERT_TO_UNIQUE_ARRAY){
        printParkFailure(vehicleType,licensePlate,entranceTime);
        return ParkingResult::NO_EMPTY_SPOT;
    }

    ParkingSpot newSpot(parkingBlock,numberInLot);
    printParkSuccess(vehicleType,licensePlate,entranceTime,newSpot);

    VehicleEntry* entry = 
        new VehicleEntry(entranceTime,licensePlate,parkingBlock,numberInLot,
        vehicleType);
    this->parkedVehicles[licensePlate] = entry;

    return ParkingResult::SUCCESS;
}

ParkingResult ParkingLot::exitParking(LicensePlate licensePlate, Time exitTime){  

    // if the vehicle doesnt exist
    if (this->parkedVehicles.count(licensePlate) == 0){ 
        ParkingLotPrinter::printExitFailure(cout,licensePlate);
        return ParkingResult::VEHICLE_NOT_FOUND;
    }

    VehicleEntry leavingVehicle = *this->parkedVehicles[licensePlate];

    ParkingLotPrinter::printVehicle(cout,
                                    leavingVehicle.getParkingSpot()
                                    .getParkingBlock(),
                                    licensePlate,
                                    leavingVehicle.getEntranceTime());

    ParkingLotPrinter::printExitSuccess(cout,
                                        leavingVehicle.getParkingSpot(),
                                        exitTime,
                                        leavingVehicle.
                                        calculateTotalFee(exitTime));   

    this->exitVehicleFromLot(licensePlate);

    return ParkingResult::SUCCESS;
}

ParkingResult ParkingLot::getParkingSpot(LicensePlate licensePlate,
                ParkingSpot& parkingSpot) const{
    try{        
        parkingSpot = this->parkedVehicles.at(licensePlate)->getParkingSpot();
        return ParkingResult::SUCCESS;
    }
    catch(const std::out_of_range&){
        return ParkingResult::VEHICLE_NOT_FOUND;
    }
}

void ParkingLot::inspectParkingLot(Time inspectionTime){
    for (auto const& parkedVehiclePair : this->parkedVehicles)
    {
        LicensePlate licensePlate = parkedVehiclePair.first;
        VehicleEntry entry = *parkedVehiclePair.second;

        Time timediff = inspectionTime - entry.getEntranceTime();

        if (timediff.toHours()>PENALTY_HOUR_LIMIT){
            entry.addPenalty(PENALTY_FEE);
        }
    }
}

ostream& operator<<(ostream& os, const ParkingLot& parkingLot){
    
    ParkingLotPrinter::printParkingLotTitle(os);
    

    return os;
}






