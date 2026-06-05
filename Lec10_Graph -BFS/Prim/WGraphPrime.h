class WGraphPrim : public WGraph {
public:
    // MST에 포함되지 않은 정점들 중에서
    // MST와의 거리(dist)가 최소인 정점 선택
    int getMinVertex(bool* selected, int* dist) {
        int minv = 0;
        int mindist = INF;
        for (int v = 0; v < size; v++) {
            if (!selected[v] && dist[v] < mindist) {
                mindist = dist[v];
                minv = v;
            }
        }
        return minv;
    }

    // Prim의 최소 비용 신장 트리: 정점 s에서 시작
    void Prim(int s) {
        bool selected[MAX_VTXS];    // 정점이 이미 포함되었는지
        int dist[MAX_VTXS];         // MST와의 거리

        for (int i = 0; i < size; i++) {    // 배열 초기화
            dist[i] = INF;
            selected[i] = false;
        }
        dist[s] = 0;                        // 시작 정점

        for (int i = 0; i < size; i++) {
            int u = getMinVertex(selected, dist);
            selected[u] = true;
            if (dist[u] == INF) return;     // 연결되지 않은 그래프
            printf("%c ", getVertex(u));

            for (int v = 0; v < size; v++) {
                if (getEdge(u, v) != INF) {
                    if (!selected[v] && getEdge(u, v) < dist[v]) {
                        dist[v] = getEdge(u, v);
                    }
                }
            }
        }
        printf("\n");
    }
};