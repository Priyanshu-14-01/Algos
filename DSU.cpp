#include <bits/stdc++.h>
#include <chrono>
using namespace std;    
using namespace chrono;

/*
    DSU is a data structure that is used to represent a set of elements.
    It is used to represent a set of elements that are connected to each other.


    1    2   3   4 are 4 different sets currently having 1,2,3,4 as their parent respectively(basically just one element in one set).
    So we are using DSU to represent these sets.
    We can represent these sets in two ways:
    1. By rank
    2. By size

    By rank:
    We will keep track of the rank of each set.
    The rank of a set is the number of elements in the set.
    The rank of a set is the number of elements in the set. 

    By size:
    We will keep track of the size of each set.
    The size of a set is the number of elements in the set.
    The size of a set is the number of elements in the set. 

    We will use the strategy to decide which way to represent the sets.
    If the strategy is "rank", we will use the rank to represent the sets.
    If the strategy is "size", we will use the size to represent the sets.

    We will use the union by rank or union by size to merge the sets.
    If the strategy is "rank", we will use the rank to merge the sets.
    If the strategy is "size", we will use the size to merge the sets.

    Union by rank:
    We will merge the set with the smaller rank into the set with the larger rank.
    If the ranks are the same, we will merge the set with the smaller rank into the set with the larger rank.
    If the strategy is "rank", we will use the rank to merge the sets.
    If the strategy is "size", we will use the size to merge the sets.

    Union by size:
    We will merge the set with the smaller size into the set with the larger size.
    If the sizes are the same, we will merge the set with the smaller size into the set with the larger size.
    If the strategy is "rank", we will use the rank to merge the sets.
    If the strategy is "size", we will use the size to merge the sets.

    */

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