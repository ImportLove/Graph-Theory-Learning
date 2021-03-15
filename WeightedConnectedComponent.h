#ifndef WEIGHTED_CONNECTED_COMPONENT_H_
#define WEIGHTED_CONNECTED_COMPONENT_H_

#include <iostream>
#include <vector>
#include "WeightedGraph.h"
using namespace std;

class WeightedConnectedComp{
private:
    WeightedGraph G;
    vector<int> visited;
    int ccount; // count the number of connected components

    void dfs(int v, int id){
        visited[v] = id;
        for(int x : G.adjL(v)){
            if (visited[x] == -1)
                dfs(x, ccount);
        }
    }

public:
    WeightedConnectedComp(const WeightedGraph& G):G(G), ccount(0){
        visited = vector<int>(G.getV(), -1);
        
        for (int i = 0; i < G.getV(); ++i){
            if (visited[i] == -1){
                dfs(i, ccount);
                ++ccount;
            }    
        }   
    }

    int getCcount() const{
        return ccount;
    }

    bool isConnected(int v, int w){
        // check if v and w is connected
        // assume v and w are valid node in the graph
        return visited[v] == visited[w];
    }

    vector<vector<int>> components(){
        vector<vector<int>> ans(ccount, vector<int>());
        for (int i = 0; i < int(visited.size()); ++i){
            ans[visited[i]].push_back(i);
        }

        return ans;
    }

    vector<int> getVisited() const{
        return visited;
    }
};

#endif
