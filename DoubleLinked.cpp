#include "DoubleLinked.h"
#include <iostream>
#include <string>
#include <print>

//Purpose: This member function adds the moves from the file into the linked list, giving each node a move, a turn number, and a color.
//Inputs: The string move that is extracted from the file in main.
//Outputs: It is void returning, but each node in the linked list receives data.
void Game::push_back(std::string m){ 
    Node *temp = new Node;
    temp->move = m;
    temp->next = nullptr; 
    temp->previous = nullptr; 

    count++;
    if(count % 2 == 0){
        temp->color = "Black";
        temp->turn = turn;
    } else {
        turn++;
        temp->color = "White";
        temp->turn = turn;

    }
    if(head == nullptr){ // if the list is empty
        head = temp; // make the head point to the new node
        // make the tail point to the new node
        tail = temp;
        return; 
    }
    temp->previous = tail;
    tail->next = temp;
    tail = temp;
    // 1) the list isn't empty
    // 2) tail is the last node
    // 3) temp is the new one we want to make the last node

    // temp's previous needs to point to the tail
}


/*Purpose: This member function moves through the linked list, displaying the node's data for each move. This function also asks the user for a move. If the user enters
    a p and there is no previous node, then no previous move is output. But if there is a previous node, then that node's data is output. If the user enters n, then the
    next node's data is given, and if there is no next node then no next move is output along with the winning node. Lastly, if the user enters q, then the game ends with
    ending review output. 
Inputs: No inputs are given as parameters, however the function itself prompts the user for a move character.
Outputs: It is a void returning function, but for each move the node's data is displayed. */
void Game::move_thru(){

    //used color for my game, so these are their variables, as well as unicode for some emojis to display during the game
    std::string pinky{"\e[38;5;219m"};
    std::string minty{"\e[38;5;122m"};
    std::string cutie{"\e[38;5;212m"};
    std::string periwinkle{"\e[38;5;147m"};
    std::string flower{"\e[38;5;183m"};
    std::string teehee{"\e[38;5;87m"};
    std::string bluey{"\e[38;5;87m"};
    std::string rosy{"\U0001F339"};
    std::string tulip{"\U0001F337"};


    Node *current_move = new Node;
    current_move = head;
    
    char move;
    std::println(" ");
    std::cout << pinky << rosy << " ---Game Start--- " << rosy; //roses  are displayed as a welcome to the game
    std::cout << "\nTurn " << current_move->turn << ": " << current_move->color << " - " << current_move->move << '\n';
    while(move != 'q'){
        std::cout << bluey << "\nEnter n/p/q: ";
        std::cin >> move;
        if(move == 'p'){ 
            if(current_move->previous == nullptr){
                std::cout << minty << "No previous move.... " << "\U0001F940\n"; //wilting rose because it's sad that there's no previous move
            }
            if(current_move->previous != nullptr){
                current_move = current_move->previous;
                std::cout << flower << "Turn " << current_move->turn << ": " << current_move->color << " - " << current_move->move << '\n';
            }
        }
        if(move == 'n'){
            if(current_move->next == nullptr){
                std::cout << periwinkle << "No next move...\n";
                std::cout << "Game Ended with " << current_move->color << " Winning " << "\U0001F490\n "; //flower bouquet for the winning move!
            }
            if(current_move->next != nullptr){
                current_move = current_move->next; 
                std::cout << cutie << "Turn " << current_move->turn << ": " << current_move->color << " - " << current_move->move << '\n';
            }
        }
        if(move == 'q'){ 
            std::println("{}--- Ending Review ---\n", teehee);
            std::cout << pinky << tulip << " " << tulip << " " << tulip << "  \n"; //tulip garden to give the user a nice exit :)
            return;
        }
    }
}