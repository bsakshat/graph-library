#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"

/*
-1 = no vertex
0 = no edge or existent vertex with no self loop
no. greater than 0 = edge with that no as weight value
*/

Graph *graph_initialize(){
	int i = 0;
	int j = 0;
	Graph *new = malloc(sizeof(Graph));
	if (new == NULL){
		return NULL;
	}
	new->max_vertex = -1;
	for (i = 0; i < MAX_VERTICES; i++){
		for (j = 0; j < MAX_VERTICES; j++){
			if (i == j){
				new->adj_matrix[i][j] = -1;
			}
			else{
				new->adj_matrix[i][j] = 0;
			}			
		}
	}
	for (i = 0; i < MAX_VERTICES; i++){
		new->visited[i] = -1;
	}
	return new;
}

int graph_add_vertex(Graph *graph, int v1){
	if (v1 < 0 || v1 >= MAX_VERTICES || graph == NULL){
		return -1;
	}
	static int max = -1;
	if (graph->adj_matrix[v1][v1] >= 0){
		return 0;
	}
	else{
		graph->adj_matrix[v1][v1] = 0;
		if (v1 > max){
			max = v1;
			graph->max_vertex = max;
		}
		return 0;
	}
}

int graph_contains_vertex(Graph *graph, int v1){
	if (v1 < 0 || v1 >= MAX_VERTICES || graph == NULL){
		return 0;
	}
	if (graph->adj_matrix[v1][v1] >= 0){
		return 1;
	}
	else{
		return 0;
	}
}

int graph_remove_vertex(Graph *graph, int v1){
	if (v1 < 0 || v1 >= MAX_VERTICES || graph == NULL){
		return -1;
	}
	if (graph->adj_matrix[v1][v1] == -1){
		return 0;
	}
	else{
		int i = 0;
		for (i = 0; i < MAX_VERTICES; i++){
			graph->adj_matrix[v1][i] = 0;
			graph->adj_matrix[i][v1] = 0;
		}
		graph->adj_matrix[v1][v1] = -1;
		return 0;
	}
}

int graph_add_edge(Graph *graph, int v1, int v2, int wt){
	if (graph == NULL || wt <= 0){
		return -1;
	}
	if (v1 < 0 || v1 >= MAX_VERTICES || v2 < 0 || v2 >= MAX_VERTICES){
		return -1;
	}
	if (graph->adj_matrix[v1][v1] == -1 || graph->adj_matrix[v2][v2] == -1){
		return -1;
	}
	else{
		graph->adj_matrix[v1][v2] = wt;
		return 0;
	}
}

int graph_contains_edge(Graph *graph, int v1, int v2){
	if (graph == NULL){
		return 0;
	}
	if (v1 < 0 || v1 >= MAX_VERTICES || v2 < 0 || v2 >= MAX_VERTICES){
		return 0;
	}
	if (graph->adj_matrix[v1][v1] == -1 || graph->adj_matrix[v2][v2] == -1){
		return 0;
	}
	else if (graph->adj_matrix[v1][v2] <= 0){
		return 0;
	}
	else{
		return 1;
	}
}

int graph_remove_edge(Graph *graph, int v1, int v2){
	if (graph == NULL){
		return -1;
	}
	if (v1 < 0 || v1 >= MAX_VERTICES || v2 < 0 || v2 >= MAX_VERTICES){
		return -1;
	}
	if (graph->adj_matrix[v1][v1] == -1 || graph->adj_matrix[v2][v2] == -1){
		return -1;
	}
	else if (graph->adj_matrix[v1][v2] <= 0){
		return 0;
	}
	else{
		graph->adj_matrix[v1][v2] = 0;
		return 0;
	}
}

int graph_num_vertices(Graph *graph){
	if (graph == NULL){
		return -1;
	}
	int i = 0;
	int count = 0;
	for (i = 0; i < MAX_VERTICES; i++){
		if (graph->adj_matrix[i][i] >= 0){
			count++;
		} 
	}
	return count;
}

int graph_num_edges(Graph *graph){
	if (graph == NULL){
		return -1;
	}
	int i = 0;
	int j = 0;
	int count = 0;
	for (i = 0; i < MAX_VERTICES; i++){
		for (j = 0; j < MAX_VERTICES; j++){
			if (graph->adj_matrix[i][j] > 0){
				count++;
			}
		}
	}
	return count;
}

int graph_total_weight(Graph *graph){
	if (graph == NULL){
		return -1;
	}
	int i = 0;
	int j = 0;
	int total = 0;
	for (i = 0; i < MAX_VERTICES; i++){
		for (j = 0; j < MAX_VERTICES; j++){
			if (graph->adj_matrix[i][j] > 0){
				total += graph->adj_matrix[i][j];
			}
		}
	}
	return total;
}

int graph_get_degree(Graph *graph, int v1){
	if (v1 < 0 || v1 >= MAX_VERTICES || graph == NULL){
		return -1;
	}
	if (graph->adj_matrix[v1][v1] == -1){
		return -1;
	}
	else{
		int i = 0;
		int degree = 0;
		for (i = 0; i < MAX_VERTICES; i++){
			if (graph->adj_matrix[v1][i] > 0 || graph->adj_matrix[i][v1] > 0){
				degree++;
			}
		}
		if (graph->adj_matrix[v1][v1] > 0){
			degree++;
		}
		return degree;
	}
}

int graph_get_edge_weight(Graph *graph, int v1, int v2){
	if (graph == NULL){
		return -1;
	}
	if (v1 < 0 || v1 >= MAX_VERTICES || v2 < 0 || v2 >= MAX_VERTICES){
		return -1;
	}
	if (graph->adj_matrix[v1][v1] == -1 || graph->adj_matrix[v2][v2] == -1){
		return -1;
	}
	else if (graph->adj_matrix[v1][v2] <= 0){
		return -1;
	}
	else{
		return graph->adj_matrix[v1][v2];
	}
}

int graph_is_neighbor(Graph *graph, int v1, int v2){
	if (graph == NULL){
		return 0;
	}
	if (v1 < 0 || v1 >= MAX_VERTICES || v2 < 0 || v2 >= MAX_VERTICES){
		return 0;
	}
	if (graph->adj_matrix[v1][v1] == -1 || graph->adj_matrix[v2][v2] == -1){
		return 0;
	}
	else if (graph->adj_matrix[v1][v2] <= 0 && graph->adj_matrix[v2][v1] <= 0){
		return 0;
	}
	else{
		return 1;
	}
}

int *graph_get_predecessors(Graph *graph, int v1){
	if (v1 < 0 || v1 >= MAX_VERTICES || graph == NULL){
		return NULL;
	}
	if (graph->adj_matrix[v1][v1] == -1){
		return NULL;
	}
	int i = 0;
	int index = 0;
	int *pred = malloc(sizeof(int) * MAX_VERTICES);
	for (i = 0; i < MAX_VERTICES; i++){
		pred[i] = -1;
	}
	for (i = 0; i < MAX_VERTICES; i++){
		if (i == v1){
			continue;
		}
		if (graph->adj_matrix[i][v1] > 0){
			pred[index] = i;
			index++;
		}
	}
	return pred;
}

int *graph_get_successors(Graph *graph, int v1){
	if (v1 < 0 || v1 >= MAX_VERTICES || graph == NULL){
		return NULL;
	}
	if (graph->adj_matrix[v1][v1] == -1){
		return NULL;
	}
	int i = 0;
	int index = 0;
	int *pred = malloc(sizeof(int) * MAX_VERTICES);
	for (i = 0; i < MAX_VERTICES; i++){
		pred[i] = -1;
	}
	for (i = 0; i < MAX_VERTICES; i++){
		if (i == v1){
			continue;
		}
		if (graph->adj_matrix[v1][i] > 0){
			pred[index] = i;
			index++;
		}
	}
	return pred;
}

int graph_has_path(Graph *graph, int v1, int v2){
	if (graph == NULL){
		return 0;
	}
	if (v1 < 0 || v1 >= MAX_VERTICES || v2 < 0 || v2 >= MAX_VERTICES){
		return 0;
	}
	if (graph->adj_matrix[v1][v1] == -1 || graph->adj_matrix[v2][v2] == -1){
		return 0;
	}
	//need to implement
	return 0;
}

void graph_print(Graph *graph){
	if (graph == NULL){
		return;
	}
	int i = 0;
	int j = 0;
	for (i = 0; i < graph->max_vertex; i++){
		printf("    %d", i);
	}
	printf("\n------------\n");
	for (i = 0; i < graph->max_vertex; i++){
		printf("%d |", i);
		for (j = 0; j < graph->max_vertex; j++){
			if (graph->adj_matrix[i][j] == -1){
				printf("    .");
			}
			else{
				printf("    %d", graph->adj_matrix[i][j]);
			}
		}
		printf("\n");
	}
	return;
}

void graph_output_dot(Graph *graph, char *filename){
	if (graph == NULL){
		return;
	}
	FILE *fptr;
	fptr = fopen(filename, "w");
	if (fptr == NULL){
		return;
	}
	int i = 0;
	int j = 0;
	fprintf(fprintf, "digraph {\n");
	for (i = 0; i < MAX_VERTICES; i++){
		if (graph->adj_matrix[i][i] < 0){
			continue;
		}
		fprintf(fptr, "%d;\n", i);
		for (j = 0; j < MAX_VERTICES; j++){
			if (graph->adj_matrix[i][j] > 0){
				fprintf(fptr, "%d -> %d [label = %d];\n", i, j, graph->adj_matrix[i][j]);
			}
		}
	}
	fprintf(fptr, "}");
	fclose(fptr);
	return;
}

int graph_load_file(Graph *graph, char *filename){
	if (graph == NULL){
		return -1;
	}
	FILE *fptr;
	char line[FILE_ENTRY_MAX_LEN];
	char *pt[3];
	fptr = fopen(filename, "r");
	if (fptr == NULL){
		return -1;
	}	
	fgets(line, FILE_ENTRY_MAX_LEN, fptr);
	printf("%s\n", line);		//test
	pt[0] = strtok(line, ",");
	printf("%d\n", *pt[0]);		//test
	graph_add_vertex(graph, *pt[0]);
		if (pt != NULL){
			pt[1] = strtok(NULL, ",");
			pt[2] = strtok(NULL, ",");
			if (graph_contains_vertex(graph, *pt[1]) == 0){
				graph_add_vertex(graph, *pt[1]);
			}

			graph_add_edge(graph, *pt[0], *pt[1], *pt[2]);
		}
	
	fclose(fptr);
	return 0;
}

int graph_save_file(Graph *graph, char *filename){
	if (graph == NULL){
		return -1;
	}
	FILE *fptr;
	fptr = fopen(filename, "w");
	if (fptr == NULL){
		return -1;
	}
	int i = 0;
	int j = 0;
	for (i = 0; i < MAX_VERTICES; i++){
		if (graph->adj_matrix[i][i] < 0){
			continue;
		}
		fprintf(fptr, "%d", i);
		for (j = 0; j < MAX_VERTICES; j++){
			if (graph->adj_matrix[i][j] > 0){
				fprintf(fptr, ",%d,%d\n", j, graph->adj_matrix[i][j]);
			}
		}
	}
	fclose(fptr);
	return 0;
}