#include <iostream>
#include <vector>
#include <algorithm>
#include "Graph.h"
using namespace std;

class SingleSourcePath{
private:
    Graph G;
    int s;
    vector<bool> visited;
    vector<int> pre;

    void dfs(int v, int parent){

        // parent represents the previous node
        visited[v] = true;
        pre[v] = parent;
        for(int x : G.adjL(v)){
            if (!visited[x])
                dfs(x, v);
        }
    }

public:
    SingleSourcePath(const Graph& G, int s):G(G),s(s){
        visited = vector<bool>(G.getV(), false);
        pre = vector<int> (G.getV(), -1);
        dfs(s, s);    
    }

    bool isConnected(int t){
        // check if t is connected to s
        return visited[t];
    }

    vector<int> path(int t){
        // return the path from s to t
        vector<int> ans;
        if (!isConnected(t))
            return ans;
        
        int cur = t;
        while (cur != s){
            ans.push_back(cur);
            cur = pre[cur];
        }

        reverse(ans.begin(), ans.end());
        return ans;
    }
};

int main(){
    Graph g("g.txt");
    SingleSourcePath ssp(g, 0);
    vector<int> ans = ssp.path(6);
    for (int i = 0; i < int(ans.size()); ++i){
        cout << ans[i] << " -> ";
    }
    cout << endl;
    return 0;
}