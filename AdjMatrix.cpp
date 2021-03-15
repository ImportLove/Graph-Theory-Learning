#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cassert>
using namespace std;

class AdjMatrix{
private:
    int V;
    int E;
    int** adj;

    void isValidVertex(int v) const{
        assert(v >= 0 && v < V);
    }

public:
    AdjMatrix(string file):V(0), E(0), adj(nullptr){
        ifstream f;
        f.open(file);
        int node1, node2;

        f >> V >> E;
        adj = new int*[V];
        for (int i = 0; i < V; ++i){
            adj[i] = new int[V];
        }

        while (f >> node1 >> node2){
            adj[node1][node2] = 1;
            adj[node2][node1] = 1;
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
        return adj[i][j] == 1;
    }

    int getEle(int i, int j) const{
        isValidVertex(i);
        isValidVertex(j);
        return adj[i][j];
    }

    // return the adjacent nodes of node v
    vector<int> adjL(int v){
        isValidVertex(v);
        vector<int> ans;
        for (int i = 0; i < V; ++i){
            if (adj[v][i] == 1)
                ans.push_back(i);
        }
        return ans;
    }

    int degree(int v){
        isValidVertex(v);
        return adjL(v).size();
    }

    ~AdjMatrix(){
        for (int i = 0; i < V; ++i){
            delete[] adj[i];
        }

        delete[] adj;
    }
};

ostream& operator<< (ostream& os, const AdjMatrix& adj){
    int V = adj.getV();
    int E = adj.getE();
    os << "V = " << V << ", E = " << E << endl;
    for (int i = 0; i < V; ++i){
        for (int j = 0; j < V; ++j){
            os << adj.getEle(i, j) << ' ';
        }
        os << endl;
    }
    return os;
}

int main(){
    AdjMatrix adj("g.txt");
    cout << adj;

    return 0;
}