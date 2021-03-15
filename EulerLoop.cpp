#include <iostream>
#include <vector>
#include <stack>
#include "Graph.h"
using namespace std;

class EulerLoop{

private:
    Graph g;

public:
    EulerLoop(const Graph& g):g(g){}

    bool hasEulerLoop(){
        for (int i = 0; i < g.getV(); ++i){
            if (g.degree(i)%2 == 1)
                return false;
        }
        return true;
    }

    vector<int> result(){
        vector<int> ans;
        if (!hasEulerLoop())
            return ans;
        stack<int> s;
        int curv = 0;
        s.push(curv);

        while (!s.empty()){
            if (g.degree(curv) != 0){
                cout << "curv is " << curv << endl;
                s.push(curv);
                cout << "the size of s is " << s.size() << endl;
                for (auto x : g.adjL(curv)){
                    g.removeEdge(curv, x);
                    curv = x;
                    break;
                }
            }
            else {
                ans.push_back(curv);
                curv = s.top();
                s.pop();
            }
        }
        return ans;
    }
};

int main(){
    Graph g("eulergraph.txt");
    EulerLoop el(g);
    vector<int> ans = el.result();
    for (int x : ans){
        cout << x << ' ';
    }
    cout << endl;
    return 0;
}