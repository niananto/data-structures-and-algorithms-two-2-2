#include <iostream>
#include <queue>
#include <vector>
#include <list>
#include <stdio.h>

using namespace std;

#define MAX 100000
#define pii pair <int,int>
#define pip pair <pii,int>
vector<int> wins;
vector<vector<int> > games;
vector<int> remaining;
int maxWins = 0 ;


bool BFS(vector<vector<int> > residualCapacity, int parent[], int source, int sink)
{
    //BFS for maxFlow
    int n = residualCapacity.size();
    bool visited[n];//= {};
    fill_n(visited, n, false);
    queue<int> Q;
    Q.push(source);
    visited[source]=true;
    bool foundPath=false;
    while(!Q.empty())
    {
        int current = Q.front();
        Q.pop();
        for( int v=0; v< n; v++)
        {
            int cost = residualCapacity[current][v];
            if(!visited[v] && cost>0)
            {
                parent[v]=current;
                visited[v]=true;
                Q.push(v);
                if(v==sink)
                {
                    foundPath=true;
                    break;
                }
            }
        }
    }
    return foundPath;
}

int maxFlow(vector<pip> capacity, int source, int sink, int n)
{
    int x = capacity.size();
    vector<vector<int> > residualCapacity (n, (vector<int> (n,0) ));
    for (int i = 0; i < x; i++)
    {
        int from = capacity[i].first.first;
        int to = capacity[i].first.second;
        int cap = capacity[i].second;
        residualCapacity[from][to] += cap;
    }


    int parent[n];
    //list<list<int> > augmentedPaths;
    int maxFlow=0;
    while(BFS(residualCapacity, parent, source, sink))
    {
        //list<int> augmentedPath;
        int flow = MAX;
        int v = sink;

        while(v!=source)
        {
            //augmentedPath.push_back(v);
            int u = parent[v];
            if(flow > residualCapacity[u][v])
                flow = residualCapacity[u][v];
            v=u;
        }
        //augmentedPath.push_back(source);
        //augmentedPath.reverse();
        //augmentedPaths.push_back(augmentedPath);
        maxFlow += flow;

        v=sink;
        while(v!=source)
        {
            int u = parent[v];
            residualCapacity[u][v] -= flow;
            //residualCapacity[v][u] -= flow;
            v=u;
        }
    }
    return maxFlow;
}

//create graph without the node we are checking if is eliminated
bool buildGraphFor(int id, int n)
{
    int maximumFlow = 0;
    int source = n;
    int sink = n+1;
    int gameNode = n+2;
    int currentMaxWins = wins[id] + remaining[id]; //


    vector<pip> edges;
    for (int i = 0; i < n; i++)
    {
        if (i == id || wins[i] + remaining[i] < maxWins)
        {
            continue;
        }

        for (int j = 0; j < i; j++)
        {
            if (j == id || games[i][j] == 0 || wins[j] + remaining[j] < maxWins)
            {
                continue;
            }
            maximumFlow +=games[i][j];

            edges.push_back( pip(pii(source,gameNode),games[i][j]));
            edges.push_back( pip(pii(gameNode,i),MAX) );
            edges.push_back( pip(pii(gameNode,j),MAX) );
            gameNode++;
        }
        int value = currentMaxWins - wins[i];
        edges.push_back( pip(pii(i,sink),value) );
    }


    int currentCap = maxFlow(edges, source, sink, gameNode);
    return (maximumFlow<=currentCap);
}

int main()
{
    int n, m, w, cases, a, b;
    cin>>cases;
    for(int c=1; c<=cases; c++)
    {
        cin>>n>>m;
        wins.resize(n);
        games.assign(n,(vector<int>(n, 0)));
        remaining.assign(n,0);
        bool teams[n];
        for(int t=0; t<n; t++)
        {
            cin>>w;
            wins[t]=w;
        }
        for(int p=0; p<m; p++)
        {
            cin>>a>>b;
            games[a-1][b-1] += 1;
            games[b-1][a-1] += 1;
            remaining[a-1]+=1;
            remaining[b-1]+=1;
        }

        for(int s=0; s<n; s++)
        {
            teams[s] = buildGraphFor(s, n);
        }
        cout<<"Case #"<<c<<": ";
        for(int o=0; o<n; o++)
        {
            if(teams[o])
                cout<<"yes ";
            else
                cout<<"no ";
        }
        cout<<endl;


    }
    return 0;
}