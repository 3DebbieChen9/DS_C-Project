//
//  12698 - Steal the most value Quiz.cpp
//  DS_C++ Project
//
//  Created by Debbie on 2020/3/23.
//  Copyright © 2020 Debbie. All rights reserved.
//

#include <iostream>
using namespace std;
int N,K;
int value[10000], weight[10000];
int minW = 1000000;

void getval(int index, int tmpV, int tmpW) {
    if (index == N || tmpV >= K) {
        if (tmpV >= K && tmpW < minW)
            minW = tmpW;
        return;
    }
    else {
        tmpV += value[index];
        tmpW += weight[index];
        getval(index + 1, tmpV, tmpW);
        tmpV -= value[index];
        tmpW -= weight[index];
        getval(index + 1, tmpV, tmpW);
    }
}

int main(void) {
    cin >> N >> K;
    for (int i = 0; i < N; i++) {
        cin >> value[i] >> weight[i];
    }
    getval(0, 0, 0);
    cout << minW;
    
    
    return 0;
}
