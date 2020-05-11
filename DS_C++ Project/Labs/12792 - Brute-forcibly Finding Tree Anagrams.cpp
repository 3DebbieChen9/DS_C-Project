//
//  12792 - Brute-forcibly Finding Tree Anagrams.cpp
//  DS_C++ Project
//
//  Created by Debbie on 2020/5/11.
//  Copyright © 2020 Debbie. All rights reserved.
//

#include <iostream>
#include <string.h>
using namespace std;

typedef struct Node {
    char key;
    int heap;
    struct Node* left, *right;
}Node;

Node* newHeapNode(char data)
{
    Node *newNode = new Node;
    newNode->key = data;
    newNode->left = newNode->right = NULL;
    return (newNode);
}

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


Node* buildHeapTree(char *newHeapOrder, int index, int len) {
    Node *root = newHeapNode(newHeapOrder[index]);
    
    if (index > len) {
        return root;
    }
        
    if(2*index <= len) {
        root->left = buildHeapTree(newHeapOrder, 2*index, len);
    }
    
    if(2*index + 1 <= len) {
        root->right = buildHeapTree(newHeapOrder, 2*index+1, len);

    }
    
    return root;
    
}

void storeInOrder(Node* node, char* newInorder) {
    if (node == NULL)
       return;

    storeInOrder(node->left, newInorder);
    if(node->key != ' ') {
        newInorder = listAppend(newInorder, node->key);
    }
    
    storeInOrder(node->right, newInorder);
}

void solution(int *heap, char *heapOrder, char *InOrder, int heapSize) {
    char newHeapOrder[100] = {};
    inputToHeap(heapOrder, heap, newHeapOrder);
    Node *root = buildHeapTree(newHeapOrder, 1, heapSize);
    char newInorder[100] = {};
    
    storeInOrder(root, newInorder);
    if(strcmp(newInorder, InOrder) == 0) {
        cout << "Yes" << endl;
    }
    else {
        cout << "No" << endl;
    }
}


int main(void) {
    int heapSize;
    cin >> heapSize;
    int heap[heapSize + 1];
    for(int i = 1; i <= heapSize; i++) {
        cin >> heap[i];
    }
    int numPairs;
    cin >> numPairs;
    char heapOrder[100], InOrder[100];
    while(numPairs--) {
        cin >> heapOrder;
        cin >> InOrder;
        solution(heap, heapOrder, InOrder, heapSize);
        
    }
    
    return 0;
}
