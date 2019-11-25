#include <stdio.h>

#include "graph.h"

int main(){
	Graph *gr = graph_initialize();
	graph_print(gr);
	return 0;
}