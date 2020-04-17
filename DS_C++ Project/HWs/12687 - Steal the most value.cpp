//
//  12687 - Steal the most value.cpp
//  DS_C++ Project
//
//  Created by Debbie on 2020/3/16.
//  Copyright © 2020 Debbie. All rights reserved.
//

#include <iostream>

using namespace std;

int N, K;
int MAX = 0;
int value[10000];
int weight[10000];

void calulate(int index, int tmpV, int tmpW) {
    if (index == N) {
        return;
    }
    else {
        tmpW += weight[index];
        
        if (tmpW <= K) {
            tmpV += value[index];
            if (tmpV > MAX)
                MAX = tmpV;
            calulate(index + 1, tmpV, tmpW);
            tmpW -= weight[index];
            tmpV -= value[index];
            calulate(index + 1, tmpV, tmpW);
        }
            
        else {
            tmpW -= weight[index];
            calulate(index + 1, tmpV, tmpW);
        }
    }
}

int main(void) {

    
    cin >> N >> K;

    for (int i = 0; i < N; i++) {
        cin >> value[i] >> weight[i];
    }
    calulate(0, 0, 0);
    
    cout << MAX;
    
    return 0;
}

