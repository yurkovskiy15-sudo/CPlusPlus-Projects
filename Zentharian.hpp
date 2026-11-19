#ifndef ZENTHARIAN_HPP
#define ZENTHARIAN_HPP

const int kMaxFuelCrystals{20};

class Zentharian{
    int fuel[kMaxFuelCrystals]; //in order to access this array need to have a function inside the class
    int fuel_counter; //this counts how many lines of crystal is in the group
    int fuel_total; //this sums up all the lines of crystal
    int ID; //this will be the group's number

public:
    //default constructor, does nothing?
    Zentharian();
    //getters
    int get_fuel(int j) const;
    int get_fuel_counter() const;
    int get_fuel_total() const;
    int get_ID() const;
    //setters
    //void set
    void set_fuel(int value, int loc);
    void set_fuel_counter(int value);
    void set_fuel_total(int v);
    void set_ID(int id);
    bool operator <(Zentharian rhs); //implied that the lhs is calling it

};

#endif