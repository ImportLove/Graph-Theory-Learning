#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include "Graph.h"
using namespace std;

class SingleSourcePath{

private:
    Graph g;
    vector<bool> visited;
    vector<int> pre;
    vector<int> dis;
    int s;

    void bfs(int s){
        queue<int> q;
        q.push(s);
        visited[s] = true;
        pre[s] = s;
        dis[s] = 0;
        
        while (!q.empty()){
            int vertex = q.front();
            q.pop();
            for (int x : g.adjL(vertex)){
                if (!visited[x]){
                    q.push(x);
                    visited[x] = true;
                    pre[x] = vertex;
                    dis[x] = dis[vertex]+1;
                }      
            }
        }
    }

public:
    SingleSourcePath(const Graph& g, int source):g(g), s(source){
        visited = vector<bool>(g.getV(), false);
        pre = vector<int>(g.getV(), -1);
        dis = vector<int>(g.getV(), -1);
        bfs(s);
    }

    bool isConnectedTo(int t) const{
        return visited[t];
    }

    vector<int> path(int t){
        vector<int> ans;
        if (!isConnectedTo(t))
            return ans;

        int tmp = t;
        while (tmp != s){
            ans.push_back(tmp);
            tmp = pre[tmp];
        }
        ans.push_back(s);
        reverse(ans.begin(), ans.end());
        return ans;
    }

    int getDis(int t) const{
        return dis[t];
    }

};

int main(){
    Graph g("bfsg.txt");
    SingleSourcePath single(g, 0);
    vector<int> ans = single.path(6);

    cout << "from 0 to 6: ";
    for (int x : ans){
        cout << x << "->";
    }
    cout << endl;

    for (int i = 0; i < g.getV(); ++i)
        cout << single.getDis(i) << endl;
    return 0;
}

