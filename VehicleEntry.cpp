#include "VehicleEntry.h"

const int BIKE_FIRST_HOUR_PRICE = 10;
const int BIKE_ADDITIONAL_HOURS_PRICE = 5;

const int CAR_FIRST_HOUR_PRICE = 20;
const int CAR_ADDITIONAL_HOURS_PRICE = 10;

const int HANDICAPPED_FEE = 15;

const int MAX_HOURS_PAYMENT = 6;

using namespace MtmParkingLot;



// -------------- payment calculations -----------------

int calcFeeByTime(Time parkTime, int firstHourFee, int additionalHoursFee){
    int hours = parkTime.toHours();
    
    if (hours == 0){
        return 0;
    }

    if (hours > MAX_HOURS_PAYMENT){
        hours = MAX_HOURS_PAYMENT;
    }

    hours--;

    return firstHourFee + (additionalHoursFee * hours);    
}

// ----------------- implementations -------------------------------

int VehicleEntry::calculateTotalFee(Time exitTime) const{
    int totalFee = 0;

    Time timeInParking = exitTime-this->entranceTime;

    switch (this->getVehicleType())
    {
        case VehicleType::MOTORBIKE:
            totalFee+=calcFeeByTime(timeInParking,
                                    BIKE_FIRST_HOUR_PRICE,
                                    BIKE_ADDITIONAL_HOURS_PRICE);
            break;
        case VehicleType::CAR:
            totalFee += calcFeeByTime(timeInParking,
                                    CAR_FIRST_HOUR_PRICE,
                                    CAR_ADDITIONAL_HOURS_PRICE);
            break;
        case VehicleType::HANDICAPPED:
            totalFee += 15;
            break;    
        default:
            break;
    }

    return totalFee + this->penalty;
}

bool operator< (const VehicleEntry& ve1, const VehicleEntry& ve2) {
    return ve1.getParkingSpot()<ve2.getParkingSpot();
}