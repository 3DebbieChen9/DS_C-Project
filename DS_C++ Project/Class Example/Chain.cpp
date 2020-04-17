#include <iostream>

using namespace std;

class ChainNode {
    friend class Chain;
    public:
        // Constructor
        ChainNode(int value = 0, ChainNode *next = NULL) {
            data = value;
            link = next;
        }
    private:
        int data;
        ChainNode *link;
};

class Chain {
    public:
        // Create a chain with two nodes
        void Create2();

        // Insert a node with data = 50
        void Insert50(ChainNode *x);

        // Delete a node
        void Delete(ChainNode *x, ChainNode *y);

        // Reverse a chain
        void Reverse();

    private:
        ChainNode *first;
};

void Chain :: Create2() {
    // Create and set the fields of 2nd node
    ChainNode* second = new ChainNode(20, 0);

    // Create and set the fields of 1st node
    first = new ChainNode(10, second);
}

void Chain :: Insert50(ChainNode *x) {
    if(first) // Insert after x
        x->link = new ChainNode(50, x->link);
    else // Insert into empty list
        first = new ChainNode(50);
}

void Chain :: Delete(ChainNode *x, ChainNode *y) {
    // x is the node to be deleted and y is the node
    // preceding x
    if(x == first) first = first->link;
    else y->link = x->link;
    delete x;
    x = NULL;
}

void Chain :: Reverse(void) {
    // Turn a chain, (a1, ..., an) into (an, ..., a1)
    ChainNode *current = first, *previous = NULL;
    while (current) {
        ChainNode *r = previous;
        previous = current; // r is behind the previous
        current = current->link; // move current to nexe node
        current->link = r; // link previous to previous node
    }
    first = previous;
}


int main(void) {

    return 0;
}