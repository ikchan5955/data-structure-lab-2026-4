#include "WGraphMST.h"
void main()
{
	WGraphMST g;
	g.load("graph.txt");
	// printf("입력 그래프: graph.txt\n");
	// g.display("graph.txt");
	printf("MST By Kruskal’s Algorithm\n");
	g.Kruskal();
}
