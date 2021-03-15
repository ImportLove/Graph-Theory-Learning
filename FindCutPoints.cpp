#include <iostream>
#include <vector>
#include "graph.h"
#include "Edge.h"
using namespace std;

class FindCutPoints{

private:
    Graph g;
    vector<bool> visited;
    vector<int> ord;
    vector<int> low;
    set<int> bridge;
    int count;

    void dfs(int s, int parent){
        visited[s] = true;
        ord[s] = count;
        low[s] = count;
        ++count;

        int child = 0;
        for (int node : g.adjL(s)){
            if (!visited[node]){
                dfs(node, s);
                low[s] = min(low[node], low[s]);

                if (s != parent && low[node] >= ord[s])
                    bridge.insert(s);
                
                ++child;

                if (s == parent && child > 1)
                    bridge.insert(s);
            }
                
            else if (node != parent)
                low[s] = min(low[s], low[node]);
        }
    }

public:
    FindCutPoints(const Graph& g):g(g), count(0){
        visited = vector<bool> (g.getV(), false);
        ord = vector<int> (g.getV(), 0);
        low = vector<int> (g.getV(), 0);
        for (int i = 0; i < g.getV(); ++i){
            if (!visited[i]){
                dfs(i, i);
            }
        }
    }

    const set<int>& getPoints() const{
        return bridge;
    }
};

int main(){
    Graph g("tree.txt");
    FindCutPoints fcp(g);
    set<int> ans = fcp.getPoints();
    for (int x : ans){
        cout << x << ' ';
    }
    cout << endl;
    return 0;
}