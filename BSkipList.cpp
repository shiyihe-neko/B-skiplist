#include <iostream>
#include <vector>
#include <limits.h>

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
        vector.resize(3); // minimum size of each block
        this->next = next;
    }

    void print(){
        for (unsigned int i = 0; i < vector.size(); i++){
            if(vector[i])
                std::cout << vector[i]->value << " ";
            else
                std::cout << vector[i] << " ";

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
    list.print();
    return 0;
}