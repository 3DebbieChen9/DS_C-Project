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


int main()
{
    char oldList[3] = {};
    char *newList;
    newList = listAppend(oldList, 'd');
    newList = listAppend(newList, 'z');
    for(int i = 0; i < strlen(newList); i++) {
        cout << newList[i];
    }
    return 0;
}
