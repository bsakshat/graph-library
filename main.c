#include <stdio.h>

#include "graph.h"

int main(){
	Graph *gr = graph_initialize();
	//char file1[] = "file.txt";
	//char file2[] = "c.txt";
	graph_add_vertex(gr, 0);
	graph_add_vertex(gr, 1);
	graph_add_vertex(gr, 2);
	graph_add_vertex(gr, 3);
	graph_add_vertex(gr, 4);
	graph_add_vertex(gr, 5);
	graph_add_vertex(gr, 6);
	graph_add_edge(gr, 0, 1, 1);
	graph_add_edge(gr, 0, 2, 1);
	graph_add_edge(gr, 0, 4, 3);
	graph_add_edge(gr, 1, 3, 1);
	graph_add_edge(gr, 3, 3, 9);
	graph_add_edge(gr, 3, 5, 2);
	graph_add_edge(gr, 3, 0, 5);
	graph_add_edge(gr, 4, 0, 3);
	printf("No. of vertices: %d\n", graph_num_vertices(gr));
	printf("No. of edges: %d\n", graph_num_edges(gr));
	printf("Total Weight: %d\n", graph_total_weight(gr));
	printf("Degree of 3: %d\n", graph_get_degree(gr, 3));
	printf("Edge Weight of 3 -> 2 is: %d\n", graph_get_edge_weight(gr, 3, 2));
	printf("Edge weight of 3 -> 5 is: %d\n", graph_get_edge_weight(gr, 3, 5));
	//graph_save_file(gr, file1);
	//graph_output_dot(gr, file2);
	//graph_load_file(gr, file1);
	int *suc = graph_get_predecessors(gr, 3);
	int i = 0;
	printf("Predecessors: ");
	while (suc[i] != -1){
		printf("%d ", suc[i]);
		i++;
	}	
	printf("\n");
	printf("Path from 0 to 0: %d\n", graph_has_path(gr, 0, 0));
	printf("Path from 3 to 3: %d\n", graph_has_path(gr, 3, 3));
	printf("Path from 1 to 1: %d\n", graph_has_path(gr, 1, 1));
	printf("Path from 2 to 2: %d\n", graph_has_path(gr, 2, 2));
	printf("Path from 4 to 4: %d\n", graph_has_path(gr, 4, 4));
	printf("Path from 5 to 5: %d\n", graph_has_path(gr, 5, 5));
	printf("Path from 3 to 1: %d\n", graph_has_path(gr, 3, 1));
	printf("Path from 3 to 4: %d\n", graph_has_path(gr, 3, 4));
	printf("Path from 0 to 6: %d\n", graph_has_path(gr, 0, 6));
	printf("Path from 1 to 6: %d\n", graph_has_path(gr, 1, 6));
	graph_print(gr);
	return 0;
}