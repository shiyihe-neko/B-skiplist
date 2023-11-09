#include <iostream>
#include <vector>
#include <random>
#include<time.h> 

class Block;

class Node {
public:
    int value;
    Block* down; // Pointer to lower level block contains same value
    Node(int value, Block* down){
        this->value= value;
        this->down = down;
    }
};

class Block {
public:
    std::vector<Node*> vector; 
    Block* next; // Pointer to the next block at the same level
    Block(int value, Block* next){
        Node* node = new Node(value,nullptr);
        vector.push_back(node);
        //vector.resize(3); // minimum size of each block
        this->next = next;
    }

    void print(){
        for (unsigned int i = 0; i < vector.size(); i++){
            // if(vector[i])
            //     std::cout << vector[i]->value << " ";
            // else
            //     std::cout << "Null ";
            std::cout << vector[i]->value << " ";
        }
        std::cout << "|";

        if(next){
            next->print();
        }
    }
};

class BSkipList {
private:
    std::vector<Block*> levels; // Vector of head blocks from each level
public:
    BSkipList() {
        Block* block = new Block(INT_MIN, nullptr); // negative infinity block
        levels.push_back(block);
    }

    ~BSkipList() {
        // Destructor to free memory
        // ... (cleanup logic here)
    }

    void insert(int value) {
        srand(time(NULL)); // initialize random seed
        int level = levels.size()-1;
        Block* current = levels[level];  // first block in higest level
        Block* block = levels[level];  // keep track the place for value
        while(current){
            for(unsigned int i = 0; i < current->vector.size(); i++) {
                if(value >= current->vector[i]->value){ // find the place
                    block = current;
                    level --;
                    break;
                }
            }
            // keep looking in next block
            current = current->next;
        }
        // reach the level 0, block is place for value
        for(unsigned int i = 0; i < block->vector.size(); i++) {
            if(block->vector[i]->value >= value){ // in the middle of the vector
                if(rand() % 2 == 0) // tail
                    block->vector.insert(block->vector.begin() + i, new Node(value,nullptr));
                else{ // head
                    std::vector<Node*> right;
                    // split and shrink block
                    for(unsigned int j = i; j < block->vector.size(); j++)
                        right.push_back(block->vector[j]);
                    std::cout << block->vector[0]->value <<std::endl;
                    block->vector.resize(i+1);
                    std::cout << block->vector[0]->value <<std::endl;
                    Block* rightBlock = new Block(-1,nullptr);
                    rightBlock->vector = right;
                    block->next = new Block(value,rightBlock);
                }
                return;
            }
        }
        // at the end of the vector
        if(rand() % 2 == 0) // tail
            block->vector.push_back(new Node(value,nullptr));
        else{ //head
            Block* newBlock = new Block(value,block->next);
            block->next = newBlock;
        }
    }

    void print(){
        for(unsigned int i = 0; i < levels.size(); i++) {
            levels[i]->print();
            std::cout << std::endl;
        }
    }
};

int main() {
    BSkipList list;
    list.insert(1);
    list.insert(5);
    list.insert(2);
    list.insert(3);
    list.insert(10);
    list.insert(-1);
    list.print();
    return 0;
}