#ifndef EDGE_H_
#define EDGE_H_

#include <iostream>
using namespace std;
class Edge{

private:
    int v, w;

public:
    Edge(int v, int w):v(v), w(w){};
    int getV() const{
        return v;
    }

    int getW() const{
        return w;
    }
};

ostream& operator<< (ostream& os, const Edge& edge){
    os << edge.getV() << '-' << edge.getW();
    return os;
}

#endif
