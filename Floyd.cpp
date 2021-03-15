#include <iostream>
#include <vector>
#include "WeightedGraph.h"
using namespace std;

class Floyd{
private:
    WeightedGraph wg;
    vector<vector<int>> dis;
    bool hasNCycle;

public:
    Floyd(const WeightedGraph& wg):wg(wg), hasNCycle(false){
        int V = wg.getV();
        dis = vector<vector<int>>(V, vector<int>(V, INT32_MAX));

        for (int i = 0; i < V; ++i){
            dis[i][i] = 0;
            for (int w : wg.adjL(i)){
                dis[i][w] = wg.getWeight(w,i);
            }
        }

        for (int t = 0; t < V; ++t){
            for (int v = 0; v < V; ++v){
                for (int w = 0; w < V; ++w){
                    if (dis[v][t] != INT32_MAX && dis[t][w] != INT32_MAX && dis[v][t] + dis[t][w] < dis[v][w])
                        dis[v][w] = dis[v][t] + dis[t][w];
                }
            }
        }

        for (int i = 0; i < V; ++i){
            if (dis[i][i] != 0)
                hasNCycle = 0;
        }
    }

    bool hasNegativeCycle() const{
        return hasNCycle;
    }

    bool isConnectedTo(int v, int w) const{
        return dis[v][w] != INT32_MAX;
    }

    int disTo(int v, int w) const{
        return dis[v][w];
    }

};

int main(){
    WeightedGraph wg("dijkstrag.txt");
    Floyd f(wg);
    if (!f.hasNegativeCycle()){
        for (int v = 0; v < wg.getV(); ++v){
            for (int w = 0; w < wg.getV(); ++w){
                cout << f.disTo(v, w) << ' ';
            }
            cout << endl;
        }
        cout << endl;
    }

    return 0;
}