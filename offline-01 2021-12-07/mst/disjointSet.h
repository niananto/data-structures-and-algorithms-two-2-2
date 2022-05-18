#pragma once
#include <vector>

//TODO implement generic

class DisjointSet{
    int nodes;
    int *parent;
    int *rank;

public:
    DisjointSet(int nodes);
    ~DisjointSet();
    int find(int x);
    void link(int u,  int v);
    void connect(int x,  int y);
};


DisjointSet::DisjointSet(int n) : nodes(n){
    rank = new int[n];
    parent = new int[n];
    for (int i = 0; i < n; i++) parent[i] = i;
}

DisjointSet::~DisjointSet(){
    delete[] rank;
    delete[] parent;
}

int DisjointSet::find(int x){
    if (parent[x] == x)
        return x;
    return parent[x] = find(parent[x]);
}

void DisjointSet::link(int u,  int v){
    if (rank[u] > rank[v])
        parent[v] = u;
    else
    {
        parent[u] = v;
        if (rank[u] == rank[v])
            rank[v]++;
    }
}

void DisjointSet::connect(int x,  int y){
    link(find(x), find(y));
}