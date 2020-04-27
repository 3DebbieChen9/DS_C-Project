//
//  12754 - DS_Quiz2_PlantFlower.cpp
//  DS_C++ Project
//
//  Created by Debbie on 2020/4/27.
//  Copyright © 2020 Debbie. All rights reserved.
//

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class node {
    public:
        // Constructor
        node() {
            type = 0;
            row = 0;
            col = 0;
            num = 0;
            index = 0;
            neighbor = 0;
            
            name = "---";

            
            next = NULL;
            down = NULL;
            right = NULL;
            up = NULL;
            left = NULL;
        }
        
        void setType(int t) { type = t; }
        void setDimension(int r, int c) { row = r; col = c; }
        void setNum(int number) { num = number; }
        void setIndex(int i) { index = i; }
        void setNeighbor(int nb) { neighbor = nb; }
        void setName(string n) { name = n; }

        void setNextNode(node *n) { next = n; }
        void setDownNode(node *d) { down = d; }
        void setRightNode(node *r) { right = r; }
        void setUpNode(node *u) { up = u; }
        void setLeftNode(node *l) { left = l; }
        
        int getType() { return type; }
        int getRow() { return row; }
        int getCol() { return col; }
        int getNum() { return num; }
        int getIndex() { return index; }
        int getNeighbor() { return neighbor; }
        string getName() { return name; }

        node* getNextNode() { return next; }
        node* getDownNode() { return down; }
        node* getRightNode() { return right; }
        node* getUpNode() { return up; }
        node* getLeftNode() { return left; }
        
    private:
        int type;
        int row;
        int col;
        int num;
        int index;
        int neighbor;
        
        string name;
        
        node *next;
        node *down;
        node *right;
        node *up;
        node *left;
};

int main(void) {
    int max_dimension = 0;
    int fieldRow = 0, fieldCol = 0;
    int targetCol = 0;
    int num_seed = 0;
    
    cin >> fieldRow >> fieldCol >> targetCol;
    cin >> num_seed;
    
    // Header of header
    node *header_of_header = new node();
    header_of_header->setType(0);
    header_of_header->setDimension(fieldRow, fieldCol);
    header_of_header->setNum(num_seed);
    header_of_header->setName("header_of_header");
    
    
    // Header
    node *header = new node();
    header->setType(1);
    header->setIndex(1);
    header->setName("header");
    header->setDownNode(header);
    header->setRightNode(header);
    header_of_header->setNextNode(header);
    for(int i = 2; i <= max(fieldRow, fieldCol); i++) {
        node *new_header = new node();
        new_header->setType(1);
        new_header->setIndex(i);
        new_header->setName("header");
        new_header->setDownNode(new_header);
        new_header->setRightNode(new_header);
        header->setNextNode(new_header);
        header = new_header;
    }
    header->setNextNode(header_of_header);
    
    for(int i = 0; i < num_seed; i++) {
        int R, C;
        string name;
        cin >> R >> C >> name;
        if(max(R, C) > max_dimension) max_dimension = max(R, C);
        node *element = new node();
        element->setType(2);
        element->setDimension(R, C);
        element->setIndex(i);
        element->setName(name);
        element->setNum(8);
        
        // find the column header
        node *tmp_col_header = header_of_header->getNextNode();
        while(tmp_col_header->getIndex() != C) {
            tmp_col_header = tmp_col_header->getNextNode();
        }
        // find the last element before R in the same column
        node *tmp_col_element = tmp_col_header;
        while((tmp_col_element->getDownNode())->getType() == 2 && (tmp_col_element->getDownNode())->getRow() < R) {
            tmp_col_element = tmp_col_element->getDownNode();
        }
        // link the element in the vertical way
        element->setDownNode(tmp_col_element->getDownNode());
        (tmp_col_element->getDownNode())->setUpNode(element);
        tmp_col_element->setDownNode(element);
        element->setUpNode(tmp_col_element);
        
        
        // find the row header
        node *tmp_row_header = header_of_header->getNextNode();
        while(tmp_row_header->getIndex() != R) {
            tmp_row_header = tmp_row_header->getNextNode();
        }
        // find the last element before C in the same row
        node *tmp_row_element = tmp_row_header;
        while((tmp_row_element->getRightNode())->getType() == 2 && (tmp_row_element->getRightNode())->getCol() < C) {
            tmp_row_element = tmp_row_element->getRightNode();
        }
        // link the element in the horizontal way
        element->setRightNode(tmp_row_element->getRightNode());
        (tmp_row_element->getRightNode())->setLeftNode(element);
        tmp_row_element->setRightNode(element);
        element->setLeftNode(tmp_row_element);
    }
    
    int num_flower = 0;
    node *row_header = header_of_header->getNextNode(); // row 0
    for(int r = 1; r <= max_dimension; r++) {
        node *tmp = row_header->getRightNode();
        while(tmp->getType() == 2) {
            node *right = tmp->getRightNode();
            node *left = tmp->getLeftNode();
            node *down = tmp->getDownNode();
            node *up = tmp->getUpNode();
            if((right->getRow() == tmp->getRow()) && (right->getCol() == tmp->getCol() + 1) && (right->getType() == 2)) {
                tmp->setNeighbor(tmp->getNeighbor() + 1);
            }
            if((left->getRow() == tmp->getRow()) && (left->getCol() == tmp->getCol() - 1) && (left->getType() == 2)) {
                tmp->setNeighbor(tmp->getNeighbor() + 1);
            }
            if((up->getCol() == tmp->getCol()) && (up->getRow() == tmp->getRow() - 1) && (up->getType() == 2)) {
                tmp->setNeighbor(tmp->getNeighbor() + 1);
            }
            if((down->getCol() == tmp->getCol()) && (down->getRow() == tmp->getRow() + 1) && (down->getType() == 2)) {
                tmp->setNeighbor(tmp->getNeighbor() + 1);
            }
            
            if(tmp->getNeighbor() == 4) {
                tmp->setNum(0);
            }
            else {
                for(int i = 0; i < tmp->getNeighbor(); i++) {
                    tmp->setNum(tmp->getNum() / 2);
                }
            }
            num_flower += tmp->getNum();
            
            tmp = tmp->getRightNode();
        }
        row_header = row_header->getNextNode();
        
    }
    
    cout << num_flower << endl;
    
    node *col_header = header_of_header->getNextNode(); // col 0
    while(col_header->getIndex() < targetCol) {
        col_header = col_header->getNextNode();
    }
    node *out = col_header->getDownNode();
    if(out->getType() == 2) {
        cout << out->getName();
        out = out->getDownNode();
        
    }
    while(out->getType() == 2) {
        cout << " " << out->getName();
        out = out->getDownNode();
    }
    
    
    return 0;
}
