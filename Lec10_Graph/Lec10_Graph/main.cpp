#include "AdjMatGraph.h"		// 그래프 클래스 포함

int main()
{
    //AdjMatGraph g;		// 새로운 그래프 객체 생성
    SrchAMGraph g;		// 새로운 그래프 객체 생성

    for (int i = 0; i < 4; i++)
        g.insertVertex('A' + i);	// 정점 삽입: 'A' 'B', ...
    g.insertEdge(0, 1);      	// 간선 삽입
    g.insertEdge(0, 3);
    g.insertEdge(1, 2);
    g.insertEdge(1, 3);
    g.insertEdge(2, 3);

    printf("인접 행렬로 표현한 그래프\n");
    g.display();

    FILE* fp;
    fopen_s(&fp, "../text_out.txt", "w");
    g.display(fp);
    fclose(fp);

    printf("DFS ==> ");
    g.resetVisited();
    g.DFS(0);
    printf("\n");

    return 0;
}