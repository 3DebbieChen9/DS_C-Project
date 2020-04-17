//
//  12726 - Block puzzle.cpp
//  DS_C++ Project
//
//  Created by Debbie on 2020/4/2.
//  Copyright © 2020 Debbie. All rights reserved.
//
// AC

#include <iostream>

using namespace std;

const int MAX_NUM = 10;
const int MAX_SIZE = 50;
const int MAX_KIND = 8;

typedef struct {
    int index;
    int w, h;
    char look[MAX_SIZE][MAX_SIZE];
}block;

typedef struct {
    int num_of_puzzle;
    block all_blocks[MAX_NUM][MAX_KIND];
    int distinct_kinds[MAX_NUM];
} puzzle;

int num_of_maps;
block maps[MAX_NUM];
puzzle all_puzzle;
bool done = false;


void print_block(block a) {
    for(int i=0; i<a.h; i++) {
        for(int j=0; j<a.w; j++) {
            cout << a.look[i][j];
        }
        cout << endl;
    }
}

bool block_compare(block a, block b) {
    if (a.w != b.w || a.h != b.h) {
        return false;
    }
    else {
        for(int i = 0; i < a.w; i++) {
            for(int j = 0; j < a.h; j++) {
                if(a.look[i][j] != b.look[i][j]) {
                    return false;
                }
            }
            
        }
    }
    return true;
}

bool check_same(int index, block a) {
    
    bool flag = false;
    for (int ind = 0; ind < all_puzzle.distinct_kinds[index]; ind++) {
        
        if(block_compare(a, all_puzzle.all_blocks[index][ind])) {
            flag = true;;
            break;
        }
    }
    return flag;
}


void bulid_all_rotate_block() {
    // n 是第幾個 puzzle (block)
    for(int n = 0; n < all_puzzle.num_of_puzzle; n++) {
        int width = all_puzzle.all_blocks[n][0].w;
        int height = all_puzzle.all_blocks[n][0].h;
        block tmp;

        // right
        tmp.w = height;
        tmp.h = width;
        for(int i = 0; i < tmp.h; i++) {
            for(int j = 0; j < tmp.w; j++) {
                tmp.look[i][j] = all_puzzle.all_blocks[n][0].look[height - j - 1][i];
            }
        }
        if(!check_same(n, tmp)) {
            all_puzzle.all_blocks[n][all_puzzle.distinct_kinds[n]] = tmp;
            all_puzzle.distinct_kinds[n] += 1;
        }
        
        // down
        tmp.w = width;
        tmp.h = height;
        for(int i = 0; i < tmp.h; i++) {
            for(int j = 0; j < tmp.w; j++) {
                tmp.look[i][j] = all_puzzle.all_blocks[n][0].look[height - i - 1][width - j - 1];
            }
        }
        if(!check_same(n, tmp)) {
            all_puzzle.all_blocks[n][all_puzzle.distinct_kinds[n]] = tmp;
            all_puzzle.distinct_kinds[n] += 1;
        }
        
        // left
        tmp.w = height;
        tmp.h = width;
        for(int i = 0; i < tmp.h; i++) {
            for(int j = 0; j < tmp.w; j++) {
                tmp.look[i][j] = all_puzzle.all_blocks[n][0].look[j][width - i - 1];
            }
        }
        if(!check_same(n, tmp)) {
            all_puzzle.all_blocks[n][all_puzzle.distinct_kinds[n]] = tmp;
            all_puzzle.distinct_kinds[n] += 1;
        }
        
        // up-flip
        tmp.w = width;
        tmp.h = height;
        for(int i = 0; i < tmp.h; i++) {
            for(int j = 0; j < tmp.w; j++) {
                tmp.look[i][j] = all_puzzle.all_blocks[n][0].look[i][width - j - 1];
            }
        }
        if(!check_same(n, tmp)) {
            all_puzzle.all_blocks[n][all_puzzle.distinct_kinds[n]] = tmp;
            all_puzzle.distinct_kinds[n] += 1;
        }
        
        // right-flip
        tmp.w = height;
        tmp.h = width;
        for(int i = 0; i < tmp.h; i++) {
            for(int j = 0; j < tmp.w; j++) {
                tmp.look[i][j] = all_puzzle.all_blocks[n][0].look[j][i];
            }
        }
        if(!check_same(n, tmp)) {
            all_puzzle.all_blocks[n][all_puzzle.distinct_kinds[n]] = tmp;
            all_puzzle.distinct_kinds[n] += 1;
        }
        
        // down-flip
        tmp.w = width;
        tmp.h = height;
        for(int i = 0; i < tmp.h; i++) {
            for(int j = 0; j < tmp.w; j++) {
                tmp.look[i][j] = all_puzzle.all_blocks[n][0].look[height - i - 1][j];
            }
        }
        if(!check_same(n, tmp)) {
            all_puzzle.all_blocks[n][all_puzzle.distinct_kinds[n]] = tmp;
            all_puzzle.distinct_kinds[n] += 1;
        }
        
        
        // left-flip
        tmp.w = height;
        tmp.h = width;
        for(int i = 0; i < tmp.h; i++) {
            for(int j = 0; j < tmp.w; j++) {
                tmp.look[i][j] = all_puzzle.all_blocks[n][0].look[height - j - 1][width - i - 1];
            }
        }
        if(!check_same(n, tmp)) {
            all_puzzle.all_blocks[n][all_puzzle.distinct_kinds[n]] = tmp;
            all_puzzle.distinct_kinds[n] += 1;
        }
    }
}

bool can_put(block map, block puzzle, int puzzle_w, int puzzle_h, int current_x, int current_y) {
    if(current_x + puzzle_w <= map.w && current_y + puzzle_h <= map.h) {
        for(int r = 0; r < puzzle_h; r++) {
            for(int c = 0; c < puzzle_w; c++) {
                if(map.look[r + current_y][c + current_x] == 'O' && puzzle.look[r][c] == 'O') {
                    return false;
                }
            }
        }
        return true;
    }
    return false;
}

block update_map(block old_map, block puzzle, int x, int y) {
    for(int i=0; i<puzzle.h; i++) {
        for(int j=0; j<puzzle.w; j++) {
            if(old_map.look[y+i][x+j] == '-' && puzzle.look[i][j] == 'O') {
                old_map.look[y+i][x+j] = 'O';
            }
                
        }
    }
    return old_map;
}

bool add_new_block(block current_map, int current_puzzle, int current_kind, int current_x, int current_y) {
    // base case: 如果是最後一片，看最後一片是否可以放
    if(current_puzzle == all_puzzle.num_of_puzzle - 1) {
        // 可以放，return true
        // try all kind
        for(int k=0; k<all_puzzle.distinct_kinds[current_puzzle]; k++) {
            int puzzle_h = all_puzzle.all_blocks[current_puzzle][k].h;
            int puzzle_w = all_puzzle.all_blocks[current_puzzle][k].w;
            for(int y=0; y<= current_map.h - puzzle_h; y++) {
                for(int x=0; x<= current_map.w - puzzle_w; x++) {
                    if(can_put(current_map, all_puzzle.all_blocks[current_puzzle][k], puzzle_w, puzzle_h, x, y)) {
                        return true;
                    }
                }
                
            }
        }
        return false;
    }
    else {
        // 當如果不是最後一片，如果自己可以放，去看下一片可不可以放
        bool done = false;
        for(int k=0; k<all_puzzle.distinct_kinds[current_puzzle]; k++) {
            int puzzle_h = all_puzzle.all_blocks[current_puzzle][k].h;
            int puzzle_w = all_puzzle.all_blocks[current_puzzle][k].w;
            for(int y=0; y<= current_map.h - puzzle_h; y++) {
                for(int x=0; x<= current_map.w - puzzle_w; x++) {
                    
                    if(can_put(current_map, all_puzzle.all_blocks[current_puzzle][k], puzzle_w, puzzle_h, x, y)) {
                        block tmp_map = update_map(current_map, all_puzzle.all_blocks[current_puzzle][k], x, y);
                        if (add_new_block(tmp_map, current_puzzle+1, 0, 0, 0)) {
                            done = true;
                            break;
                        }
                    }
                }
                if(done) break;
                
            }
            if(done) break;
        }
        return done;
    }
}

bool check(int map_index) {
    // 檢查第 n 個地圖的情況（從第一片, 第一種狀態, x=0, y=0);
    return add_new_block(maps[map_index], 0, 0, 0, 0);
}


int main (void) {
    
    // Input
    cin >> all_puzzle.num_of_puzzle;
    for(int i = 0; i < all_puzzle.num_of_puzzle; i++) {
        int height, width;
        cin >> width >> height;
        all_puzzle.all_blocks[i][0].w = width;
        all_puzzle.all_blocks[i][0].h = height;
        all_puzzle.distinct_kinds[i] = 1;
        for(int h = 0; h < height; h++) {
            for(int w = 0; w < width; w++) {
                cin >> all_puzzle.all_blocks[i][0].look[h][w];
            }
        }
    }
    
    cin >> num_of_maps;
    for(int i = 0; i < num_of_maps; i++) {
        cin >> maps[i].w >> maps[i].h;
        for(int h = 0; h < maps[i].h; h++) {
            for(int w = 0; w < maps[i].w; w++) {
                cin >> maps[i].look[h][w];
            }
        }
    }
    
    bulid_all_rotate_block();
    
    for(int graph = 0; graph < num_of_maps; graph++) {
        
        if(check(graph)) {
            cout << "Yes" << endl;
        }
        else {
            cout << "No" << endl;
        }
        
    }
    return 0;
}
