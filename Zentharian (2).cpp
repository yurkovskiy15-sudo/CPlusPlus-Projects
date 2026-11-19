#include "Zentharian.hpp"
#include <print>

//Purpose: sets up the object so that it's ready to use
//Inputs: no parameters
//Outputs: initializes member variables
Zentharian::Zentharian(){
    //default constructor
}

//getters-
//Purpose: to acces the private fuel array
//Inputs: an integer that will be the location for the array
//Outputs: the fuel array at a specific location
int Zentharian::get_fuel(int j) const{   //needs a parameter bc this is an array, not one value like the others
    return fuel[j]; //is this how you can return an array
}

//Purpose: to access the private fuel counter
//Inputs: no parameters
//Outputs: the fuel counter is returned
int Zentharian::get_fuel_counter() const{
    return fuel_counter;
}

//Purpose: to access the private fuel total
//Inputs: no parameters
//Outputs: the fuel total is returned
int Zentharian::get_fuel_total() const{
    return fuel_total;
}

//Purpose: to access the private ID
//Inputs: no parameters
//Outputs: the ID is returned
int Zentharian::get_ID() const{
    return ID;
}

//setters-
//Purpose: this function stores a value at a specific location within the fuel array, and also adds the value to the fuel total
//Inputs: an integer value and an integer location for the fuel array
//Outputs: void function, so nothing is returned but the fuel array and fuel total are both 'mutated'
void Zentharian::set_fuel(int value, int loc){
    fuel[loc] = value;  //where are you storing the value in the array, location
    fuel_total += value;// add the value to my fuel total
    //fueltotal += value
}

//Purpose: this function sets the fuel counter to the given value
//Inputs: the integer value
//Outputs: the fuel counter is mutated
void Zentharian::set_fuel_counter(int value){
    fuel_counter = value;
}

//Purpose: this function sets the fuel total to the given value
//Inputs: the integer v
//Outputs: the fuel total is mutated
void Zentharian::set_fuel_total(int v){
    fuel_total = v;
}

//Purpose: this function sets the ID to the given value
//Inputs: the integer id
//Outputs: the ID is mutated
void Zentharian::set_ID(int id){
    ID = id;
}

//overloaded operator
//Purpose: this function overloads the < operator to see if the fuel total on the left side of the operator is less than the fuel total on the right side of the operator
//Inputs: the class Zentharian as the right hand side
//Outputs: true or false is returned 
bool Zentharian::operator <( Zentharian rhs){
    return get_fuel_total() < rhs.get_fuel_total();
} //this returns true or false


