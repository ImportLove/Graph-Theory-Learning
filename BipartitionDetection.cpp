#include <iostream>
#include <vector>
#include "Graph.h"
using namespace std;

class BiparitionDetection{
private:
    Graph g;
    vector<bool> visited;
    vector<int> colors;
    bool bipartite;

    bool dfs(int v, int color){

        // color is the color of v
        visited[v] = true;
        colors[v] = color;
        for (int x : g.adjL(v)){
            if (!visited[x]){
                if (!dfs(x, 1-color))
                    return false;
            }
            else if (colors[x] == color)
                return false;
        }
        return true;
    }

public:
    BiparitionDetection(const Graph& g):g(g), bipartite(true){
        visited = vector<bool>(g.getV(), false);
        colors = vector<int>(g.getV(), -1);

        for (int i = 0; i < g.getV(); ++i){
            if (!visited[i]){
                if (!dfs(i, 0)){
                    bipartite = false;
                    break;
                }  
            }  
        }
    }

    int isBipartite() const{
        return bipartite;
    }
};

int main(){
    Graph g("NoCycle.txt");
    BiparitionDetection bd(g);
    cout << bd.isBipartite() << endl;
    return 0;
}
