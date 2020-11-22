class ParkingSystem {
    vector<int> space;
public:
    ParkingSystem(int big, int medium, int small):space{{big,medium,small}} {
    }
    
    bool addCar(int carType) {
        carType--;
        space[carType] -= 1;
        return space[carType] >= 0;
    }
};

