#include <iostream>
#include <vector>
#include "graph.h"
#include "Edge.h"
using namespace std;

class FindBridge{
private:
    Graph g;
    vector<bool> visited;
    vector<int> ord;
    vector<int> low;
    vector<Edge> bridge;
    int count;

    void dfs(int s, int parent){
        visited[s] = true;
        ord[s] = count;
        low[s] = count;
        ++count;

        for (int node : g.adjL(s)){
            if (!visited[node]){
                dfs(node, s);
                low[s] = min(low[node], low[s]);
                if (low[node] > ord[s])
                    bridge.push_back(Edge(s, node));
            }
                
            else if (node != parent)
                low[s] = min(low[s], low[node]);
        }
    }

public:
    FindBridge(const Graph& g): g(g), count(0){
        visited = vector<bool> (g.getV(), false);
        ord = vector<int> (g.getV(), 0);
        low = vector<int> (g.getV(), 0);
        for (int i = 0; i < g.getV(); ++i){
            if (!visited[i]){
                dfs(i, i);
            }
        }
    }

    const vector<Edge>& getBridge() const{
        return bridge;
    }
};

int main(){
    Graph g("bridge.txt");
    FindBridge fb(g);
    vector<Edge> ans = fb.getBridge();
    for (int i = 0; i < int (ans.size()); ++i){
        cout << ans[i] << ' ';
    }
    cout << endl;
    return 0;
}