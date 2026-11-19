/*Gloria Silva
Project 5: Nebula Forge Works
Program Description: this program asks the user for 2 files, and keeps asking until the file is opened successfully. Then, it has 3 
    functions that fill arrays in order to find the material and product amounts, material costs, material per product, product names, and
    final cost. Finally, it outputs it in an organized table.
A.I. Disclaimer: All work for this assignment was completed by myself and entirely without the use of artificial intelligence tools such as ChatGPT, MS Copilot, other LLMs, etc.*/

#include <iostream>
#include <print>
#include <string>
#include <fstream>

//constants
const int kMaxMaterials {20};
const int kMaxProducts {15}; 

//prototypes
void fill2_print2(std::ifstream& ifile, double mcost[], int mpp[][kMaxProducts], int mnum, int pnum);
void fill_print_names(std::ifstream& afile, std::string names[], int pnum);
void final_cost(double mcost[], int mpp[][kMaxProducts], int pnum, int mnum, double finall_cost[]); 


int main(){

    //get the 1st file name
    std::cout << "Enter the materials filename: ";
    std::string mfname;
    std::cin >> mfname;

    //create and open file 1
    std::ifstream ifile;
    ifile.open(mfname);

    //loop until first file opens successfully
    while(!ifile){
        std::println("File open error.");              
        std::print("Enter the materials filename: ");
        std::cin >> mfname;
        ifile.open(mfname);
    } 
        std::println("File Open Successfully.");

    
    //create and get the 2nd file
    std::ifstream afile;
    std::cout << "Enter the products filename: ";
    std::string pfname;
    std::cin >> pfname;

    
    //open 2nd file
    afile.open(pfname);
    

    //loop until 2nd file opens successfully
    while(!afile){
        std::println("File open error.");
        std::print("Enter the products filename: ");
        std::cin >> pfname;
        afile.open(pfname);
    } std::println("File Open Successfully.");
    

    //variables
    double mcost[kMaxMaterials];
    int mpp[kMaxMaterials][kMaxProducts];
    int pnum {};
    int mnum {};
    std::string names[kMaxProducts];
    double finall_cost[kMaxProducts];

    
    ifile >> pnum;
    ifile >> mnum;      //putting these outside the loop bc theres only two of them to extract
    
    //function calls
    fill2_print2(ifile, mcost, mpp, mnum, pnum);   //getting the 2 arrays from this one, to the final cost one for the multiplication
    fill_print_names(afile, names, pnum); //we can use variables from main
    final_cost(mcost, mpp, pnum, mnum, finall_cost);

   
    //printing the table...
    std::println(" ");
    
    std::println("--- Nebula Forge Works Product Table ---");
    for(int i {0}; i < (36 + (mnum * 6)); i++){
        std::print("*");
    }

    std::println(" ");
    
    std::print("{:<21}", "Product"); 
    for(int j {1}; j <= mnum; j++){
        std::print("Mat{:<3}", j);
    } std::print("    Price");

    std::println(" ");
    
    for(int i {0}; i < (36 + (mnum * 6)); i++){
        std::print("-");
    } std::println(" ");
    
    for(int i {0}; i < pnum; i++){
        std::print("{:>2} {:<18} ", (i + 1), names[i]);
        for(int j {0}; j < mnum; j++){
            std::print("{:<6}", mpp[j][i]);
        } std::println("   ${:>7.2f}", finall_cost[i]);
    } 
    
    
    int max {0};
    //int i {0};
    for(int i {0}; i < pnum; i++){
        if(finall_cost[i] > finall_cost[max]){
            max = i;
        }
    } std::println(" ");
    std::cout << "Product " << (max + 1) << ": " << names[max] << " is the most expensive product" << "\n";


    //close files
    ifile.close();
    afile.close();


    return 0;

}
 

//Purpose: this function fills 2 arrays, the material cost and the 2d material per product.
//Inputs: the material file, the empty material cost array, the empty material per product array, and material number and product number.
//Outputs: the material cost and per product arrays filled.
void fill2_print2(std::ifstream& ifile, double mcost[], int mpp[][kMaxProducts], int mnum, int pnum){
    for(int row = 0; row < mnum; row++){
        ifile >> mcost[row];                   
        for(int col = 0; col < pnum; ++col){      
            ifile >> mpp[row][col];
        } 
    }
}

   

//Purpose: fills the string names array.
//Inputs: products file, empty string names array, and product number.
//Outputs: a filled string array called names.
void fill_print_names(std::ifstream& afile, std::string names[], int pnum){
    for(int i = 0; i < pnum; i++){
        std::getline(afile , names[i]);                    
    }
}



 
//Purpose: fills the finall_cost array by multiplying the material cost and material per product arrays.
//Inputs: material cost array, material per product array, product number, material number, and an empty finall_cost array.
//Outputs: a filled finall_cost array.
void final_cost(double mcost[], int mpp[][kMaxProducts], int pnum, int mnum, double finall_cost[]){
    for(int j {0}; j < mnum; j++){
        for(int i {0}; i < pnum; i++){
            finall_cost[i] += mcost[j] * mpp[j][i];
        }
    }       
}


