#include <iostream>
#include <queue>
#include <vector>
#include "Graph.h"
using namespace std;

class GraphBFS{

private:
    Graph g;
    vector<bool> visited;
    vector<int> order;

    void bfs(int s){
        queue<int> q;
        q.push(s);
        visited[s] = true;
        
        while (!q.empty()){
            int vertex = q.front();
            q.pop();
            order.push_back(vertex);
            for (int x : g.adjL(vertex)){
                if (!visited[x]){
                    q.push(x);
                    visited[x] = true;
                }      
            }
        }
    }

public:
    GraphBFS(const Graph& g):g(g){
        visited = vector<bool>(g.getV(), false);
        
        for (int i = 0; i < g.getV(); ++i){
            if (!visited[i])
                bfs(i);
        }
    }

    vector<int> getOrder() const{
        return order;
    }
};

int main(){
    Graph g("bfsg.txt");
    GraphBFS gbfs(g);
    vector<int> ans = gbfs.getOrder();
    for (int i : ans){
        cout << i << ' ';
    }
    cout << endl;
    return 0;
}