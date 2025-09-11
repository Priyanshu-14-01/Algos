#include <bits/stdc++.h>
using namespace std;

void BFS(int node,int parent, vector<vector<pair<int,int>>> &Tree){
    queue<pair<int,int>> q;
    q.push({node,parent});
    while(!q.empty()){
        pair<int,int> current = q.front();
        cout<<current.first<<" ";
        q.pop();
        for(auto &child : Tree[current.first]){
            if(child.first != current.second){
                q.push({child.first,current.first});
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

    vector<vector<pair<int,int>>> Tree(n+1);

    for(int i=1;i<=m;i++){
        cin>>U[i]>>V[i]>>W[i];
        Tree[U[i]].push_back(make_pair(V[i],W[i]));
        Tree[V[i]].push_back(make_pair(U[i],W[i])); 
    }

    BFS(1,-1,Tree);
    return 0;
}