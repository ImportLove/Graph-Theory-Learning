#include <iostream>
#include <vector>
#include "Graph.h"
using namespace std;

class CycleDetection{

private:
    Graph g;
    vector<bool> visited;
    bool Cycle;

    bool dfs(int v, int parent){
        visited[v] = true;
        for(int x : g.adjL(v)){
            if (!visited[x]){
                if (dfs(x, v))
                    return true;
            }
            else if (x != parent)
                return true;
        }
        return false;
    }

public:
    CycleDetection(const Graph& g):g(g), Cycle(false){
        visited = vector<bool>(g.getV(), false);
        
        for (int i = 0; i < g.getV(); ++i){
            if (!visited[i]){
                if (dfs(i, i)){
                    Cycle = true;
                    break;
                }
            }     
        }
    }

    bool hasCycle() const{
        return Cycle;
    }
};

int main(){
    Graph g("g.txt");
    CycleDetection cd(g);
    cout << cd.hasCycle() << endl;
    return 0;
}