#include<bits/stdc++.h>

using namespace std;

// void addEdge(vector<pair<int,float>> adj[], int u, int v, float wt)
void addEdge(vector<vector<int>> edgeListKruskal, int u, int v, int wt)
{
    edgeListKruskal.push_back( {wt, u, v} );
}

class DSU
{
    int *parent;
    int *rank;
 
public:
    DSU(int n)
    {
        parent = new int[n];
        rank = new int[n];
 
        for (int i = 0; i < n; i++)
        {
            parent[i] = -1;
            rank[i] = 1;
        }
    }
 
    // Find function
    int find(int i)
    {
        if (parent[i] == -1)
            return i;
 
        return parent[i] = find(parent[i]);
    }
    // union function
    void unite(int x, int y)
    {
        int s1 = find(x);
        int s2 = find(y);
 
        if (s1 != s2)
        {
            if (rank[s1] < rank[s2])
            {
                parent[s1] = s2;
                rank[s2] += rank[s1];
            }
            else
            {
                parent[s2] = s1;
                rank[s1] += rank[s2];
            }
        }
    }
};

int findKruskalsMST(vector<vector<int>> edgeListKruskal, int n, int m)
{
    sort(edgeListKruskal.begin(), edgeListKruskal.end());

    DSU s(n);
    int result = 0;
    for(auto edge: edgeListKruskal){
        int wt = edge[0];
        int u = edge[1];
        int v = edge[1];

        if(s.find(u) != s.find(v)){
            s.unite(u,v);
            result += wt;
        }

    }

    return result;
}



int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> edgeListKruskal;

    for(int i=0; i<m; i++){
        int u, v;
        float wt;
        cin >> u >> v >> wt;
        // cout << u << " " << v << " " << " " << wt << endl;

        addEdgeKruskal(edgeListKruskal, u, v, wt);
    }

    // printGraph(adj, n);

    // findPrimMST(adj, n, m);
}