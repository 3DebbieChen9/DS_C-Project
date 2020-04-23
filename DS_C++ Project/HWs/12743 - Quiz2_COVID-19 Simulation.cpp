//
//  12743 - Quiz2_COVID-19 Simulation.cpp
//  DS_C++ Project
//
//  Created by Debbie on 2020/4/17.
//  Copyright © 2020 Debbie. All rights reserved.
//


// Infection still have problem
// RTE? WTF?

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;




int capacity;
int sim_time;

class node {
    public:
        // Constructor
        node(int type_ = 0, int row_ = 0, int col_ = 0, int value_ = 0, int rec_time_ = 0, int sur_time_ = 0, bool new_S_ = false, bool new_H_ = false, string state_ = "Help", string name_ = "COVID", node *next_ = NULL, node *down_ = NULL, node *right_ = NULL, node *up_ = NULL, node *left_ = NULL) {
            type = type_;
            row = row_;
            col = col_;
            value = value_;
            recovery_time = rec_time_;
            surround_time = sur_time_;
            
            new_sick = new_S_;
            new_healthy = new_H_;
            
            state = state_;
            name = name_;
            
            next = next_;
            down = down_;
            right = right_;
            up = up_;
            left = left_;
        }
        
        // Setting function
        void setType(int t) { type = t; } // Type 0: header_of_header | 1: header | 2: element
        void setDimension(int r, int c) { row = r; col = c; }
        void setValue(int it) { value = it; } // # of non-zero term | index | insert time
        void setRecTime(int rc) { recovery_time = rc; }
        void setStime(int st) { surround_time = st;}
    
        void setNewSick(bool sick) { new_sick = sick; }
        void setNewHealthy(bool healthy) { new_healthy = healthy; }
    
        void setState(string s) { state = s; } // State 0: Healthy | 1: Masked | 2: Sick | 3: ICU | 4: dead
        void setName(string n) { name = n; }
    
        void setNextNode(node *n) { next = n; }
        void setDownNode(node *d) { down = d; }
        void setRightNode(node *r) { right = r; }
        void setUpNode(node *u) { up = u; }
        void setLeftNode(node *l) { left = l; }
    
        // Getting function
        int getType() { return type; }
        int getRow() { return row; }
        int getCol() { return col; }
        int getValue() { return value; }
        int getRCtime() { return recovery_time; }
        int getStime() { return surround_time; }
    
        bool getNewSick() { return new_sick; }
        bool getNewHealthy() { return new_healthy; }
    
        string getState(){ return state; }
        string getName(){ return name; }
    
        node* getNextNode() { return next; }
        node* getDownNode() { return down; }
        node* getRightNode() { return right; }
        node* getUpNode() { return up; }
        node* getLeftNode() { return left; }

    private:
        int type;
        int row;
        int col;
        int value; // insert_time || total people || index of header
        int recovery_time;
        int surround_time;
        
        bool new_sick;
        bool new_healthy;
        
        string state;
        string name;
        
        node *next;
        node *down;
        node *right;
        node *up;
        node *left;
};




int main(void) {
    int max_dimension = 0;
    int sim_time = 0, cur_time = 0;
    int capacity = 0, cur_capacity = 0;
    int row, col, num_people;
    
//  node (int type_ = 0, int row_ = 0, int col_ = 0, int value_ = 0, int rec_time_ = 0, string state_ = "Help", string name_ = "COVID", node *next_ = NULL, node *down_ = NULL, node *right_ = NULL, node *up_ = NULL, node *left_ = NULL)
    
    // Header of header
    
    cin >> row >> col >> capacity >> sim_time;
    cin >> num_people;
    node *header_of_header = new node(0, row, col, num_people, 0, 0, false, false, "None", "header_of_header", NULL, NULL, NULL, NULL, NULL);
    
    // Header link
    node *header = new node(1, 0, 0, 0, 0, 0, false, false, "None", "header_of_header", NULL, NULL, NULL, NULL, NULL);
    header->setDownNode(header); // link back to self
    header->setRightNode(header);
    header_of_header->setNextNode(header);
    for(int i = 1; i < max(row, col); i++) {
        node *new_header = new node(1, 0, 0, i, 0, 0, false, false, "None", "header_of_header", NULL, NULL, NULL, NULL, NULL);
        new_header->setDownNode(new_header);
        new_header->setRightNode(new_header);
        header->setNextNode(new_header);
        header = new_header;
    }
    header->setNextNode(header_of_header);
    
    // Sparse Matrix
    for(int i = 0; i < num_people; i++) {
        int iT, R, C;
        string name, state;
        cin >> iT >> R >> C >> name >> state;
        if(max(R,C) > max_dimension) max_dimension = max(R,C);
        node *element = new node(2, R, C, iT, 0, 0, false, false, state, name, NULL, NULL, NULL, NULL, NULL);
        
        // find the column header
        node *tmp_col_header = header_of_header;
        while(tmp_col_header->getValue() != C) {
            tmp_col_header = tmp_col_header->getNextNode();
        }
        // find the last element in the same column
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
        node *tmp_row_header = header_of_header;
        while(tmp_row_header->getValue() != R) {
            tmp_row_header = tmp_row_header->getNextNode();
        }
        // find the last element in the same row
        node *tmp_row_element = tmp_row_header;
        while((tmp_row_element->getRightNode())->getType() == 2 && (tmp_row_element->getRightNode())->getCol() < C) {
            tmp_row_element = tmp_row_element->getRightNode();
        }
        // link the element in the horizontal way
        element->setRightNode(tmp_row_element->getRightNode());
        (tmp_row_element->getRightNode())->setLeftNode(element);
        tmp_row_element->setRightNode(element);
        element->setLeftNode(tmp_row_element);
        
        if(state.compare("Sick") == 0) element->setRecTime(14);
    }
    
    cur_capacity = capacity;
    int dead = 0;
    while(cur_time <= sim_time) {
        cout << endl;
        node *row_header = header_of_header->getNextNode(); // row 0
        for(int r = 0; r < max_dimension; r++) {
            node *tmp_element = row_header->getRightNode(); // left-most element in the current row_header
            while(tmp_element->getType() == 2) {
                //cout << tmp_element->getValue() << " " << tmp_element->getRow() << " " << tmp_element->getCol() << " " << tmp_element->getName() << " " << tmp_element->getState() << endl;
                if(tmp_element->getValue() <= cur_time) { // make sure the element is already inserted
                    int neighborSick = 0;
                    node *right = tmp_element->getRightNode();
                    node *left = tmp_element->getLeftNode();
                    node *up = tmp_element->getUpNode();
                    node *down = tmp_element->getDownNode();
                    
                    if(right->getCol() == tmp_element->getCol() + 1) {
                        if(((right->getState().compare("Sick") == 0) && (right->getValue() <= cur_time) && (right->getNewSick() == false)) || ((right->getNewHealthy() == true) && (right->getValue() <= cur_time))) neighborSick += 1;
                    }
                    
                    if(left->getCol() == tmp_element->getCol() - 1) {
                        if(((left->getState().compare("Sick") == 0) && (left->getValue() <= cur_time) && (left->getNewSick() == false)) || ((left->getNewHealthy() == true) && (left->getValue() <= cur_time))) neighborSick += 1;
                    }
                    
                    if(down->getRow() == tmp_element->getRow() + 1) {
                        if(((down->getState().compare("Sick") == 0) && (down->getValue() <= cur_time) && (down->getNewSick() == false)) || ((down->getNewHealthy() == true)  && (down->getValue() <= cur_time))) neighborSick += 1;
                    }
                    
                    if(up->getRow() == tmp_element->getRow() - 1) {
                        if(((up->getState().compare("Sick") == 0) && (up->getValue() <= cur_time) && (up->getNewSick() == false)) || ((up->getNewHealthy() == true) && (up->getValue() <= cur_time))) neighborSick += 1;
                    }
                    
                    
                    if(tmp_element->getState().compare("Healthy") == 0) {
                        if(neighborSick) {
                            tmp_element->setState("Sick");
                            tmp_element->setNewSick(true);
                            tmp_element->setRecTime(15);
                        }
                        
                        tmp_element->setNewHealthy(false);
                    }
                    if(tmp_element->getState().compare("Sick") == 0) {

                        if(neighborSick >= 3) {
                            int cur_st = tmp_element->getStime();
                            if(cur_st > 7) {
                                tmp_element->setState("Dead");
                                dead++;
                            }
                            else {
                                cur_st += 1;
                                tmp_element->setStime(cur_st);
                            }
                            
                        }
                
                        else {
                            tmp_element->setStime(0);
                        }
                        
                        int cur_rc = tmp_element->getRCtime();
                        cur_rc = cur_rc - 1 + neighborSick * 7;
                        if(cur_rc > 28 && cur_capacity > 0) {
                            tmp_element->setState("ICU");
                            dead++;
                            cur_capacity--;
                        }
                        else if(cur_rc == 0) {
                            tmp_element->setState("Healthy");
                            tmp_element->setNewHealthy(true);

                        }
                        tmp_element->setRecTime(cur_rc);
                    
                        tmp_element->setNewSick(false);
                    }
                    cout << tmp_element->getName() << " " << tmp_element->getState() << " rc = " << tmp_element->getRCtime() << endl;
                }
                tmp_element = tmp_element->getRightNode();
            }
            row_header = row_header->getNextNode();
        }
        cur_time++;
    }
    
    node *row_header = header_of_header->getNextNode(); // row 0
    int alive = num_people - dead;
    float rate = alive / num_people * 100;
    cout << fixed << setprecision(2) << rate << "%" << endl;
    for(int r = 0; r < max_dimension; r++) {
        node *tmp_element = row_header->getRightNode();
        while(tmp_element->getType() == 2) {
            if(tmp_element->getState().compare("Dead") != 0 && tmp_element->getState().compare("ICU") != 0) {
                cout << tmp_element->getName();
                if(alive > 1) {
                    cout << " ";
                    alive--;
                }
            }
            tmp_element = tmp_element->getRightNode();
        }
        row_header = row_header->getNextNode();
    }
    
    
    
    return 0;
}
