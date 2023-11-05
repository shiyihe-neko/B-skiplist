#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

class Node {
public:
    int value;
    Node* next; // Pointer to next node within the same block
    Node* down; // Pointer to the corresponding node in the lower level

    Node(int val) : value(val), next(nullptr), down(nullptr) {}
};

class Block {
public:
    Node* head; // Pointer to the first node of the block
    Block* next; // Pointer to the next block at the same level
    size_t size; // Current size of the block

    Block() : head(nullptr), next(nullptr), size(3) {}

    bool is_full() {
        Node* temp = head;
        size_t count = 0;
        while (temp) {
            count++;
            if (count >= size) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    void double_size() {
        size *= 2;
    }
};


class BSkipList {
private:
    std::vector<Block*> levels; // Vector of head blocks, one for each level

public:
    BSkipList() {
        levels.push_back(new Block()); // Starting block at the bottom level
        srand(static_cast<unsigned>(time(nullptr))); // Seed the random number generator
    }

    ~BSkipList() {
        // Destructor to free memory
        // ... (cleanup logic here)
    }

    void insert(int value) {
        // Find the position to insert the new value in the bottom level
        Block* current = levels[0];
        Node* prev = nullptr;
        while (current && (prev == nullptr || prev->value < value)) {
            prev = find_position_in_block(current, value);
            if (prev && prev->value == value) {
                // Duplicate found; handle as required
                return;
            }
            if (prev && prev->next && prev->next->value < value) {
                current = current->next;
            }
        }

        // Create the new node
        Node* new_node = new Node(value);

        // Insert the node in the correct position
        if (prev) {
            new_node->next = prev->next;
            prev->next = new_node;
        }
        else {
            new_node->next = current->head;
            current->head = new_node;
        }

        // Adjust the block size if needed
        if (current->is_full()) {
            current->double_size();
        }

        // Coin flip to decide if we should promote
        if (rand() % 2 == 0) {
            promote(new_node);
        }
    }

    // Utility to find the position to insert within the block
    Node* find_position_in_block(Block* block, int value) {
        Node* current = block->head;
        Node* prev = nullptr;
        while (current && current->value < value) {
            prev = current;
            current = current->next;
        }
        return prev;
    }

    // Promote the node to the new block in the upper level
    void promote(Node* node_to_promote) {
        int level = 1; // Start promoting to the first level
        Node* current_node = node_to_promote;

        while (rand() % 2 == 0) { // Continue flipping the coin for promotion
            if (level >= levels.size()) {
                levels.push_back(new Block()); // Create a new level
            }

            // Create a new node for the upper level
            Node* new_node = new Node(node_to_promote->value);
            new_node->down = current_node; // Set down pointer to the current node

            // Insert the new node into the block at the beginning
            Block* current_level = levels[level];
            new_node->next = current_level->head;
            current_level->head = new_node;

            current_node = new_node; // Move up for the next iteration
            level++; // Go to the next level
        }
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