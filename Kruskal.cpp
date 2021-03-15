#include <iostream>
#include <vector>
#include <algorithm>
#include "WeightedGraph.h"
#include "WeightedEdge.h"
#include "WeightedConnectedComponent.h"
using namespace std;

class Kruskal{
private:
    WeightedGraph wg;
    vector<WeightedEdge> mst;
public:
    Kruskal(const WeightedGraph& wg):wg(wg){
        WeightedConnectedComp wcc(wg);
        if (wcc.getCcount() > 1)
            return;
        vector<WeightedEdge> edges;
        for (int v = 0; v < wg.getV(); ++v){
            for (int w : wg.adjL(v)){
                if (v < w)
                    edges.push_back(WeightedEdge(v, w, wg.getWeight(v, w)));
            }   
        }
        sort(edges.begin(), edges.end());

        // require disjoint set to finish the rest
        
    }

    vector<WeightedEdge> result() const{
        return mst;
    }
};