#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

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
private:
const int MINIMUM_BLOCK_SIZE = 3;
public:
    std::vector<Node*> vector; 
    Block* next; // Pointer to the next block at the same level
    Block(int value, Block* next){
        Node* node = new Node(value,nullptr);
        vector[0] = node;
        vector.resize(MINIMUM_BLOCK_SIZE);
        this->next = next;
    }

    void print(){
        for (auto & it : vector){
            std::cout << it << ",";
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
    const int NEGATIVE_INFINITY = - std::numeric_limits<int>::infinity();
public:
    BSkipList() {
        Block* block = new Block(NEGATIVE_INFINITY, nullptr);
        levels.push_back(block);
    }

    ~BSkipList() {
        // Destructor to free memory
        // ... (cleanup logic here)
    }

    void insert(int value) {
    }

    void print(){
        for(auto& it : levels) {
            it->print();
            std::cout << std::endl;
        }
    }
};

int main(void) {
  BSkipList list;
  list.print();
  return 0;
}
