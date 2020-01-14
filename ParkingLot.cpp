#include "ParkingLot.h"
#include "UniqueArray.h"
#include "ParkingLotPrinter.h"
#include <vector>
#include <algorithm>

using std::ostream;

using namespace ParkingLotUtils;

namespace MtmParkingLot {

    const int AMOUNT_OF_VEHICLE_TYPES = 3;

    const int FAILED_TO_INSERT_TO_UNIQUE_ARRAY = -1;
    const int FAILED_TO_FIND_SPOT = -1;

    const int PENALTY_HOUR_LIMIT = 24;
    const int PENALTY_FEE = 250;

    // ----------------- helper funcs ----------------------------

    /**
     * Tries to insert an element of type string to UniqueArray.
     * @param arr
     * @param licensePlate
     * @return If insertion was successful -The index in the array the element was inserted to.
     *         Otherwise, returns FAILED_TO_INSERT_TO_UNIQUE_ARRAY.
     */
    int tryInsertToUniqueArray(UniqueArray<string>& arr,
                            LicensePlate licensePlate){
        try {
            return (int)(arr.insert(licensePlate));
            }
            catch (UniqueArray<string>::UniqueArrayIsFullException& e){           
                return FAILED_TO_INSERT_TO_UNIQUE_ARRAY;
            }
    }

    /**
     * Print a message to the console that notes that a park attempt had failed.
     * @param vehicleType - The type of the vehicle tries to parking.
     * @param licensePlate
     * @param entranceTime - The time in which the vehicle is trying to park.
     */
    void printParkFailure(VehicleType vehicleType, LicensePlate licensePlate,
                            Time entranceTime){
        ParkingLotPrinter::printVehicle(cout,vehicleType,licensePlate,entranceTime);
        ParkingLotPrinter::printEntryFailureNoSpot(cout);
    }

    /**
     * Print a message to the console that notes that a park attempt was successful.
     * @param vehicleType - The type of the vehicle.
     * @param licensePlate
     * @param entranceTime - The time of parking in the lot.
     * @param parkingSpot - The spot in which the vehicle had parked.
     */
    void printParkSuccess(VehicleType vehicleType, LicensePlate licensePlate,
                            Time entranceTime,ParkingSpot parkingSpot){
        ParkingLotPrinter::printVehicle(cout,vehicleType,licensePlate,entranceTime);        
        ParkingLotPrinter::printEntrySuccess(cout,parkingSpot);   
    }

    /**
     * Print a message to the console that notes that a vehicle is already in the lot.
     * @param entry - The data of the vehicle that is already in the lot.
     */
    void printAlreadyParked(VehicleEntry entry){
        ParkingLotPrinter::printVehicle(cout,entry.getVehicleType(),entry.getLicensePlate(),entry.getEntranceTime());
        ParkingLotPrinter::printEntryFailureAlreadyParked(cout,entry.getParkingSpot());        
    }

    /**
     * Gets a sorted vector of all the entries given as values of a map of <string,VehicleEntry>.
     * @param inputMap - A map of vehicle entries.
     * @return The sorted VehicleEntry vector.
     */
    vector<VehicleEntry>
    getSortedVectorOfVehicleEntries(map<string,VehicleEntry> inputMap){
        vector<VehicleEntry> resultVec;

        for(map<string,VehicleEntry>::iterator it = inputMap.begin();
                it != inputMap.end(); ++it ) {
            resultVec.push_back( it->second );
        }

        std::sort(resultVec.begin(),resultVec.end());

        return resultVec;
    } 

    // ---------- implementation - helper funcs -----------------

    pair<VehicleType,int> ParkingLot::
    tryFindSpotForHandicapped(LicensePlate licensePlate, Time entranceTime){
        int blockInLot;

        blockInLot =
            tryInsertToUniqueArray(this->parkingLots[VehicleType::HANDICAPPED],
                                    licensePlate);

        if (blockInLot != FAILED_TO_INSERT_TO_UNIQUE_ARRAY){
            return make_pair(VehicleType::HANDICAPPED,blockInLot);
        }

        blockInLot =
            tryInsertToUniqueArray(this->parkingLots[VehicleType::CAR],
                                    licensePlate);

        if (blockInLot != FAILED_TO_INSERT_TO_UNIQUE_ARRAY){
            return make_pair(VehicleType::CAR,blockInLot);
        }

        return make_pair(VehicleType::HANDICAPPED,
                                    FAILED_TO_INSERT_TO_UNIQUE_ARRAY);
    }


    /**
     * Tries to insert a vehicle to the lot.
     *   
     * @return A pair where the first member is the block that the handicapped has parked in.
     *         The second member is the number in that block.
     *
     *         The second member value will be FAILED_TO_INSERT_TO_UNIQUE_ARRAY if no parking was available at all.
     */
    pair<VehicleType,int> ParkingLot::tryInsertToParkingLot(
                VehicleType vehicleType,
                LicensePlate licensePlate,
                Time entranceTime){
        if (vehicleType == VehicleType::HANDICAPPED){
            return this->tryFindSpotForHandicapped(licensePlate,entranceTime);             
        }
        
        return
            make_pair(vehicleType,
            tryInsertToUniqueArray(this->
                    parkingLots[vehicleType],licensePlate));
    
    }

    void ParkingLot::exitVehicleFromLot(LicensePlate licensePlate){
        ParkingSpot vehicleSpot = this->parkedVehicles.at(licensePlate)
                                                    .getParkingSpot();

        this->parkingLots[vehicleSpot.getParkingBlock()].remove(licensePlate);
        this->parkedVehicles.erase(licensePlate);
    }
    
    // ---------- implementation ----------------------------

    ParkingResult ParkingLot::enterParking(VehicleType vehicleType,
                LicensePlate licensePlate,
                Time entranceTime) {    
        VehicleType parkingBlock;
        int numberInLot;

        if (this->parkedVehicles.count(licensePlate)>0){
            printAlreadyParked(this->parkedVehicles.at(licensePlate));
            return ParkingResult::VEHICLE_ALREADY_PARKED;
        }
        
        tie(parkingBlock,numberInLot) = tryInsertToParkingLot(vehicleType,
            licensePlate, entranceTime);

        if (numberInLot == FAILED_TO_INSERT_TO_UNIQUE_ARRAY){
            printParkFailure(vehicleType,licensePlate,entranceTime);
            return ParkingResult::NO_EMPTY_SPOT;
        }

        ParkingSpot newSpot(parkingBlock,numberInLot);
        printParkSuccess(vehicleType,licensePlate,entranceTime,newSpot);

        VehicleEntry entry(entranceTime,licensePlate,parkingBlock,numberInLot,
            vehicleType);
        
        this->parkedVehicles.insert({licensePlate,entry});

        return ParkingResult::SUCCESS;
    }

    ParkingResult ParkingLot::exitParking(LicensePlate licensePlate,
         Time exitTime){  

        // if the vehicle doesnt exist
        if (this->parkedVehicles.count(licensePlate) == 0){ 
            ParkingLotPrinter::printExitFailure(cout,licensePlate);
            return ParkingResult::VEHICLE_NOT_FOUND;
        }

        VehicleEntry leavingVehicle = this->parkedVehicles[licensePlate];

        ParkingLotPrinter::printVehicle(cout,
                                        leavingVehicle.getVehicleType(),
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
            parkingSpot = this->parkedVehicles.at(licensePlate)
                                                .getParkingSpot();
            return ParkingResult::SUCCESS;
        }
        catch(const std::out_of_range&){
            return ParkingResult::VEHICLE_NOT_FOUND;
        }
    }

    void ParkingLot::inspectParkingLot(Time inspectionTime){
        int numFined=0;

        for (auto & parkedVehiclePair : this->parkedVehicles)
        {            
            VehicleEntry& entry = parkedVehiclePair.second;

            Time timediff = inspectionTime - entry.getEntranceTime();

            if (timediff.toHours()>PENALTY_HOUR_LIMIT && entry.getPenalty()==0){
                entry.addPenalty(PENALTY_FEE);
                numFined++;
            }
        }

        ParkingLotPrinter::printInspectionResult(cout,inspectionTime,numFined);
    }

    ostream& operator<<(ostream& os, ParkingLot const& parkingLot){
        
        ParkingLotPrinter::printParkingLotTitle(os);
        
        vector<VehicleEntry> sortedEntries 
            = getSortedVectorOfVehicleEntries(parkingLot.getParkedVehicles());
        
        for(const auto& entry: sortedEntries) {       
            ParkingLotPrinter::printVehicle(os,entry.getVehicleType(),
            entry.getLicensePlate(), entry.getEntranceTime());

            ParkingLotPrinter::printParkingSpot(os,entry.getParkingSpot());
        }

        return os;
    }
}





