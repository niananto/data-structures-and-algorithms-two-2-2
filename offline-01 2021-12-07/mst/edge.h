#pragma once
#include <iostream>

class Edge
{
public:
    int u;
    int v;
    double w;

    Edge(int U = -1, int V = -1, double W = 0) : u(U), v(V), w(W) {}
    ~Edge() {}
    bool operator<(Edge that) { return this->w < that.w; }
    bool operator>(Edge that) { return this->w > that.w; }
    friend std::ostream &operator<<(std::ostream &stream, Edge e);
};

std::ostream &operator<<(std::ostream &stream, Edge e)
{
    //stream << "(" << e.u << "-" << e.v << " , " << e.w << ")";
    stream << "(" << e.u << "," << e.v << ")";
    return stream;
}

struct CompareEdge{
    bool operator()(Edge const& edge1, Edge const& edge2)
    {
        return edge1.w > edge2.w;
    }
};

