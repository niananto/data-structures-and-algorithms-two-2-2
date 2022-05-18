#include<bits/stdc++.h>
#include "edge.h"
#include "disjointSet.h"

using namespace std;

void printMST(vector<Edge> kruskalMST)
{
    double minimumWeight = 0;
    cout << "List of edges selected by Kruskal's:{ ";
    for(auto edge : kruskalMST){
        minimumWeight += edge.w;
        cout << edge << " ";
    }
    cout << " }" << endl;
    cout << "Cost of the minimum spanning tree : " << minimumWeight << endl;

}

// void findPrimMST(priority_queue<Edge, vector<Edge>, CompareEdge> edgeListPrim, double** adj, int n, int m)
vector<Edge> findPrimMST(double** adj, int n, int m)
{
    // int parent[n];
    // double key[n];
    bool visited[n];
    double minimumWeight = 0;

    for(int i=0; i<n; i++){
        // key[i] = DBL_MAX;
        visited[i] = false;
        // parent[i] = -1;
    }

    // key[0] = 0;
    // priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
    // pq.push(make_pair(0,0));
    vector<Edge> primMST;
    priority_queue<Edge, vector<Edge>, CompareEdge > edgeListPrim;
    for(int v=0; v<n; v++){
        if(adj[0][v]){
            edgeListPrim.push(Edge(0,v,adj[0][v]));
        }
    }
    visited[0] = true;

    while(!edgeListPrim.empty()){
        Edge ed = edgeListPrim.top();
        int u = ed.u;
        int v = ed.v;
        edgeListPrim.pop();
        if(visited[u] != true){
            for(int i=0; i<n; i++){
                if(adj[u][i]){
                    edgeListPrim.push(Edge(u,i,adj[u][i]));
                }
            }
            visited[u] = true;
            primMST.push_back(ed);
            // printMST(primMST);
        }
        else if(visited[v] != true){
            for(int i=0; i<n; i++){
                if(adj[v][i]){
                    edgeListPrim.push(Edge(v,i,adj[v][i]));
                }
            }
            visited[v] = true;
            primMST.push_back(ed);
            // printMST(primMST);
        }
    }

    return primMST;
}

vector<Edge> findKruskalMST(vector<Edge> edgeListKruskal, int n)
{
    sort(edgeListKruskal.begin(), edgeListKruskal.end());

    DisjointSet djs(n);
    vector<Edge> kruskalMST;
    double minimumWeight = 0;

    for(Edge edge : edgeListKruskal){
        if(djs.find(edge.u) != djs.find(edge.v)){
            djs.connect(edge.u, edge.v);
            kruskalMST.push_back(edge);
            minimumWeight += edge.w;
        }
    }
    
    // cout << "Cost of the minimum spanning tree : " << minimumWeight << endl;
    return kruskalMST;
}

int main()
{
    ifstream cin("mst.in");

    int n, m;
    cin >> n >> m;

    // priority_queue<Edge, vector<Edge>, CompareEdge > edgeListPrim;
    double** adj = new double*[n];
    for(int i=0; i<n; i++){
        adj[i] = new double[n];
    }
    vector<Edge> edgeListKruskal;

    int u, v;
    double w;

    for(int i=0; i<m; i++){
        cin >> u >> v >> w;
        // edgeListPrim.push(Edge(u,v,w));
        adj[u][v] = w;
        edgeListKruskal.push_back(Edge(u,v,w));
    }

    // findPrimMST(edgeListPrim, adj, n, m);
    printMST(findPrimMST(adj, n, m));

    vector<Edge> kruskalMST = findKruskalMST(edgeListKruskal, n);
    printMST(kruskalMST);

}