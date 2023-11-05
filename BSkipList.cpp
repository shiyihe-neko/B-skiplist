#include <iostream>
#include <vector>
#include <cstdlib>

class Node {
public:
    int value;
    Node* next; // Pointer to next node within the same block
    Node* above; // Pointer to the node above in the upper block

    Node(int val) : value(val), next(nullptr), above(nullptr) {}
};

class Block {
public:
    std::vector<Node*> nodes; // Container for nodesA within the block
    Block* next_block; // Pointer to the next block at the same level
    Block* above_block; // Pointer to the block above at the upper level
    size_t size; // Current size of the block

    Block() : next_block(nullptr), above_block(nullptr), size(3) {}

    bool is_full() const {
        return nodes.size() >= size;
    }

    void double_size() {
        size *= 2;
    }
};

class BSkipList {
private:
    Block* head;

public:
    BSkipList() {
        head = new Block(); // Starting block at the bottom level
    }

    ~BSkipList() {
        // Destructor to free memory
        // ... (cleanup logic here)
    }

    void insert(int value) {
        // ... (implementation of insert logic)
    }

    bool delete_value(int value) {
        // ... (implementation of delete logic)
    }

    Node* search(int value) {
        // ... (implementation of search logic)
    }

    std::vector<int> range_query(int start_value, int end_value) {
        // ... (implementation of range query logic)
    }
};
