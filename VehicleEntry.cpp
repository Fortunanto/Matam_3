#include "VehicleEntry.h"

const int BIKE_FIRST_HOUR_PRICE = 10;
const int BIKE_ADDITIONAL_HOURS_PRICE = 5;

const int CAR_FIRST_HOUR_PRICE = 20;
const int CAR_ADDITIONAL_HOURS_PRICE = 10;

const int MAX_HOURS_PAYMENT = 6;

using namespace MtmParkingLot;

int VehicleEntry::calculateTotalFee(Time exitTime){
    int totalFee = 0;


}



// -------------- payment calculations -----------------
int calcFeeByHours(int hours, int firstHourFee, int additionalHoursFee){
    if (hours == 0){
        return 0;
    }

    if (hours > MAX_HOURS_PAYMENT){
        hours = MAX_HOURS_PAYMENT;
    }

    hours--;

    return firstHourFee + (additionalHoursFee * hours);    
}


int calcBikePayment(Time entranceTime, Time exitTime){
    Time timeInParking = exitTime-entranceTime;
    if (timeInParking.toHours()==1){
        return 
    }
}