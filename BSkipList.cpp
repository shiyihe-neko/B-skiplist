#include <iostream>
#include <vector>
#include <stack>
#include <random>
#include <limits.h>
#include <time.h> 

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
    std::stack<Block*> getBlockStack(int value){
        Block* current = levels[levels.size()-1];  // starting from first block in higest level
        std::stack<Block*> blocks;      // place for value at each level
        Block* block = current;  // keep track the place for value
        Node* prev;
        while(current){
            bool found = false;
            // find a value greater than insert value
            for(unsigned int i = 0; i < current->vector.size(); i++) {
                if(value > current->vector[i]->value){ // go to next node
                    prev = current->vector[i];
                }
                else{    // find the place
                    blocks.push(block);
                    current = prev->down;
                    block = current;
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
            block = current;
        }
        return blocks;
    }
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
        std::stack<Block*> blocks = getBlockStack(value);
        Block* lower = nullptr;
        // building block from botton
        while (!blocks.empty()){
            bool inserted = false;
            Block* block = blocks.top();
            blocks.pop();
            for(unsigned int i = 0; i < block->vector.size(); i++) {
                if(block->vector[i]->value > value){ // in the middle of the vector
                    if(rand() % 2 == 0){ // tail
                        r++;
                        block->vector.insert(block->vector.begin() + i, new Node(value,lower));
                        return;
                    }
                    else{ // head
                        r++;
                        // split and shrink block
                        std::vector<Node*> right;
                        right.push_back(new Node(value,lower));
                        for(unsigned int j = i; j < block->vector.size(); j++)
                            right.push_back(block->vector[j]);
                        block->vector.resize(i);
                        Block* rightBlock = new Block(right,block->next);
                        block->next = rightBlock;
                        // new level
                        if(blocks.empty()){
                            Block* up = new Block(new Node(INT_MIN,block),nullptr);
                            up->vector.push_back(new Node(value,block->next));
                            levels.push_back(up);
                        }
                        inserted = true;
                        lower = block->next;
                        break;
                    }
                }
            }
            if (!inserted){
                // at the end of the vector
                if(rand() % 2 == 0){ // tail
                    r++;
                    block->vector.push_back(new Node(value,lower));
                    return;
                }
                else{ //head
                    r++;
                    Block* newBlock = new Block(new Node(value,lower),block->next);
                    block->next = newBlock;
                    // new level
                    if(blocks.empty()){
                        Block* up = new Block(new Node(INT_MIN,block),nullptr);
                        up->vector.push_back(new Node(value,newBlock));
                        levels.push_back(up);
                    }
                    lower = newBlock;

                    
                }
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
    list.insert(2);
    list.insert(6);
    list.insert(11);
    list.insert(7);
    list.insert(8);

    list.print();
    return 0;
}