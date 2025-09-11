#include <bits/stdc++.h>
using namespace std;

void dfs(int node, int parent, vector<vector<pair<int,int>>> &Tree){
    cout<<node<<" ";
    for(auto &child : Tree[node]){
        if(child.first != parent){
            dfs(child.first,node,Tree);
        }
    }
}

int main(){

    int n,m;
    cin>>n>>m;

    vector<int> U(n+1);
    vector<int> V(m+1);
    vector<int> W(m+1);

    vector<vector<pair<int,int>>> Tree(n+1);

    for(int i=1;i<=m;i++){
        cin>>U[i]>>V[i]>>W[i];
        Tree[U[i]].push_back(make_pair(V[i],W[i]));
        Tree[V[i]].push_back(make_pair(U[i],W[i])); 
    }

    dfs(1,-1,Tree);
    return 0;
}