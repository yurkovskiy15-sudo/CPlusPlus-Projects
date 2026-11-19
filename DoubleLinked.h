#ifndef DOUBLE_LINKED_H
#define DOUBLE_LINKED_H
#include <string>



class Game{
public:
    struct Node{
        std::string move;
        std::string color;
        Node *next;
        Node *previous;
        int turn;
    };

private:    
    Node *head;
    Node *tail;
    int turn;
    int count;
    //add count and turn
    
public:


    
    Game() {  
        head = nullptr;
        tail = nullptr;
        turn = 0;
        count = 0;
    }


    void push_back(std::string m);

    void move_thru();




};





#endif