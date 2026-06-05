#pragma once
#include "WGraph.h"

class WGraphDijkstra : public WGraph {
    int choose(int dist[], bool found[]) {
        int minv = -1;
        int mindist = INF;
        for (int i = 0; i < size; i++) {
            if (!found[i] && dist[i] < mindist) {
                mindist = dist[i];
                minv = i;
            }
        }
        return minv;
    }

public:
    void ShortestPath(int start) {
        int dist[MAX_VTXS];
        bool found[MAX_VTXS];

        for (int i = 0; i < size; i++) {
            dist[i] = adj[start][i];
            found[i] = false;
        }
        found[start] = true;
        dist[start] = 0;

        for (int i = 0; i < size - 1; i++) {
            int u = choose(dist, found);
            if (u == -1 || dist[u] == INF) break;
            found[u] = true;

            for (int w = 0; w < size; w++) {
                if (!found[w] && adj[u][w] != INF) {
                    if (dist[u] + adj[u][w] < dist[w]) {
                        dist[w] = dist[u] + adj[u][w];
                    }
                }
            }
        }

        for (int i = 0; i < size; i++) {
            if (i != start) {
                printf("정점 %c 까지의 최단거리 = %d\n", getVertex(i), dist[i]);
            }
        }
    }
};