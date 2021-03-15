#include <iostream>
#include <cassert>
#include <fstream>
#include <list>
#include <vector>
using namespace std;

class AdjList{
private:
    int V;
    int E;
    vector<list<int>> adj;

    void isValidVertex(int v) const{
        assert(v >= 0 && v < V);
    }

public:
    AdjList(string file){
        ifstream f;
        f.open(file);
        int node1, node2;

        f >> V >> E;
        adj = vector<list<int>>(V, list<int>());

        while (f >> node1 >> node2){
            adj[node1].push_back(node2);
            adj[node2].push_back(node1);
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
        for(auto x : adj[i]){
            if (x == j)
                return true;
        }
        return false;
    }

    // return the adjacent nodes of node v
    list<int> adjL(int v) const{
        isValidVertex(v);
        return adj[v];
    }

    int degree(int v){
        isValidVertex(v);
        return adjL(v).size();
    }
};

ostream& operator<< (ostream& os, const AdjList& adj){
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


int main(){
    AdjList adj("g.txt");
    cout << adj;
    return 0;
}