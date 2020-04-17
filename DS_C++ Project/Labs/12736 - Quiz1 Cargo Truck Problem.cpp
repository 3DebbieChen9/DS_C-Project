//
//  12736 - Quiz1 Cargo Truck Problem.cpp
//  DS_C++ Project
//
//  Created by Debbie on 2020/4/13.
//  Copyright © 2020 Debbie. All rights reserved.
//

#include <iostream>

using namespace std;

const int MAX_NUM = 10;
const int MAX_SIZE = 50;
const int MAX_TRUCK_H = 50;

typedef struct {
    int index;
    int place;
    int width;
    int height;
    char look[MAX_SIZE][MAX_SIZE];
}item;

typedef struct {
    int index;
    int length;
    char look[MAX_TRUCK_H][MAX_SIZE];
}truck;


int num_of_items;
int num_of_trucks;
item ITEMS[MAX_NUM];
truck TRUCKS[MAX_NUM];
bool done = false;

void print_truck(truck truck) {
    for(int i = 0; i < MAX_TRUCK_H; i++) {
        for(int j = 0; j < truck.length; j++) {
            cout << truck.look[i][j];
        }
        cout << endl;
    }
}

bool can_put(int index, truck truck, int x) {
    int h = ITEMS[index].height;
    int w = ITEMS[index].width;
    if(x + w == truck.length) {
        return false;
    }
    for(int row = 0; row < h; row++) {
        for(int col = 0; col < w; col++) {
            if(ITEMS[index].look[row][col] == 'O' && truck.look[row + MAX_TRUCK_H - h][x + col] == 'O') {
                return false;
            }
        }
    }

    return true;
}

// Items must occupy the entire length
// 自己拼圖的大小左右各加一，只要在這個範圍內，且不屬於自己的Ｏ，左右邊各有Ｏ，就表示有滿足
bool wall (int index) {
    return true;
    //    // Items must occupy the entire length
    //    bool touch = false;
    //    if(x == 0) {
    //        return true;
    //    }
    ////    else if(index == num_of_items - 1){
    ////        if(x + w == truck.length - 1) {
    ////            return true;
    ////        }
    ////        else return false;
    ////    }
    //    else {
    //        for(int row = 0; row < h; row++) {
    //            if(ITEMS[index].look[row][0] == 'O'){
    //                if(truck.look[row + MAX_TRUCK_H - h][x - 1] == 'O') {
    //                    touch = true;
    //                    break;
    //                }
    //            }
    //        }
    //    }
    //                bool r_wall = false, l_wall = false;
    //                for(int truck_r = cur_truck.length-1; truck_r < MAX_TRUCK_H; truck_r++) {
    //                    if(cur_truck.look[truck_r][cur_truck.length-1] == 'O'){
    //                        r_wall = true;
    //                        break;
    //                    }
    //                }
    //                if(r_wall) {
    //                    done = true;
    //                }
    //                else {
    //                    done = false;
    //                }
}

truck put_item(int index, truck truck, int x) {
    int h = ITEMS[index].height;
    int w = ITEMS[index].width;
    for(int row = 0; row < h; row++) {
        for(int col = 0; col < w; col++) {
            if(ITEMS[index].look[row][col] == 'O') {
                truck.look[row + MAX_TRUCK_H - h][x + col] = 'O';
            }
        }
    }
    return truck;
}



void slove(int index, truck cur_truck) {

    
//    // All done, and within the length
//    if(index == num_of_items) {
//        done = true;
//        return;
//    }
    // The last piece
    if(index == num_of_items - 1) {
        for(int col = 0; col <= cur_truck.length - ITEMS[index].width; col++) {
//            cout << "Try # " << index << "@ col " << col << endl;
            if(can_put(index, cur_truck, col)) {
                bool edge = true;
                for(int piece = 0; piece < num_of_items; piece++) {
                    if(!wall(piece)) {
                        edge = false;
                        break;
                    }
                }
                if(edge)
                    done = true;
//                truck tmp_truck;
//                tmp_truck.length = cur_truck.length;
//                tmp_truck = put_item(index, cur_truck, col);
//                cout << "Put # " << index << "@ col " << col << endl;
//                print_truck(tmp_truck);
//                cout << "====" << endl;
                return;
            }
        }
        if(!done) return;
    }
    else {
        for(int col = 0; col <= cur_truck.length - ITEMS[index].width; col++) {
//            cout << "Try # " << index << "@ col " << col << endl;
            if(done) break;
            if(can_put(index, cur_truck, col)) {
                ITEMS[index].place = col;
                truck tmp_truck;
                tmp_truck.length = cur_truck.length;
                tmp_truck = put_item(index, cur_truck, col);
//                cout << "Put # " << index << "@ col " << col << endl;
//                print_truck(tmp_truck);
//                cout << "====" << endl;
                slove(index + 1, tmp_truck);
            }
            //cout << "Next x " << col + 1 << endl;
        }
        
    }
}




int main(void) {
    
    cin >> num_of_items;
    for(int i = 0; i < num_of_items; i++) {
        ITEMS[i].index = i;
        cin >> ITEMS[i].width >> ITEMS[i].height;
        for(int h = 0; h < ITEMS[i].height; h++) {
            for(int w = 0; w < ITEMS[i].width; w++) {
                cin >> ITEMS[i].look[h][w];
            }
        }
    }
    
    cin >> num_of_trucks;
    for(int i = 0; i < num_of_trucks; i++) {
        cin >> TRUCKS[i].length;
        TRUCKS[i].index = i;
        for(int row = 0; row < MAX_TRUCK_H; row++) {
            for(int col = 0; col < TRUCKS[i].length; col++) {
                TRUCKS[i].look[row][col] = '-';
            }
        }
    }
    
    for(int i = 0; i < num_of_trucks; i ++) {
        done = false;
        slove(0, TRUCKS[i]);
        if(done) {
            cout << "Yes" << endl;
        }
        else {
            cout << "No" << endl;
        }
        
    }
    
    
    
    
    
    
    return 0;
}
