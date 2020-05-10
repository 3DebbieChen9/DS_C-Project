#include "function.h"
#include<iostream>
using namespace std;
int main()
{
    int N;
    cin >> N;
    char LevelOrder[1000], InOrder[1000];
    cout << N << "\n";
    while(N--)
    {
        cin >> LevelOrder;
        cin >> InOrder;
        solution(LevelOrder, InOrder);
    }
}