/*
Gloria Silva
Project 8: Chess is Double the Fun
Filename: gametracker.cpp, DoubleLinked.cpp, DoubleLinked.h
CSCI 2170 002
Instructor: Robert Smith
Due Date: April 29th, 2026
Description: This program works with 3 files. In the main file, the user is asked for a file and outputs an error message if there is none. If one successfully opens,
    then each move from the file is extracted and two member functions from the class are called. Within the implementation file, we have 2 functions. Pushback adds to
    the linked list the moves from the file and then assigns the color and turn number for each node. The movethru function is what displays each move to the terminal.
    Finally, within the header file I have the linked list class and node structure defined.
A.I. Disclaimer: All work for this assignment was completed by myself and entirely without the use of artificial intelligence tools such as ChatGPT, MS Copilot, other LLMs, etc.
*/


#include <iostream>
#include <print>
#include <string>
#include <fstream>
#include "DoubleLinked.h"


int main(){

    //used color and unicode emojis to decorate my terminal
    std::string pinky{"\e[38;5;219m"};
    std::string cherry_blossom{"\U0001F338"};
    std::string sad_rose{"\U0001F940"};

    std::cout << cherry_blossom << pinky << " Enter a game to review" <<  cherry_blossom << " :"; //cherry blossoms to welcome the user to the terminal
    std::string filename;
    std::cin >> filename;

    std::ifstream infile;
    infile.open(filename);

    if(!infile){
        std::println("\n{} {} ERROR: {} could not be opened... {}", sad_rose, pinky, filename, sad_rose); //wilting rose if game couldn't start bc no file 
        return 1;
    }

    Game game;

    std::string move;


    infile >> move;
    while(infile){
        game.push_back(move); 
        infile >> move;
    }


    game.move_thru();




    return 0;
}

