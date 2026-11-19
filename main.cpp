/*
Gloria Silva
Project 7: Galactic Fuel w/Structures
Filename: main.cpp, Zentharian.cpp, Zentharian.hpp
CSCI 2170 002
Instructor: Robert Smith
Due Date: April 20th, 2026
Description: This program reads a file that has groups of crystals aka fuel, and each group is a Zentharian group. This program first checks if the file exists, then it
    gets an ID number for each group, converts each line of the file back into integers and stores them into the fuel array, and sums each group up into the fuel total.
    This program also has 3 functions, not including main, with one function finding the smallest fuel count, another for finding the largest, and lastly a third that 
    prints them out in a specially designed ledger along with the Zentharian group number with the smallest and largest fuel counts. This program also has 3 files, a main
    that calls member functions from the Zentharian class, an implementation file that has the class's member definitions that access and mutate the class's data, and
    lastly the header file with the class definition and member function prototypes. The member functions include a constructor, getters for all 4 data types of the class,
    and setters for them as well. And lastly an overloaded operator member function.
A.I. Disclaimer: All work for this assignment was completed by myself and entirely without the use of artificial intelligence tools such as ChatGPT, MS Copilot, other LLMs, etc.
*/



#include <iostream>
#include <fstream>
#include <string>
#include <print>
#include <cmath>
#include "Zentharian.hpp"

//my constants
const int kMaxZentharians{1000};
// const int kMaxFuelCrystals{20};
//my function prototypes
int find_max(Zentharian stu[], int count);
int find_min(Zentharian stu[], int count);
void print_ledger(Zentharian stu[], int max_loc, int min_loc);

//main begins
int main() {

    //get the filename
    std::cout << "Enter ledger file:";
    std::string filename;
    std::cin >> filename;

    //create and open the file object
    std::ifstream infile;
    infile.open(filename);

    //check if the file exists, and if not print out a message and end the program
    if(!infile){
        std::println("Invalid ledger file entered...{}!", filename);
        return 1;
    }

    //make the class itself into an array
    Zentharian zentharian[kMaxZentharians]; //the function would be outside of the class in order to access it , bc its in main
    int count{0}; //my variables
    std::string line;
    int counter{};

    //start off by trying to read the first line of the file as a string into the variable 'line'
    std::getline(infile, line);  
    while(infile){ //now we have the while loop as long as the file is okay
        counter = 0; //these variables must be reset to 0 everytime because they are unique to each group
        zentharian[count].set_fuel_counter(0); 
        zentharian[count].set_fuel_total (0); //something is being changed so it's a setter
        zentharian[count].set_ID(count + 1); //getting the group number 'ID'
    //while the line is not empty
        while(line != ""){
            // store the line as an integer in the fuel for that zentharian
            zentharian[count].set_fuel(std::stoi(line), counter); // get the location and store it so i can use it later
             //this converts the line back into integers and fills the fuel array
            counter++; 
            std::getline(infile, line);
            // increment the counter for fuel 
            // get the next line   
        }
    
        zentharian[count].set_fuel_counter(counter);
        // store the counter for my fuel in my fuel_counter
        //i is inside and count is outside
        //counter is inside 
        count++; //the count moves us to the next spot in the structure array
        if(infile && line == ""){
            std::getline(infile, line);
        } //skips the empty line in the file
    }

    //calling my functions
    int max_loc = find_max(zentharian, count); 
    int min_loc = find_min(zentharian, count); 
    print_ledger(zentharian, max_loc, min_loc); 

    //close the file
    infile.close();

    //end main
    return 0;
}


//Purpose: This function finds the group with the greatest fuel total, and prints it out along with the count and ID numbers.
//Inputs: The structure array and count.
//Outputs: the group with the greatest fuel total is found and printed out along with the ID and count. Maxiumum location is returned.
int find_max(Zentharian stu[], int count){
    int max_loc{0};
    for(int i{0}; i < count; ++i){
        if(stu[max_loc] < stu[i]){ //overloaded operator is used here
            max_loc = i;
        }
    } 
    std::println("\nZentharian {} has the  most - {} crystals worth {} units.", stu[max_loc].get_ID(), stu[max_loc].get_fuel_counter(), stu[max_loc].get_fuel_total());
    return max_loc;
}

//Purpose: This function finds the group with the least fuel total, and prints it out along with the count and ID numbers.
//Inputs: The structure array and count.
//Outputs: the group with the least fuel total is found and printed out along with the ID and count. Minimum location is returned.
int find_min(Zentharian stu[], int count){  
    int min_loc{0};
    for(int i{0}; i < count; ++i){
        if(stu[min_loc].get_fuel_total() > stu[i].get_fuel_total()){ //using getters bc nothing is changing
            min_loc = i;
        } //not changing the class's private info
    } //also bc its an array
    std::println("Zentharian {} has the least - {} crystals worth {} units.", stu[min_loc].get_ID(), stu[min_loc].get_fuel_counter(), stu[min_loc].get_fuel_total());
    return min_loc;
}

//Purpose: This function prints out a nicely designed ledger, with each line of the smallest and largest groups in two different columns.
//Inputs: The structure array, the maximum and minimum locations.
//Outputs: The smallest and largest groups crystals printed out line by line into two separate columns on a designed ledger. 
void print_ledger(Zentharian stu[], int max_loc, int min_loc){
    std::println("\n|- Smallest -|- Largest -|");
    for(int j{0}; j < stu[max_loc].get_fuel_counter(); ++j){
        if(j < stu[min_loc].get_fuel_counter()){
            std::print("|{:>10}  ", stu[min_loc].get_fuel(j)); 
        } else {
            std::print("|            ");
        }   
        std::println("|{:>10} |", stu[max_loc].get_fuel(j));   
    } 
    std::println("|------------|-----------|");
}
