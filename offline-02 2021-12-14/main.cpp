#include<bits/stdc++.h>
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

void findDijkstraPath(vector< pair<double,int> > adj_list[], int n, int s, int d)
{
    int parent[n];
    double dist[n];
    bool visited[n];

    //  initialize single source
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

        for(const pair<double,int> &adj_vertex : adj_list[u]){
            int v = adj_vertex.second;
            double w = adj_vertex.first;
            // relax
            if(visited[v] == false
                && dist[v] > (dist[u] + w)){
                    dist[v] = dist[u] + w;
                    parent[v] = u;
                }
        }

        visited[u] = true;
    }

    // cout << "distance from " << s << " to " << d << " is " << dist[d] << endl;
    printPath(dist, parent, s, d);
}

void findBellmanFordPath(vector< pair<double,int> > adj_list[], int n, int s, int d)
{
    int parent[n];
    double dist[n];
    bool visited[n];

    // initialize single source
    for(int i=0; i<n; i++){
        dist[i] = DBL_MAX;
        visited[i] = false;
        parent[i] = -1;
    }

    dist[s] = 0;

    for(int i=0; i<n-1; i++){
        int u = findMinDistance(dist, visited, n);

        for(const pair<double,int> &adj_vertex : adj_list[u]){
            int v = adj_vertex.second;
            double w = adj_vertex.first;
            // relax
            if(visited[v] == false
                && dist[v] > (dist[u] + w)){
                    dist[v] = dist[u] + w;
                    parent[v] = u;
                }
        }

        visited[u] = true;
    }

    // check for negative cycles
    for(int i=0; i<n; i++){
        for(const pair<double,int> &adj_vertex : adj_list[i]){
            int j = adj_vertex.second;
            double w = adj_vertex.first;
            if(dist[j] > (dist[i] + w)){
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
    // ifstream cin("dijkstra.in");
    // ifstream cin("bf1.in");
    ifstream cin("bf2.in");

    int n, m;
    cin >> n >> m;

    // priority_queue<Edge, vector<Edge>, CompareEdge > EdgeListPrim;
    // vector<int>* adj_list = new vector<int>[n];
    vector< pair<double,int> > adj_list[n];

    int u, v;
    double w;

    for(int i=0; i<m; i++){
        cin >> u >> v >> w;
        adj_list[u].push_back(make_pair(w,v));
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

    // findDijkstraPath(adj_list, n, s, d);
    findBellmanFordPath(adj_list, n, s, d);
}