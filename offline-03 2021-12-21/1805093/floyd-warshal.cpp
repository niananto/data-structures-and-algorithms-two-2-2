#include<bits\stdc++.h>

using namespace std;

#define INF 100001

void findFW(double** graph, int n)
{
    for(int k=0; k<n; k++){
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                if(graph[i][k] != INF && graph[k][j] != INF && graph[i][j] > (graph[i][k]+graph[k][j])){
                    graph[i][j] = graph[i][k]+graph[k][j];
                }
            }
        }
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(graph[i][j] == INF){
                cout << "INF\t";
                continue;
            }
            cout << graph[i][j] << "\t";
        }
        cout << endl;
    }
}

int main()
{
    freopen("fw2.in","r",stdin);

    int n, m;
    cin >> n >> m;

    double** graph = new double*[n];
    for(int i=0; i<n; i++){
        graph[i] = new double[n];
        for(int j=0; j<n; j++){
            graph[i][j] = INF;
        }
        graph[i][i] = 0;
    }

    int u, v;
    double w;
    for(int i=0; i<m; i++){
        cin >> u >> v >> w;
        graph[u-1][v-1] = w;
        // cout << w;
    }

    findFW(graph, n);

    for(int i=0; i<n; i++){
        delete[] graph[i];
    }
    delete[] graph;

    return 0;
}