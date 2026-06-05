#pragma once
#include <iostream>
#include <fstream>
#include <cstdio>

#define MAX_VTXS 100
#define INF 9999

class WGraph {
protected:
    int size;
    char vertices[MAX_VTXS];
    int adj[MAX_VTXS][MAX_VTXS];

public:
    WGraph() { reset(); }

    void reset() {
        size = 0;
        for (int i = 0; i < MAX_VTXS; i++) {
            for (int j = 0; j < MAX_VTXS; j++) {
                adj[i][j] = (i == j) ? 0 : INF;
            }
        }
    }

    char getVertex(int i) { return vertices[i]; }
    int getEdge(int i, int j) { return adj[i][j]; }

    void load(const char* filename) {
        std::ifstream fp(filename);
        if (!fp.is_open()) {
            printf("Error: 파일을 열 수 없습니다 (%s)\n", filename);
            return;
        }
        reset();
        fp >> size;
        for (int i = 0; i < size; i++) {
            fp >> vertices[i];
        }
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                fp >> adj[i][j];
            }
        }
        fp.close();
    }
};