#ifndef WEIGHTED_EDGE_H_
#define WEIGHTED_EDGE_H_

#include <iostream>
using namespace std;
class WeightedEdge{

private:
    int v, w;
    int weight;

public:
    WeightedEdge(int v, int w, int weight):v(v), w(w), weight(weight){};
    int getV() const{
        return v;
    }

    int getW() const{
        return w;
    }

    int getWeight() const{
        return weight;
    }
};

ostream& operator<< (ostream& os, const WeightedEdge& edge){
    os << '(' << edge.getV() << '-' << edge.getW() << ": " << edge.getWeight() << ')';
    return os;
}

bool operator< (const WeightedEdge& lhs, const WeightedEdge& rhs){
    return lhs.getWeight() < rhs.getWeight();
}

bool operator> (const WeightedEdge& lhs, const WeightedEdge& rhs){
    return lhs.getWeight() > rhs.getWeight();
}

#endif