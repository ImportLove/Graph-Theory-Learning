#include <iostream>
#include <vector>
#include <queue>
#include "WeightedGraph.h"
#include "WeightedEdge.h"
#include "WeightedConnectedComponent.h"
using namespace std;

class Prim{

private:
    WeightedGraph wg;
    vector<WeightedEdge> mst;
public:
    Prim(const WeightedGraph& wg):wg(wg){
        WeightedConnectedComp wcc(wg);
        if (wcc.getCcount() > 1)
            return;
        
        // Prim algorithm
        vector<bool> visited(wg.getV(), false);
        visited[0] = true;

        /*
        // inefficient approach
        for (int i = 1; i < wg.getV(); ++i){
            
            WeightedEdge minE(-1,-1,INT32_MAX);
            for (int v = 0; v < wg.getV(); ++v){
                if (visited[v]){
                    for (int w: wg.adjL(v)){
                        if (!visited[w]){
                            WeightedEdge tmp(v, w, wg.getWeight(v,w));
                            minE = min(minE, tmp);
                        }
                    }
                }
            }
            if (minE.getV() == -1)
                break;
            mst.push_back(minE);
            visited[minE.getW()] = true;
        }
        */

        // optimized
        priority_queue<WeightedEdge, vector<WeightedEdge>, greater<WeightedEdge>> pq;
        for (int w : wg.adjL(0)){
            pq.push(WeightedEdge(0, w, wg.getWeight(0,w)));
        }

        while (!pq.empty()){
            WeightedEdge target = pq.top();
            pq.pop();
            if (visited[target.getW()])
                continue;
            visited[target.getW()] = true;
            for (int x : wg.adjL(target.getW())){
                pq.push(WeightedEdge(target.getW(), x, wg.getWeight(target.getW(),x)));
            }
            mst.push_back(target);
        }

    }

    vector<WeightedEdge> result(){
        return mst;
    }
};

int main(){
    WeightedGraph wg("primg.txt");
    Prim p(wg);
    auto ans = p.result();
    for (auto& i : ans){
        cout << i << ' ';
    }
    cout << endl;
    return 0;
}