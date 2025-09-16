#include <bits/stdc++.h>
using namespace std;

void MSTKrushkal(vector<vector<pair<int,int>>> &Graph){
    
    vector<int> parent(n+1);
    vector<int> rank(n+1);
    vector<int> size(n+1);
    for(int i=1;i<=n;i++){
        parent[i] = i;
        rank[i] = 0;
    }
    for(int i=1;i<=n;i++){
        size[i] = 1;
    }
    for(auto &edge : Graph){
        int u = edge.first;
        int v = edge.second;
        int w = edge.third;
        int u_parent = findSet(u);
        int v_parent = findSet(v);
        if(u_parent != v_parent){
            unionSets(u_parent,v_parent,"rank");
        }
    }

    for(int i=1;i<=n;i++){
        cout<<parent[i]<<" "<<rank[i]<<endl;
    }

}

void MSTPrim(vector<vector<pair<int,int>>> &Graph){
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({0,1});
    while(!pq.empty()){
        pair<int,int> current = pq.top();
        pq.pop();
        cout<<current.first<<" ";
        for(auto &child : Graph[current.first]){
            if(child.first != current.second){
                pq.push({child.second,child.first});
            }
        }
    }
}

int main(){
    int n,m;
    cin>>n>>m;

    vector<int> U(n+1);
    vector<int> V(m+1);
    vector<int> W(m+1);

    vector<vector<pair<int,int>>> Graph(n+1);

    for(int i=1;i<=m;i++){
        cin>>U[i]>>V[i]>>W[i];
        Graph[U[i]].push_back(make_pair(V[i],W[i]));
        Graph[V[i]].push_back(make_pair(U[i],W[i])); 
    }

}