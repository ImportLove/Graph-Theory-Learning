#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include "WeightedGraph.h"
using namespace std;

// single source algorithm
class Dijkstra{
private:
    WeightedGraph wg;
    vector<int> dis;
    vector<bool> visited;
    vector<int> pre;
    int s; // the start point
public:
    Dijkstra(const WeightedGraph& wg, int s):wg(wg),s(s){
        dis = vector<int>(wg.getV(), INT32_MAX);
        visited = vector<bool>(wg.getV(), false);
        pre = vector<int>(wg.getV(), -1);
        dis[s] = 0;
        pre[s] = s;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int,int>>> pq;
        pq.push(make_pair(dis[0],0));
        while (!pq.empty()){

            /*
            int curdis = INT32_MAX;
            int cur = -1;
            for (int i = 0; i < wg.getV(); ++i){
                if (!visited[i] && dis[i] < curdis){
                    curdis = dis[i];
                    cur = i;
                }
            }
            if (cur == -1)
                break;
            */

            pair<int,int> tmp = pq.top();
            pq.pop();
            int cur = tmp.second;
            int curdis = tmp.first;

            if (visited[cur])
                continue;
            
            visited[cur] = true;
            for (int w : wg.adjL(cur)){
                if (!visited[w] && dis[w] > curdis + wg.getWeight(cur, w)){
                    dis[w] = curdis + wg.getWeight(cur, w);
                    pq.push(make_pair(dis[w], w));
                    pre[w] = cur;
                }  
            }
        }
    }

    bool isConnectedTo(int v) const{
        return visited[v];
    }

    int disTo(int v) const{
        return dis[v];
    }

    vector<int> path(int t) const{
        vector<int> ans;
        if (!isConnectedTo(t))
            return ans;
        int cur = t;
        while (cur != s){
            ans.push_back(cur);
            cur = pre[cur];
        }
        ans.push_back(cur);
        reverse(ans.begin(), ans.end());
        return ans;
    }
};

int main(){
    WeightedGraph wg("dijkstrag.txt");
    Dijkstra d(wg, 0);
    for (int i = 0; i < wg.getV(); ++i){
        cout << d.disTo(i) << ' ';
    }
    cout << endl;

    vector<int> ans = d.path(3);
    for (auto i : ans){
        cout << i << ' ';
    }
    cout << endl;
    return 0;
}