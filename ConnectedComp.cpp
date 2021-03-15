#include <iostream>
#include <vector>
#include "Graph.h"
using namespace std;

class ConnectedComp{
private:
    Graph G;
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
    ConnectedComp(const Graph& G):G(G), ccount(0){
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

int main(){
    Graph g("g.txt");
    ConnectedComp cc(g);
    cout << cc.getCcount() << endl;

    vector<int> visited = cc.getVisited();
    for (int i = 0; i < int(visited.size()); ++i){
        cout << visited[i] << ' ';
    }
    cout << endl;

    cout << cc.isConnected(1,2) << endl;

    vector<vector<int>> component = cc.components();

    for (int i = 0; i < int(component.size()); ++i){
        for (int j = 0; j < int(component[i].size()); ++j){
            cout << component[i][j] << ' ';
        }
        cout << endl;
    }
    return 0;
}