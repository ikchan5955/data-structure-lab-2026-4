class WGraphMST : public WGraph {
public:
	void Kruskal() { // kruskal의 최소 비용 신장 트리 프로그램
		MinHeap heap;
		for (int i = 0; i < size - 1; i++)
			for (int j = i + 1; j < size; j++)
				if (hasEdge(i, j))
					heap.insert(getEdge(i, j), i, j); // 모든 간선 삽입
		VertexSets set(size); // size개의 집합을 만듦
		int edgeAccepted = 0; // 선택된 간선의 수
		while (edgeAccepted < size - 1) { // 간선의 수 < (size-1)
			HeapNode& e = heap.remove();
			int uset = set.findSet(e.getV1());
			int vset = set.findSet(e.getV2());
			if (uset != vset) {
				printf("간선 추가 : %c - %c (비용:%d)\n",
					getVertex(e.getV1()), getVertex(e.getV2()), e.getKey());
				set.unionSets(uset, vset); // 두개의 집합을 합함.
				edgeAccepted++;
			}
		}
	}
};