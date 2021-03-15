#include <iostream>
#include <vector>
#include <algorithm>
#include "Graph.h"
using namespace std;

class HamiltonLoop{
private:
    Graph G;
    vector<bool> visited;
    vector<int> pre;
    int end;

    bool allVisited(){
        for (int i = 0; i < int(visited.size()); ++i){
            if (visited[i] == false)
                return false;
        }

        return true;
    }

    bool dfs(int v, int parent){
        visited[v] = true;
        pre[v] = parent;
        for(int x : G.adjL(v)){
            if (!visited[x]){
                if (dfs(x, v))
                    return true;
            }
                
            else if (x == 0 && allVisited()){
                end = v;
                return true;
            }
        }
        visited[v] = false;
        return false;
    }

public:
    HamiltonLoop(const Graph& G):G(G), end(-1){
        visited = vector<bool>(G.getV(), false);
        pre = vector<int>(G.getV(), -1);
        dfs(0, 0);    
    }

    vector<int> result(){
        vector<int> ans;
        if (end == -1)
            return ans;
        
        int tmp = end;
        while (tmp != 0){
            ans.push_back(tmp);
            tmp = pre[tmp];
        }
        ans.push_back(0);
        reverse(ans.begin(), ans.end());
        return ans;
    }
};

int main(){
    Graph g("hamilton2.txt");
    HamiltonLoop hl(g);
    vector<int> ans = hl.result();
    for (auto x : ans){
        cout << x << ' ';
    }
    cout << endl;
    return 0;
}