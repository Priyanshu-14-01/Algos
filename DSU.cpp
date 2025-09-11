#include <bits/stdc++.h>
#include <chrono>
using namespace std;    
using namespace chrono;

class DSU {
    private: 
    vector<int> parent;
    vector<int> rank;
    vector<int> size;
    string strategy;    


    public:
    DSU(int n,string strategy){
        parent.resize(n);
        rank.resize(n);
        size.resize(n);
        for(int i = 0; i < n; i++) {
            parent[i] = i;
            rank[i] = 0;
            size[i] = 1;
        }
    }

    void makeSet(int v){
        parent[v] = v;
        rank[v] = 0;
        size[v] = 1;
    }

    int findSet(int v){
        if(parent[v] == v) return v;
        return parent[v] = findSet(parent[v]);
    }

    void unionSets(int a, int b,string strategy){
        a = findSet(a);
        b = findSet(b);
        if(a != b){
            if(strategy == "rank"){
                if(rank[a] < rank[b]) swap(a, b);
            }
            else if(strategy == "size"){
                if(size[a] < size[b]) swap(a, b);
            }
            parent[b] = a;
            rank[a] += rank[b];
        }
    }
};

int main(){
    auto start = chrono::high_resolution_clock::now();
    int n = 5;
    string strategy = "rank";
    DSU dsu(n,strategy);
    dsu.unionSets(0,1,strategy);
    dsu.unionSets(2,3,strategy);
    dsu.unionSets(3,4,strategy);
    cout << dsu.findSet(0) << endl;
    cout << dsu.findSet(1) << endl;
    cout << dsu.findSet(2) << endl;
    cout << dsu.findSet(3) << endl;
    cout << dsu.findSet(4) << endl;
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Time taken: " << duration.count() << " milliseconds" << endl;

    start = chrono::high_resolution_clock::now();
    n = 10;
    strategy = "size";
    DSU dsu2(n,strategy);
    dsu2.unionSets(0,1,strategy);
    dsu2.unionSets(2,3,strategy);
    dsu2.unionSets(3,4,strategy);
    cout << dsu2.findSet(0) << endl;
    cout << dsu2.findSet(1) << endl;
    cout << dsu2.findSet(2) << endl;
    cout << dsu2.findSet(3) << endl;
    cout << dsu2.findSet(4) << endl;
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Time taken: " << duration.count() << " milliseconds" << endl;
    return 0;

}