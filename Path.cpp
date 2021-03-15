#include <iostream>
#include <vector>
#include <algorithm>
#include "Graph.h"
using namespace std;

class Path{
private:
    Graph G;
    int s;
    int t;
    vector<bool> visited;
    vector<int> pre;

    bool dfs(int v, int parent){

        // parent represents the previous node
        visited[v] = true;
        pre[v] = parent;
        if (v == t) 
            return true;
        for(int x : G.adjL(v)){
            if (!visited[x]){
                if (dfs(x, v))
                    return true;
            }  
        }
        return false;
    }

public:
    Path(const Graph& G, int s, int t):G(G),s(s),t(t){
        visited = vector<bool>(G.getV(), false);
        pre = vector<int> (G.getV(), -1);
        dfs(s, s);    
    }

    bool isConnected(){
        // check if t is connected to s
        return visited[t];
    }

    vector<int> path(){
        // return the path from s to t
        vector<int> ans;
        if (!isConnected())
            return ans;
        
        int cur = t;
        while (cur != s){
            ans.push_back(cur);
            cur = pre[cur];
        }
        ans.push_back(s);
        reverse(ans.begin(), ans.end());
        return ans;
    }
};

int main(){
    Graph g("gg.txt");
    Path ssp(g, 0, 6);
    vector<int> ans = ssp.path();
    for (int i = 0; i < int(ans.size()); ++i){
        cout << ans[i] << " -> ";
    }
    cout << endl;
    return 0;
}