#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include "Graph.h"
using namespace std;

class WaterPuzzle{
private:
    vector<int> pre;
    int end;
public:
    void findAll(int a, int b, vector<int>& next){
        next.push_back(5*10 + b);
        next.push_back(a*10+3);
        next.push_back(b);
        next.push_back(a*10);
        next.push_back((a-min(3-b, a))*10 + b+min(3-b, a));
        next.push_back((a+min(5-a,b))*10 + b-min(5-a,b));
    }

    WaterPuzzle(){
        end = -1;
        pre = vector<int> (100, 0);
        queue<int> q;
        vector<bool> visited(100, false);
        q.push(0);
        visited[0] = true;

        while (!q.empty()){
            int cur = q.front();
            q.pop();
            int a = cur/10;
            int b = cur%10;
            // max a = 5, max b = 3;
            vector<int> next;
            findAll(a, b, next);

            for (int x : next){
                if (!visited[x]){
                    q.push(x);
                    visited[x] = true;
                    pre[x] = cur;
                    if (x/10 == 4 || x%10 == 4){
                        end = x;
                        return;
                    }     
                }
                    
            }
        }
    }

    vector<int> result() const{
        vector<int> ans;
        if (end == -1)
            return ans;
        
        int tmp = end;
        while (tmp != 0){
            ans.push_back(tmp);
            tmp = pre[tmp];
        }
        ans.push_back(tmp);
        reverse(ans.begin(), ans.end());
        return ans;
    }
};

int main(){
    WaterPuzzle wp;
    vector<int> ans = wp.result();
    cout << ans.size() << endl;
    for (int i = 0; i < int(ans.size()); ++i){
        cout << ans[i] << ' ';
    }
    cout << endl;
    return 0;
}