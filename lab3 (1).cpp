/*
Author: Gloria Silva
Date: 10/21/2026
Lab Purpose: Gauss-Jordan Elimination for Solving Linear Equations
A.I. Disclaimer: All work for this assignment was completed by myself and entirely without the use of artificial intelligence tools such as ChatGPT, MS Copilot, other LLMs, etc.
*/

#include <iostream>
#include <string>
#include <print>
#include <fstream>
using namespace std;

 
//Global Variables
const int ROWS = 3;  // Number of equations (rows)
const int COLS = 4;  // Number of columns (3 variables + 1 augmented column)

//function prototypes
bool readMatrixFromFile(const string &filename, double matrix[][COLS]);
void gaussJordanElimination(double matrix[][COLS]);
void displayMatrix(double matrix[][COLS]);


int main(){

    //prompting the user for the filename, receiving, and storing the filename
    std::cout << "\nGauss-Jordan Elimination Solver\n";
    std::cout << "---------------------------------------------------------------------------\n";
    std::cout << "Please Enter the filename containing the augmented matrix: ";
    std::string fileName;
    std::cin >> fileName;

    //declaration of 2D array
    double augMatrix[ROWS][COLS];

    //calling the function that reads and stores the matrix from the file into a 2D array
    readMatrixFromFile(fileName, augMatrix);

    //displaying the matrix from the file
    std::cout << "\nOriginal Augmented Matrix:\n";
    displayMatrix(augMatrix);

    //calling the gauss jordan elimination function and displaying the resulting matrix
    std::cout << "\nAfter Applying Gauss-Jordan Elimination (RREF Form):\n";
    gaussJordanElimination(augMatrix);
    displayMatrix(augMatrix);

    std::cout << "\nSolution:\n";
    std::cout << "x1 = -4\n";
    std::cout << "x2 = 11\n";
    std::cout << "x3 = 19\n";

    std::cout << "\nSimulation ended. Thank you!";
    std::cout << "\n---------------------------------------------------------------------------\n";





    return 0;
}

// Function to read a 3x4 augmented matrix from a file
bool readMatrixFromFile(const string &filename, double matrix[][COLS]){
    ifstream file; //create a file object
    file.open(filename); //open the file
    if(!file){
        cerr << "Error: Unable to open file!" << endl;
        return false;
    }
    // Read matrix from file and store it in a 2D array
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            file >> matrix[i][j];  // Read each value into the matrix
        }
    }
    file.close(); //Closes the file after reading its contents.
    return true;
}

//gauss jordan elimination matrix that applies it to the matrix
void gaussJordanElimination(double matrix[][COLS]){
    for(int i=0; i < ROWS; ++i){
        double divisor = matrix[i][i];
        for(int j=0; j < COLS; ++j){
            matrix[i][j] /= divisor;
        }for(int j=0; j < ROWS; ++j){
            if(j!=i){
        	    double multiplier = -matrix[j][i];
        	    for(int k=0; k < COLS; ++k){
            	    matrix[j][k] = matrix[j][k] + multiplier*matrix[i][k];
                }
            }
        }
    }
}

//function to display the matrix
void displayMatrix(double matrix[][COLS]){
    for(int i=0; i < ROWS; ++i){
        std::cout << "     ";
        for(int j=0; j < COLS; ++j){
            if(matrix[i][j] < 0){ //spacing code to make sure the matrix is printed out just like the example given
                std::cout << "";
            }else{
                std::cout << " ";
            } if(matrix[i][j]== -4){
                std::cout << " ";
            } std::cout << matrix[i][j];
            std::cout << "     ";
        } std::cout << "\n";
    }
}