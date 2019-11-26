#include <stdio.h>

#include "graph.h"

int main(){
	Graph *gr = graph_initialize();
	char file[] = "file.txt";
	graph_load_file(gr, file);
	graph_print(gr);
	return 0;
}