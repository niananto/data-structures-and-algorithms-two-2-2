#include<bits/stdc++.h>
// #include "edge.h"
using namespace std;

int findMinDistance(double dist[], bool visited[], int n)
{
    int min_index = -1;
    double current_min_dist = DBL_MAX;
    for(int i=0; i<n; i++){
        if(visited[i] == false && dist[i] < current_min_dist){
            current_min_dist = dist[i];
            min_index = i;
        }
    }
    return min_index;
}

void printPath(double dist[], int parent[], int s, int d)
{
    int v = d;
    while(v != s){
        cout << v << " <- " << parent[v] << endl;
        v = parent[v];
    }
    cout << "cost " << dist[d] << endl;
}

void findDijkstraPath(double** adj, int n, int s, int d)
{
    int parent[n];
    double dist[n];
    bool visited[n];

    for(int i=0; i<n; i++){
        dist[i] = DBL_MAX;
        visited[i] = false;
        parent[i] = -1;
    }

    dist[s] = 0;
    // priority_queue < pair<double, int>, vector< pair<double, int> >, greater< pair<double, int> > > pq;
    // pq.push(make_pair(0,0));

    for(int i=0; i<n-1; i++){
        int u = findMinDistance(dist, visited, n);
        // cout << u;

        for(int v=0; v<n; v++){
            if(visited[v] == false
                && adj[u][v] != 0
                && dist[u] != DBL_MAX
                && dist[v] > (dist[u] + adj[u][v])){
                    dist[v] = dist[u] + adj[u][v];
                    parent[v] = u;
                }
        }

        visited[u] = true;
    }

    // cout << "distance from " << s << " to " << d << " is " << dist[d] << endl;
    printPath(dist, parent, s, d);
}

void findBellmanFordPath(double** adj, int n, int s, int d)
{
    int parent[n];
    double dist[n];
    bool visited[n];

    for(int i=0; i<n; i++){
        dist[i] = DBL_MAX;
        visited[i] = false;
        parent[i] = -1;
    }

    dist[s] = 0;

    for(int i=0; i<n-1; i++){
        int u = findMinDistance(dist, visited, n);

        for(int v=0; v<n; v++){
            if(visited[v] == false
                && adj[u][v] != 0
                && dist[u] != DBL_MAX
                && dist[v] > (dist[u] + adj[u][v])){
                    dist[v] = dist[u] + adj[u][v];
                    parent[v] = u;
                }
        }

        visited[u] = true;
    }

    // check for negative cycles
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(adj[i][j] && dist[i] != DBL_MAX && dist[i]+adj[i][j] < dist[j]){
                cout << "The graph contains a negative cycle" << endl;
                return;
            }
        }
    }

    // cout << "distance from " << s << " to " << d << " is " << dist[d] << endl;
    cout << "The graph does not contain a negative cycle" << endl;
    printPath(dist, parent, s, d);
}

int main()
{
    // ifstream cin("mst.in");
    // ifstream cin("bf1.in");
    ifstream cin("bf2.in");

    int n, m;
    cin >> n >> m;

    // priority_queue<Edge, vector<Edge>, CompareEdge > EdgeListPrim;
    double** adj = new double*[n];
    for(int i=0; i<n; i++){
        adj[i] = new double[n];
        for(int j=0; j<n; j++){
            adj[i][j] = 0;
        }
    }

    int u, v;
    double w;

    for(int i=0; i<m; i++){
        cin >> u >> v >> w;
        adj[u][v] = w;
        // adj[v][u] = w;
        // *(*(adj+u)+v) = w;
        // *(*(adj+v)+u) = w;
    }

    int s, d;
    cin >> s >> d;

    // cout << n << " " << m << endl;
    // for(int i=0; i<n; i++){
    //     for(int j=0; j<n; j++){
    //         if(adj[i][j]){
    //             cout << i << " " << j << " " << adj[i][j] << endl;
    //         }
    //     }
    // }
    // cout << s << " " << d << endl;

    // findDijkstraPath(adj, n, s, d);
    findBellmanFordPath(adj, n, s, d);
}