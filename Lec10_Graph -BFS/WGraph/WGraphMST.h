#pragma once
#include "WGraph.h"
#include <algorithm>

struct Edge {
    int u, v, weight;
    bool operator<(const Edge& s) const {
        return weight < s.weight;
    }
};

class WGraphMST : public WGraph {
    int parent[MAX_VTXS];

    int findSet(int i) {
        if (parent[i] == -1) return i;
        return findSet(parent[i]);
    }

    void unionSet(int i, int j) {
        int root_i = findSet(i);
        int root_j = findSet(j);
        if (root_i != root_j) parent[root_i] = root_j;
    }

public:
    void Kruskal() {
        int edgeCount = 0;
        Edge edges[MAX_VTXS * MAX_VTXS];

        for (int i = 0; i < size; i++) {
            for (int j = i + 1; j < size; j++) {
                if (adj[i][j] != INF && adj[i][j] != 0) {
                    edges[edgeCount++] = { i, j, adj[i][j] };
                }
            }
        }

        std::sort(edges, edges + edgeCount);
        for (int i = 0; i < size; i++) parent[i] = -1;

        int acceptedEdges = 0;
        for (int i = 0; i < edgeCount && acceptedEdges < size - 1; i++) {
            int u = edges[i].u;
            int v = edges[i].v;
            if (findSet(u) != findSet(v)) {
                printf("(%c, %c) %d\n", getVertex(u), getVertex(v), edges[i].weight);
                unionSet(u, v);
                acceptedEdges++;
            }
        }
    }
};