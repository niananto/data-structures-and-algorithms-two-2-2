#include <bits\stdc++.h>
using namespace std;

bool bfs(int** rGraph, int source, int sink, int n, int* parent)
{

    bool visited[n];
    for(int i=0; i<n; i++){
        visited[i] = false;
    }

    queue<int> q;
    q.push(source);
    visited[source] = true;
    parent[source] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < n; v++) {
            if (visited[v] == false && rGraph[u][v] > 0) {
                if (v == sink) {
                    parent[v] = u;
                    return true;
                }
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    return false;
}

int fordFulkerson(int** parentGraph, vector<pair <pair <int,int>,int> > edges, int source, int sink, int n)
{
    int u, v, capacity;

    int** rGraph = new int*[n];
    for(int i=0; i<n;i++){
        rGraph[i] = new int[n];
        for(int j=0; j<n; j++){
            rGraph[i][j] = 0;
        }
    }

    for(pair< pair<int, int>, int> &edge : edges){
        u = edge.first.first;
        v = edge.first.second;
        capacity = edge.second;
        rGraph[u][v] = capacity;
    }

    int* parent = new int[n];
    for(int i=0; i<n; i++){
        parent[i] = 0;
    }
    int max_flow = 0;

    while (bfs(rGraph, source, sink, n, parent)){
        for(int i=0; i<n; i++){
            // cout << parent[i] << " ";
        }

        int path_flow = INT_MAX;
        for(v = sink; v != source; v = parent[v]){
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }

        for(v = sink; v != source; v = parent[v]){
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        max_flow += path_flow;
    }

    for(int i=0; i<n; i++){
        delete[] rGraph[i];
    }
    delete[] rGraph;
    delete[] parent;
    
    return max_flow;
}

bool buildGraphFor(int id, int n, int** parentGraph, int* win, int* lose, int* left)
{
    int maximumFlow = 0;
    int source = n;
    int sink = n+1;
    int gameNode = n+2;
    int currentMaxWins = win[id] + left[id];
    
    vector<pair <pair <int,int>,int> > edges;
    for (int i = 0; i < n; i++){
        if (i == id){
            continue;
        }

        for (int j = 0; j < i; j++){
            // cout << "Hello " << id << i << j << endl;

            if (j == id || parentGraph[i][j] == 0){
                // cout << "continued" << endl;
                continue;
            }
            maximumFlow += parentGraph[i][j];

            edges.push_back(make_pair(make_pair(source,gameNode), parentGraph[i][j]));
            edges.push_back(make_pair(make_pair(gameNode, i), INT_MAX));
            edges.push_back(make_pair(make_pair(gameNode, j), INT_MAX));

            // cout << gameNode << i << j << parentGraph[i][j];
            // cout << maximumFlow;

            gameNode++;
        }

        int value = currentMaxWins - win[i];
        edges.push_back(make_pair(make_pair(i, sink), value));
    }


    int currentCapacity = fordFulkerson(parentGraph, edges, source, sink, gameNode);
    // cout << currentCapacity << " " << maximumFlow << endl;
    return (maximumFlow > currentCapacity);
}

// void reasoning(int id)
// {

// }

int main()
{
    freopen("input.txt", "r", stdin);
    // freopen(".\\baseball test cases\\teams29.txt", "r", stdin);
    int n;
    cin >> n;

    int** parentGraph = new int*[n];
    for(int i=0; i<n; i++){
        parentGraph[i] = new int[n];
    }

    string* nameOfTeams = new string[n];
    int* win = new int[n];
    int* lose = new int[n];
    int* left = new int[n];
    for(int i=0; i<n; i++){
        cin >> nameOfTeams[i] >> win[i] >> lose[i] >> left[i];
        for(int j=0; j<n; j++){
            cin >> parentGraph[i][j];
        }
    }

    // for(int i=0; i<n; i++){
    //     // cout << nameOfTeams[i] << " ";
    //     // cout << win[i] << " ";
    //     // cout << lose[i] << " ";
    //     // cout << left[i] << " ";
    //     for(int j=0; j<n; j++){
    //         cout << parentGraph[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    // if some team has already won more matches than other could
    // possibly win
    int topWins = 0;
    for(int j=0; j<n; j++){
        if(win[j] > topWins){
            topWins = win[j];
        }
    } // to be compared later

    // make graph for each team and evaluate it
    bool* teams = new bool[n];
    for(int id=0; id<n; id++){
        if(win[id] + left[id] < topWins){
            teams[id] = true;
            continue;
        }

        teams[id] = buildGraphFor(id, n, parentGraph, win, lose, left);
    }

    for(int i=0; i<n; i++){
        if(teams[i] == true){
            cout << nameOfTeams[i] << " is eliminated." << endl;
            // reasoning(i, );
        }
    }

    delete[] nameOfTeams;
    delete[] win;
    delete[] lose;
    delete[] left;
    delete[] teams;
    for(int i=0; i<n; i++){
        delete[] parentGraph[i];
    }
    delete[] parentGraph;

    return 0;
}