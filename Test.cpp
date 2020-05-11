//
//  Test.cpp
//  DS_C++ Project
//
//  Created by Debbie on 2020/3/16.
//  Copyright © 2020 Debbie. All rights reserved.
//


#include <iostream>
#include <string.h>
using namespace std;


/*char* listAppend(char* oldList, char appendChar) {
    int newSize = int(strlen(oldList)) + 1;
    char newList[newSize];
    strcpy(newList, oldList);
    newList[newSize - 1] = appendChar;
    return newList;
}*/

char* listAppend(char* oldList, char appendChar) {
    int newSize = int(strlen(oldList));
    oldList[newSize] = appendChar;
    return oldList;
}

void inputToHeap(char* heapOrder, int* heap, char *newHeapOrder) {
    int j = 1;
    int i = 0;
    while(i < int(strlen(heapOrder))) {
        if(heap[j] == 1) {
            newHeapOrder[j] = heapOrder[i];
            i++;
            j++;
        }
        else {
            newHeapOrder[j] = ' ';
            j++;
        }
    }
}

int main()
{
    char heapOrder[100] = "abcd";
    cout << int(strlen(heapOrder)) << endl;
    int heap[100] = {0,1,1,0,1,1};
    char newHeapOrder[100] = {};
    inputToHeap(heapOrder, heap, newHeapOrder);
    for(int i = 0 ; i < 6; i++) {
        cout << newHeapOrder[i];
    }
    return 0;
}
