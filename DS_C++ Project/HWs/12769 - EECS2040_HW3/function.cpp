//
//  12769 - EECS2040_HW3
//  function.cpp
//  DS_C++ Project
//
//  Created by Debbie on 2020/5/7.
//  Copyright © 2020 Debbie. All rights reserved.
//

#include <iostream>
#include <string.h>
using namespace std;

typedef struct Node {
    char key;
    struct Node* left, *right;
}Node;

Node* newNode(char data)
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

int search(char *level, int strt, int end, char value)
{
    for (int i = strt; i <= end; i++)
        if (level[i] == value)
            return i;
    return -1;
}

char *newLevelOrder(char *inOrder, char *levelOrder, int m, int n)
{
    char *newlevel = new char[m], j = 0;
    for (int i = 0; i < n; i++)
        if (search(inOrder, 0, m-1, levelOrder[i]) != -1) {
            newlevel[j] = levelOrder[i];
            j++;
        }
            
    return newlevel;
}
  
Node* buildTree(char *inOrder, char *levelOrder, int inStrt, int inEnd, int n)
{
    if (inStrt > inEnd)
        return NULL;
  
    /* The first node in level order traversal is root */
    Node *root = newNode(levelOrder[0]);
  
    /* If this node has no children then return */
    if (inStrt == inEnd)
        return root;
  
    /* Else find the index of this node in Inorder traversal */
    int inIndex = search(inOrder, inStrt, inEnd, root->key);
  
    // Extract left subtree keys from level order traversal
    char *llevel  = newLevelOrder(inOrder, levelOrder, inIndex, n);
  
    // Extract right subtree keys from level order traversal
    char *rlevel  = newLevelOrder(inOrder + inIndex + 1, levelOrder, n-inIndex-1, n);
  
    /* construct left and right subtress */
    root->left = buildTree(inOrder, llevel, inStrt, inIndex-1, n);
    root->right = buildTree(inOrder, rlevel, inIndex+1, inEnd, n);
  
    // Free memory to avoid memory leak
    delete [] llevel;
    delete [] rlevel;
  
    return root;
}

int height(Node* node)
{
    if (node == NULL)
        return 0;
    else
    {
        /* compute the height of each subtree */
        int lheight = height(node->left);
        int rheight = height(node->right);
  
        /* use the larger one */
        if (lheight > rheight)
            return(lheight + 1);
        else return(rheight + 1);
    }
}

void StoreGivenLevel(Node* root, int level, char* newLevel)
{
    if (root == NULL)
        return;
    if (level == 1) {
        //cout << root->key;
        newLevel = listAppend(newLevel, root->key);
    }
        
    else if (level > 1)
    {
        StoreGivenLevel(root->left, level-1, newLevel);
        StoreGivenLevel(root->right, level-1, newLevel);
    }
}

void StoreLevelOrder(Node* root, char* newLevel)
{
    int h = height(root);
    int i;
    for (i = 1; i <= h; i++)
        StoreGivenLevel(root, i, newLevel);
}
  
int permutation(char *InOrder, char In) {
    int index = 0;
    for(int i = 0; i < strlen(InOrder); i++) {
        if(InOrder[i] == In) {
            index = i;
        }
    }
    return index;
}

void solution(char *LevelOrder, char *InOrder) {
    Node *root = buildTree(InOrder, LevelOrder, 0, int(strlen(LevelOrder) - 1), int(strlen(LevelOrder)));
    cout << LevelOrder << endl << InOrder;
    
    char newLevel[100] = {};
    StoreLevelOrder(root, newLevel);
    
    cout << " " << permutation(InOrder, LevelOrder[0]);
    for(int i = 1; i < int(strlen(LevelOrder)); i++) {
        cout << "-" << permutation(InOrder, LevelOrder[i]);
    }
    
    if(strcmp(newLevel, LevelOrder) == 0) {
        cout << " Yes" << endl;
    }
    else {
        cout << " No" << endl;
    }
    
}
