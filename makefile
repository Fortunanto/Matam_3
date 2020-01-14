CC=g++
CXXFLAGS=-std=c++11 -Wall -Werror -pedantic-errors -DNDEBUG
PARKING_LOT_OBJS=MtmParkingLot.o  ParkingLot.o ParkingLotPrinter.o \
 ParkingSpot.o Time.o VehicleEntry.o

MtmParkingLot: MtmParkingLot.o  ParkingLot.o ParkingLotPrinter.o \
 ParkingSpot.o Time.o VehicleEntry.o
	$(CC) $(CXXFLAGS) $(PARKING_LOT_OBJS) -o $@
MtmParkingLot.o: MtmParkingLot.cpp ParkingLotTypes.h Time.h \
 ParkingLotPrinter.h ParkingSpot.h ParkingLot.h UniqueArray.h \
 UniqueArrayImp.h VehicleEntry.h
ParkingLot.o: ParkingLot.cpp ParkingLot.h ParkingLotTypes.h Time.h \
 ParkingSpot.h UniqueArray.h UniqueArrayImp.h VehicleEntry.h \
 ParkingLotPrinter.h
ParkingLotPrinter.o: ParkingLotPrinter.cpp ParkingLotPrinter.h Time.h \
 ParkingSpot.h ParkingLotTypes.h
ParkingSpot.o: ParkingSpot.cpp ParkingSpot.h ParkingLotTypes.h
Time.o: Time.cpp Time.h
VehicleEntry.o: VehicleEntry.cpp VehicleEntry.h Time.h ParkingLotTypes.h \
 ParkingSpot.h
clean: 
	rm -f *.o MtmParkingLot