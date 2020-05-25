//
//  12802 - Least Skill Point.cpp
//  DS_C++ Project
//
//  Created by Debbie on 2020/5/25.
//  Copyright © 2020 Debbie. All rights reserved.
//

#include <iostream>
#include <limits.h>
#include <string.h>

using namespace std;

char* listAppend(char* oldList, char appendChar) {
    int newIndex = int(strlen(oldList));
    oldList[newIndex] = appendChar;
    return oldList;
}

int Choose(int n, int* current_dist, bool* current_visited) {
    int minimum = INT_MAX;
    int index = 0;
    for(int i = 0; i < n; i++) {
        if(current_visited[i] == false && current_dist[i] != -1) {
            if(current_dist[i] < minimum) {
                minimum = current_dist[i];
                index = i;
            }
        }
    }
    return index;
}

int main(void) {
    int courses, relations;

    char start_char, target_char;
    int effort = 0;
    char finalpath[100]{};
    cin >> courses >> relations;
    cin >> start_char >> target_char;
    int start = int(start_char) - int('A');
    int target = int(target_char) - int('A');
    
    bool visited[courses];
    int cost[courses][courses];
    int dist[courses];
    int predecessor[courses];
    
    memset(cost, -1, sizeof(cost));
    
    // input : change 'char' into 'int'
    char tmp_from, tmp_to;
    int tmp_cost;
    while(relations--) {
        cin >> tmp_from >> tmp_to;
        int index_from = int(tmp_from) - int('A');
        int index_to = int(tmp_to) - int('A');
        cost[index_from][index_to] = 1;
    }
    
    // initial
    for(int i = 0; i < courses; i++) {
        visited[i] = false;
        dist[i] = cost[start][i];
        predecessor[i] = start;
    }
    dist[start] = 0;
    visited[start] = true;
    
    
    for(int i = 0; i < courses - 1; i++) {
        int now = Choose(courses, dist, visited);
        visited[now] = true;
        for(int j = 0; j < courses; j++) {
            // j is not visited yet, and there is the path between now -> j
            if(visited[j] == false && cost[now][j] != -1) {
                if(dist[now] + cost[now][j] < dist[j]) {
                    dist[j] = dist[now] + cost[now][j];
                    predecessor[j] = now;
                }
                else if(dist[j] == -1 && cost[now][j] != -1) {
                    dist[j] = dist[now] + cost[now][j];
                    predecessor[j] = now;
                }
            }
        }
    }
    

    
    
    effort = dist[target];
    int cur = target;
    listAppend(finalpath, char(target + int('A')));
    while(predecessor[cur] != start) {
        listAppend(finalpath, char(predecessor[cur] + int('A')));
        cur = predecessor[cur];
    }
    listAppend(finalpath, char(start + int('A')));
    
    
//    // debug
//    cout << "dist : ";
//    for(int i = 0; i < courses; i++) {
//        cout << dist[i] << " " ;
//    }
//    cout << endl;
//    // debug
//    cout << "predecessor : ";
//    for(int i = 0 ; i < courses; i++) {
//        cout << predecessor[i] << " ";
//    }
//    cout << endl;


    // output
    cout << effort << endl;
    int index = int(strlen(finalpath)) - 1;
    cout << finalpath[index];
    for(int i = index - 1 ; i >= 0; i--) {
        cout << " " << finalpath[i];
    }
    

    return 0;
}
