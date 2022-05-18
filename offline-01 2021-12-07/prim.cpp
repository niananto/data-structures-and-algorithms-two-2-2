#include<bits/stdc++.h>

using namespace std;

// void addEdge(vector<pair<int,float>> adj[], int u, int v, float wt)
void addEdge(float** adj, int u, int v, float wt)
{
    // adj[u].push_back(make_pair(v, wt));
    // // for undirected graph
    // adj[v].push_back(make_pair(u, wt));

    adj[u][v] = wt;
}

// Print adjacency list representation of graph
// void printGraph(vector<pair<int,float> > adj[], int V)
void printGraph(float** adj, int V)
{
    int v, w;
    for (int u = 0; u < V; u++)
    {
        cout << "Node " << u << " makes an edge with \n";
        // for (auto it = adj[u].begin(); it!=adj[u].end(); it++)
        // {
        //     v = it->first;
        //     w = it->second;
        //     cout << "\tNode " << v << " with edge weight ="
        //          << w << "\n";
        // }

        for (int v = 0; v < V; v++){
            if(adj[u][v]){
                cout << "\tNode " << v << " with edge weight ="
                    << adj[u][v] << endl;
            }
        }

        cout << "\n";
    }
}

int findMinKey(bool visited[], float key[], int n)
{
    float min = FLT_MAX;
    int minIndex;

    for(int i=0; i<n; i++){
        if(visited[i] == false && key[i] < min){
            min = key[i];
            minIndex = i;
        }
    }

    return minIndex;
}

// void printMST(vector<pair<int,float>> adj[], int n, int m, int parent[])
void printMST(float** adj, int n, int m, int parent[])
{
    cout << "V1\tV2\tWeight\n";
    // zeroth element has no parent
    for(int i=1; i<n; i++){
        // cout << parent[i] << "\t" << i << "\t";
        // for( auto it = adj[ parent[i] ].begin(); it != adj[ parent[i] ].end(); it++){
        //     if(it->first == i){
        //         cout << it->second << endl;
        //         break;
        //     }
        // }

        cout << parent[i] << "\t" << i << "\t" << adj[ parent[i] ][i] << endl;
    }
}

// void findPrimMST(vector<pair<int,float>> adj[], int n, int m)
void findPrimMST(float** adj, int n, int m)
{
    // key of a certain vertex means
    // that vertex can be visited by atleast that
    // cost from some node in the visited list
    int parent[n];
    float key[n];
    bool visited[n];

    // initialization
    for(int i=0; i<n; i++){
        key[i] = FLT_MAX;
        visited[i] = false;
    }

    key[0] = 0; // so that the code starts from here
    parent[0] = -1; // zeroth node is always the root. so it has no parent

    for(int _=0; _<n-1; _++){
        int u = findMinKey(visited, key, n);
        visited[u] = true;

        // updating parents and key values of u's adj vertices
        for(int v=0; v<n; v++){
            if(visited[v] == false){
                // for(auto it=adj[u].begin(); it!=adj[u].end(); it++){
                //     if(v == it->first && it->first < key[v]){
                //         parent[v] = u;
                //         key[v] = it->second;
                //         break;
                //     }
                // }

                if(adj[u][v] && adj[u][v] < key[v]){
                    parent[v] = u;
                    key[v] = adj[u][v];
                }
            }
        }
    }

    printMST(adj, n, m, parent);
}

int main()
{
    int n, m;
    cin >> n >> m;

    // vector<pair<int, float>> adj[n];
    float** adj = new float*[n];
    for(int i=0; i<n; i++){
        adj[i] = new float[n];
    }

    for(int i=0; i<m; i++){
        int u, v;
        float wt;
        cin >> u >> v >> wt;
        // cout << u << " " << v << " " << " " << wt << endl;

        addEdge(adj, u, v, wt);
    }

    // printGraph(adj, n);

    // findPrimMST(adj, n, m);
}