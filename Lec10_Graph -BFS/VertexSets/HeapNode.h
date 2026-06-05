// HeapNode.h: 힙에 저장할 노드 클래스
class HeapNode {
	int key; // Key 값: 간선의 가중치
	int v1; // 정점 1
	int v2; // 정점 2
public:
	HeapNode(int k, int u, int v) : key(k), v1(u), v2(v) { }
	void setKey(int k) { key = k; }
	int getKey() { return key; }
	int getV1() { return v1; }
	int getV2() { return v2; }
};