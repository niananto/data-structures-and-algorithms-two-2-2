#pragma once
#include <vector>
#include <iostream>
#include "edge.h"

class digraph
{
    int vertices;
    int edges;
    std::vector<bool> visited;
    std::vector<std::vector<Edge>> adj;

public:
    digraph(int, int);
    ~digraph();
    friend std::ostream &operator<<(std::ostream &stream, digraph g);
    //friend std::istream &operator>>(std::istream &stream, digraph &ob);
    void addEdge(int u, int v, double w);
    void DFS(int u);
};



digraph::digraph(int n, int e) : vertices(n), edges(e)
{
    adj.resize(vertices);
    std::vector<bool> visited(vertices, false);
}

digraph::~digraph()
{
    //*not needed becuase no pointers or dynamically allocated memory
}

std::ostream &operator<<(std::ostream &stream, digraph g)
{
    for (int i = 1; i <= g.vertices; i++)
    {
        stream << i << " - ";
        for (auto j : g.adj[i])
            stream << j << " ";
        stream << std::endl;
    }
    return stream;
}

void digraph::addEdge(int start, int end, double weight = 0)
{
    Edge edg(start,end,weight);
    adj[start].push_back(edg); 
}

void digraph::DFS(int u)
{
    visited[u] = true;
    std::cout << u << " ";

    for (auto e : adj[u]){
        if (!visited[e.v])
            DFS(e.v);
    }  
};