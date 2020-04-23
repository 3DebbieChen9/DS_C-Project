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

typedef struct {
    int rec_time;
    int sur_time;
    int sick_neighbor;
    int new_sick_neighbor;
    bool new_infected;
    string cur_vital;
    string next_vital;
    
    string right_name;
    string left_name;
    string down_name;
    string up_name;
}state_struct;

class node {
    public:
        // Constructor
        node() {
            type = 0;
            row = 0;
            col = 0;
            value = 0;
            index = 0;
            
            state.rec_time = 0;
            state.sur_time = 0;
            state.sick_neighbor = 0;
            state.new_sick_neighbor = 0;
            state.new_infected = false;
            state.cur_vital = "---";
            state.next_vital = "---";
            state.right_name = "---";
            state.left_name = "---";
            state.up_name = "---";
            state.down_name = "---";
            
            name = "---";
            next = NULL;
            down = NULL;
            right = NULL;
            up = NULL;
            left = NULL;
        }
        
        
        // Setting function
        void setType(int t) { type = t; } // Type 0: header_of_header | 1: header | 2: element
        void setDimension(int r, int c) { row = r; col = c; }
        void setValue(int it) { value = it; } // # of non-zero term | insert time
        void setIndex(int in) { index = in; } // insert order || index of header

        void setRCtime(int rc) { state.rec_time = rc; }
        void setSRtime(int sr) { state.sur_time = sr; }
        void setSN(int sn) { state.sick_neighbor = sn; }
        void setNSN(int nsn) { state.new_sick_neighbor = nsn; }
        void setNewInfected(bool nIN) { state.new_infected = nIN; }
        void setCurVital(string v) { state.cur_vital = v; }
        void setNextVital(string nv) { state.next_vital = nv; }
        void setRName(string rn) { state.right_name = rn; }
        void setLName(string ln) { state.left_name = ln; }
        void setUName(string un) { state.up_name = un; }
        void setDName(string dn) { state.down_name = dn; }
        
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
        int getIndex() { return index; }
    
        state_struct getState(){ return state; }
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
        int value; // insert_time || total people
        int index; // insert order || index of header
        
        state_struct state;
        string name;
        //status *status = new status(0, 0 , false, "None", "None", "None", "None", "None", "None");
    
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
    int dead = 0;
    
    // Header of header
    cin >> row >> col >> capacity >> sim_time;
    cur_capacity = capacity;
    cin >> num_people;
    node *header_of_header = new node();
    header_of_header->setType(0);
    header_of_header->setDimension(row, col);
    header_of_header->setValue(num_people);
    header_of_header->setName("header_of_header");
    
    // Header link
    node *header = new node();
    header->setType(1);
    header->setIndex(1);
    //cout << endl << header->getIndex() << endl;
    header->setName("header");
    header->setDownNode(header); // link back to self
    header->setRightNode(header);
    header_of_header->setNextNode(header);
    for(int i = 2; i <= max(row, col); i++) {
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
    
    cout << header->getType() << endl;
    
    
    // Sparse Matrix
    for(int i = 0; i < num_people; i++) {
        int iT, R, C;
        string name, state;
        cin >> iT >> R >> C >> name >> state;
        if(max(R,C) > max_dimension) max_dimension = max(R,C);
        node *element = new node();
        element->setType(2);
        element->setDimension(R, C);
        element->setValue(iT);
        element->setIndex(i);
        element->setCurVital(state);
        ///element->setNextVital(state);
        element->setName(name);
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

        if(state.compare("Sick") == 0) element->setRCtime(14);
    }
    
    
//    while(cur_time <= sim_time) {
//        node *row_header = header_of_header->getNextNode(); // row 0
//        // Day
//        for(int r = 0; r < max_dimension; r++) {
//            node *tmp = row_header->getRightNode(); // left-most element in the current row_header
//            while(tmp->getType() == 2) {
//                if(tmp->getValue() < cur_time) {
//                    ///tmp->setCurVital(tmp->getState().next_vital);
//                    node *right = tmp->getRightNode();
//                    node *left = tmp->getLeftNode();
//                    node *down = tmp->getDownNode();
//                    node *up = tmp->getUpNode();
//                    // 檢查附近的確診人數
//                    if((right->getRow() == tmp->getRow()) && (right->getCol() == tmp->getCol() + 1) && (right->getValue() < cur_time) && (right->getType() == 2)) {
//                        if(right->getState().cur_vital.compare("Sick") == 0) {
//                            if(right->getName().compare(tmp->getState().right_name) != 0) {
//                                tmp->setRName(right->getName());
//                                tmp->setNSN(tmp->getState().new_sick_neighbor + 1);
//                            }
//                            tmp->setSN(tmp->getState().sick_neighbor + 1);
//                        }
//                        // 右邊的人不是sick
//                        else {
//                            tmp->setRName("---");
//                        }
//                    }
//                    if((left->getRow() == tmp->getRow()) && (left->getCol() == tmp->getCol() - 1) && (left->getValue() < cur_time) && (left->getType() == 2)) {
//                        if(left->getState().cur_vital.compare("Sick") == 0) {
//                            if(left->getName().compare(tmp->getState().left_name) != 0) {
//                                tmp->setLName(left->getName());
//                                tmp->setNSN(tmp->getState().new_sick_neighbor + 1);
//                            }
//                            tmp->setSN(tmp->getState().sick_neighbor + 1);
//                        }
//                        else {
//                            tmp->setLName("---");
//                        }
//                    }
//                    if((up->getCol() == tmp->getCol()) && (up->getRow() == tmp->getRow() - 1) && (up->getValue() < cur_time) && (up->getType() == 2)) {
//                        if(up->getState().cur_vital.compare("Sick") == 0) {
//                            if(up->getName().compare(tmp->getState().up_name) != 0) {
//                               tmp->setUName(up->getName());
//                               tmp->setNSN(tmp->getState().new_sick_neighbor + 1);
//                            }
//                            tmp->setSN(tmp->getState().sick_neighbor + 1);
//                        }
//                        else {
//                            tmp->setUName("---");
//                        }
//                    }
//                    if((down->getCol() == tmp->getCol()) && (down->getRow() == tmp->getRow() + 1) && (down->getValue() <= cur_time) && (down->getType() == 2)) {
//                        if(down->getState().cur_vital.compare("Sick") == 0) {
//                            if(down->getName().compare(tmp->getState().down_name) != 0) {
//                                tmp->setDName(down->getName());
//                                tmp->setNSN(tmp->getState().new_sick_neighbor + 1);
//                            }
//                            tmp->setSN(tmp->getState().sick_neighbor + 1);
//                        }
//                        else {
//                            tmp->setDName("---");
//                        }
//                    }
//                }
//                tmp = tmp->getRightNode();
//            }
//            row_header = row_header->getNextNode();
//        }
//
//        // Night
//        for(int r = 0; r < max_dimension; r++) {
//            node *tmp = row_header->getRightNode();
//            while(tmp->getType() == 2) {
//                if(tmp->getValue() < cur_time) {
//                    // 如果自己是健康的
//                    if(tmp->getState().cur_vital.compare("Healthy") == 0) {
//                        if(tmp->getState().sick_neighbor > 0) {
//                            tmp->setCurVital("Sick");
//                            tmp->setRCtime(14 + 7 * tmp->getState().sick_neighbor);
//                        }
//                    }
//                    // 如果自己已確診
//                    else if(tmp->getState().cur_vital.compare("Sick") == 0) {
//                        // surrounded time
//                        if(tmp->getState().sick_neighbor >= 3) {
//                            tmp->setSRtime(tmp->getState().sur_time + 1);
//                        }
//                        else {
//                            tmp->setSRtime(0);
//                        }
//                        // recovery time
//                        tmp->setRCtime(tmp->getState().rec_time - 1 + 7 * tmp->getState().new_sick_neighbor);
//
//
//                        if(tmp->getState().rec_time == 0) {
//                            tmp->setCurVital("Healthy");
//                        }
//                        // Insert ICU have problem!!!
//                        else if(tmp->getState().rec_time > 28) {
//                            if(cur_capacity > 0) {
//                                tmp->setCurVital("ICU");
//                            }
//                        }
//
//                        if(tmp->getState().sur_time > 7) {
//                            tmp->setCurVital("Dead");
//                        }
//                    }
//                }
//                tmp->setSN(0);
//                tmp->setNSN(0);
//                tmp = tmp->getRightNode();
//            }
//            row_header = row_header->getNextNode();
//        }
//        cur_time++;
//    }
//
    node *row_header = header_of_header->getNextNode(); // row 0
    int alive = num_people - dead;
    float rate = alive / num_people * 100;
    cout << fixed << setprecision(2) << rate << "%" << endl;
    for(int r = 0; r < max_dimension; r++) {
        node *tmp_element = row_header->getRightNode();
        while(tmp_element->getType() == 2) {
            if(tmp_element->getState().cur_vital.compare("Dead") != 0 && tmp_element->getState().cur_vital.compare("ICU") != 0) {
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

    cout << "FUCK" << endl;
    
    
    return 0;
}
