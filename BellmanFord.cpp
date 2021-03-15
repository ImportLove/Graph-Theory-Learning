#include <iostream>
#include <vector>
#include <algorithm>
#include "WeightedGraph.h"
using namespace std;


class BelllmanFord{
private:
    WeightedGraph wg;
    int s;
    vector<int> dis;
    vector<int> pre;
    bool hasNCycle;

public:
    BelllmanFord(const WeightedGraph& wg, int s):wg(wg), s(s), hasNCycle(false){
        dis = vector<int>(wg.getV(), INT32_MAX);
        pre = vector<int>(wg.getV(), -1);
        dis[s] = 0;
        pre[s] = s;

        for (int i = 1; i < wg.getV(); ++i){
            for (int v = 0; v < wg.getV(); ++v){
                for (int w : wg.adjL(v)){
                    if (dis[v] != INT32_MAX && dis[v] + wg.getWeight(v, w) < dis[w]){
                        dis[w] = dis[v] + wg.getWeight(v, w);
                        pre[w] = v;
                    }
                        
                }
            }
        }

        // check one more round

        for (int v = 0; v < wg.getV(); ++v){
            for (int w : wg.adjL(v)){
                if (dis[v] != INT32_MAX && dis[v] + wg.getWeight(v, w) < dis[w])
                    hasNCycle = true;
            }
        }
    }

    bool hasNegativeCycle() const{
        return hasNCycle;
    }

    bool isConnectedTo(int v) const{
        return dis[v] != INT32_MAX;
    }

    int disTo(int v) const{
        return dis[v];
    }

    vector<int> path(int v) const{
        vector<int> ans;

        int cur = v;
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
    // WeightedGraph wg("dijkstrag.txt");
    WeightedGraph wg("bellmanfordg.txt");
    BelllmanFord bf(wg, 0);

    if (!bf.hasNegativeCycle()){
        for (int i = 0; i < wg.getV(); ++i){
            cout << bf.disTo(i) << ' ';
        }
        cout << endl;
    }

    return 0;
}