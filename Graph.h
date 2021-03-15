#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream>
#include <cassert>
#include <fstream>
#include <set>
#include <vector>
using namespace std;

class Graph{
private:
    int V;
    int E;
    bool directed;
    vector<set<int>> adj;

    void isValidVertex(int v) const{
        assert(v >= 0 && v < V);
    }

public:
    Graph(string file, bool d = false):directed(d){
        ifstream f;
        f.open(file);
        int node1, node2;

        f >> V >> E;
        adj = vector<set<int>>(V, set<int>());

        while (f >> node1 >> node2){
            adj[node1].insert(node2);
            if (directed) 
                adj[node2].insert(node1);
        }

        f.close();
    }

    int getV() const{
        return V;
    }

    int getE() const{
        return E;
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
        return adj[v];
    }

    int degree(int v) const{
        isValidVertex(v);
        return adjL(v).size();
    }

    void removeEdge(int v, int w){
        adj[v].erase(w);
        if (directed)
            adj[w].erase(v);
    }
};

ostream& operator<< (ostream& os, const Graph& adj){
    int V = adj.getV();
    int E = adj.getE();
    os << "V = " << V << ", E = " << E << endl;
    for (int i = 0; i < V; ++i){
        os << i << ": ";
        for (auto x : adj.adjL(i)){
            os << x << ' ';
        }
        os << endl;
    }
    return os;
}

#endif 