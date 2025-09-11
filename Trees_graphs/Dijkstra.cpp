#include <bits/stdc++.h>
using namespace std;

void Dijkstra(int node, vector<vector<pair<int,int>>> &Graph,vector<int> &D){
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq; // min-heap
    vector<bool> visited(Graph.size(), false);
    
    D[node] = 0; // Initialize source distance to 0
    pq.push({0,node});
    
    while(!pq.empty()){
        pair<int,int> cur = pq.top();
        pq.pop();
        
        int dist = cur.first;
        int u = cur.second;
        
        if(visited[u]) continue; // Skip if already visited
        visited[u] = true;
        
        for(auto child: Graph[u]){
            int v = child.first;
            int weight = child.second;
            
            if(!visited[v] && D[v] > D[u] + weight){
                D[v] = D[u] + weight;
                pq.push({D[v], v});
            }
        }
    }
}


int main(){
    int n,m,source;
    cin>>n>>m>>source;
    vector<vector<pair<int,int>>> Graph(n+1);
    vector<int> D(n+2,INT_MAX);

    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        Graph[u].push_back({v,w});
        Graph[v].push_back({u,w});
    }

    Dijkstra(source,Graph,D);
    
    // Print shortest distances from source to all nodes
    for(int i = 1; i <= n; i++){
        if(D[i] == INT_MAX){
            cout << "Node " << i << ": INF" << endl;
        } else {
            cout << "Node " << i << ": " << D[i] << endl;
        }
    }
    
    return 0;
}