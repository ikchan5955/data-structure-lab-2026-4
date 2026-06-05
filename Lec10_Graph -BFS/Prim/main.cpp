#include "WGraphMST.h"
#include "WGraphPrim.h"
#include "WGraphDijkstra.h"

int main() {
    // WGraphMST f;
    // f.load("graph.txt");
    // printf("MST By Kruskal's Algorithm\n");
    // f.Kruskal();

    WGraphPrim g;
    g.load("graph.txt");
    printf("MST By Prim's Algorithm\n");
    g.Prim(0);
    // return 0;

    WGraphDijkstra h;
    h.load("graph_sp.txt");
    printf("Shortest Path By Dijkstra Algorithm\n");
    h.ShortestPath(0);
    return 0;
}
