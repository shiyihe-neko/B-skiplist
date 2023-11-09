#include <iostream>
#include <vector>
#include <stack>
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
    Block( Node* node, Block* next){
        vector.push_back(node);
        //vector.resize(3); // minimum size of each block
        this->next = next;
    }

    Block(std::vector<Node*> vector, Block* next){
    this->vector = vector;
    //vector.resize(3); // minimum size of each block
    this->next = next;
    }

    void print(){
        for (unsigned int i = 0; i < vector.size(); i++){
            // if(vector[i])
            //     std::cout << vector[i]->value << " ";
            // else
            //     std::cout << "Null ";
            std::cout << vector[i]->value;
            if(vector[i]->down)
                std::cout<<"("<<vector[i]->down->vector[0]->value <<")";
            std::cout<< " ";
        }
        std::cout << "|";
    }
};

class BSkipList {
private:
    std::vector<Block*> levels; // Vector of head blocks from each level
public:
    int r = 2;
    BSkipList() {
        Block* block = new Block(new Node(INT_MIN,nullptr), nullptr); // negative infinity block
        levels.push_back(block);
    }

    ~BSkipList() {
        // Destructor to free memory
        // ... (cleanup logic here)
    }

    void insert(int value) {
        srand(time(NULL)); // initialize random seed
        Block* current = levels[levels.size()-1];  // starting from first block in higest level
        std::stack<Block*> blocks;      // place for value at each level
        Block* block;  // keep track the place for value
        Node* prev;
        while(current){
            bool found = false;
            // find a value greater than insert value
            for(unsigned int i = 0; i < current->vector.size(); i++) {
                if(value > current->vector[i]->value){ // go to next node
                    prev = current->vector[i];
                    block = current;
                }
                else{    // find the place
                    blocks.push(block);
                    current = prev->down;
                    found = true;
                    break;
                }
            }
            if(!found){
                // keep looking in next block
                if(current->next){
                    current = current->next;
                    // last in current block
                    if(value < current->vector[0]->value){
                        blocks.push(block);
                        current = prev->down;
                    }
                }
                else // last in this level
                    blocks.push(current);
                    current = prev->down;
            }
        }
        // building block from botton
        block = blocks.top();
        blocks.pop();
        for(unsigned int i = 0; i < block->vector.size(); i++) {
            if(block->vector[i]->value > value){ // in the middle of the vector
                if(r % 2 == 0){ // tail
                    r++;
                    block->vector.insert(block->vector.begin() + i, new Node(value,nullptr));
                }
                else{ // head
                    r++;
                    std::vector<Node*> right;
                    // split and shrink block
                    for(unsigned int j = i; j < block->vector.size(); j++)
                        right.push_back(block->vector[j]);
                    block->vector.resize(i);
                    Block* rightBlock = new Block(right,nullptr);
                    block->next = new Block(new Node(value,nullptr),rightBlock);
                    // new level
                    if(blocks.empty()){
                        Block* up = new Block(new Node(INT_MIN,block),nullptr);
                        up->vector.push_back(new Node(value,block->next));
                        levels.push_back(up);
                    }
                }
                return;
            }
        }
        // at the end of the vector
        if(r % 2 == 0){ // tail
            r++;
            block->vector.push_back(new Node(value,nullptr));
        }
        else{ //head
            r++;
            Block* newBlock = new Block(new Node(value,nullptr),block->next);
            block->next = newBlock;
            // new level
            if(blocks.empty()){
                Block* up = new Block(new Node(INT_MIN,block),nullptr);
                up->vector.push_back(new Node(value,newBlock));
                levels.push_back(up);
            }
            
        }
    }

    void print(){
        for(unsigned int i = levels.size() - 1; i >= 0 ; i--) {
            Block* current = levels[i];
            while(current){
                current->print();
                current = current->next;
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    BSkipList list;
    list.insert(1);
    list.insert(10);
    list.insert(3);
    list.insert(4);
    list.print();
    return 0;
}