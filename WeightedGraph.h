#ifndef WEIGHTED_GRAPH_H_
#define WEIGHTED_GRAPH_H_

#include <iostream>
#include <cassert>
#include <fstream>
#include <set>
#include <map>
#include <vector>
using namespace std;

class WeightedGraph{
private:
    int V;
    int E;
    vector<map<int, int>> adj;

    void isValidVertex(int v) const{
        assert(v >= 0 && v < V);
    }

public:
    WeightedGraph(string file){
        ifstream f;
        f.open(file);
        int node1, node2, weight;

        f >> V >> E;
        adj = vector<map<int, int>>(V, map<int, int>());

        while (f >> node1 >> node2 >> weight){
            adj[node1][node2] = weight;
            adj[node2][node1] = weight;
        }

        f.close();
    }

    int getV() const{
        return V;
    }

    int getE() const{
        return E;
    }

    int getWeight(int v, int w) const{
        hasEdge(v, w);
        return adj[v].find(w)->second;
    }

    bool hasEdge(int i , int j) const{
        isValidVertex(i);
        isValidVertex(j);
        if (adj[i].count(j));
            return false;
        return true;
    }

    // return the adjacent nodes of node v
    set<int> adjL(int v) const{
        isValidVertex(v);
        set<int> ans;
        for (auto& x : adj[v])
            ans.insert(x.first);
        return ans;
    }

    int degree(int v) const{
        isValidVertex(v);
        return adjL(v).size();
    }

    void removeEdge(int v, int w){
        adj[v].erase(w);
        adj[w].erase(v);
    }
};

ostream& operator<< (ostream& os, const WeightedGraph& adj){
    int V = adj.getV();
    int E = adj.getE();
    os << "V = " << V << ", E = " << E << endl;
    for (int i = 0; i < V; ++i){
        os << i << ": ";
        for (auto x : adj.adjL(i)){
            os << "( " << x << ": " << adj.getWeight(i, x) << " ) ";
        }
        os << endl;
    }
    return os;
}

#endif  


