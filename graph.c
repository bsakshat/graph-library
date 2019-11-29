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
	//initialize max-vertex as -1
	new->max_vertex = -1;
	//initialize the adjacency matrix 
	for (i = 0; i < MAX_VERTICES; i++){
		for (j = 0; j < MAX_VERTICES; j++){
			if (i == j){
				//vertices with value -1
				new->adj_matrix[i][j] = -1;
			}
			else{
				//edges with value 0
				new->adj_matrix[i][j] = 0;
			}			
		}
	}
	//initialize all the visited[] array elements with value 0
	for (i = 0; i < MAX_VERTICES; i++){
		new->visited[i] = 0;
	}	
	return new;
}

int graph_add_vertex(Graph *graph, int v1){
	//invalid values of graph or v1
	if (v1 < 0 || v1 >= MAX_VERTICES || graph == NULL){
		return -1;
	}
	static int max = -1;
	//if vertex already present, return 0
	if (graph->adj_matrix[v1][v1] >= 0){
		return 0;
	}
	else{
		//otherwise add the vertex
		graph->adj_matrix[v1][v1] = 0;
		if (v1 > max){
			//update the max-vertex according to the vertex added
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
	//if the vertex is present
	if (graph->adj_matrix[v1][v1] >= 0){
		return 1;
	}
	//if the vertex is not present
	else{
		return 0;
	}
}

int graph_remove_vertex(Graph *graph, int v1){
	if (v1 < 0 || v1 >= MAX_VERTICES || graph == NULL){
		return -1;
	}
	//if the vertex is already not present
	if (graph->adj_matrix[v1][v1] == -1){
		return 0;
	}
	//if the vertex is present
	else{
		int i = 0;
		//remove all the edges
		for (i = 0; i < MAX_VERTICES; i++){
			graph->adj_matrix[v1][i] = 0;
			graph->adj_matrix[i][v1] = 0;
		}
		//remove the vertex
		graph->adj_matrix[v1][v1] = -1;
		return 0;
	}
}

int graph_add_edge(Graph *graph, int v1, int v2, int wt){
	//invalid values of graph or weight
	if (graph == NULL || wt <= 0){
		return -1;
	}
	//invalid values of v1 or v2
	if (v1 < 0 || v1 >= MAX_VERTICES || v2 < 0 || v2 >= MAX_VERTICES){
		return -1;
	}
	//if anyone or both the vertices are not present
	if (graph->adj_matrix[v1][v1] == -1 || graph->adj_matrix[v2][v2] == -1){
		return -1;
	}
	//otherwise add the edge
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
	//if the edge already not present
	else if (graph->adj_matrix[v1][v2] <= 0){
		return 0;
	}
	//if the edge present
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
	//if the edge already not present
	else if (graph->adj_matrix[v1][v2] <= 0){
		return 0;
	}
	//if present, remove the edge
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
	//count the no. of vertices present
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
	//count the no. of edges present
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
	//calculate total weight by adding all the weights
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
	//if the vertex not present
	if (graph->adj_matrix[v1][v1] == -1){
		return -1;
	}
	//if the vertex is present
	else{
		int i = 0;
		int degree = 0;
		for (i = 0; i < MAX_VERTICES; i++){
			if (graph->adj_matrix[v1][i] > 0 || graph->adj_matrix[i][v1] > 0){
				degree++;
			}
		}
		//in case of self loop
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
	//if the edge not present
	else if (graph->adj_matrix[v1][v2] <= 0){
		return -1;
	}
	//if present, return the weight
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
	//if any or both of the vertices are not present
	if (graph->adj_matrix[v1][v1] == -1 || graph->adj_matrix[v2][v2] == -1){
		return 0;
	}
	//if the vertices are not connected
	else if (graph->adj_matrix[v1][v2] <= 0 && graph->adj_matrix[v2][v1] <= 0){
		return 0;
	}
	//if connected
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
	int *pred = malloc(sizeof(int) * (graph->max_vertex + 1));
	//initialize all the array elements with value -1
	for (i = 0; i <= graph->max_vertex; i++){
		pred[i] = -1;
	}
	//check and store the vertices from which there's an edge
	for (i = 0; i <= graph->max_vertex; i++){
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
	int *suc = malloc(sizeof(int) * (graph->max_vertex + 1));
	//initialize all the array elements with value -1
	for (i = 0; i <= graph->max_vertex; i++){
		suc[i] = -1;
	}
	//check and store the vertices to which there's an edge
	for (i = 0; i <= graph->max_vertex; i++){
		if (graph->adj_matrix[v1][i] > 0){
			suc[index] = i;
			index++;
		}
	}
	return suc;
}

/*
This function performs the depth-first-search to
check if there's a path between two vertices.
used inside graph_has_path function
*/

int dfs(Graph *graph, int v1, int v2){
	int i = 0;
	//mark the vertex v1 as visited
	graph->visited[v1] = 1;
	//get successors of the vertex
	int *suc = graph_get_successors(graph, v1);
	//run through all the successors
 	while (suc[i] != -1){
 		//if the successor is v2
		if (suc[i] == v2){
			return 1;
		}
		//if the successor is already visited
		else if(graph->visited[suc[i]]){
			i++;
			continue;
		}
		else{
			//perform dfs forward from the successor
			int r = dfs(graph, suc[i], v2);
			//if v2 is found
			if (r == 1){
				return 1;
			}
			i++;
		}	
	}
	//if v2 is not found
	return 0;
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
	//for same vertices with self loop
	if (v1 == v2 && graph->adj_matrix[v1][v1] > 0){
		return 1;
	}
	int i = 0;
	//initialize all of the visited[] array elements to value 0
	for (i = 0; i < MAX_VERTICES; i++){
		graph->visited[i] = 0;
	}
	//perform dfs for the vertices and check if there's a path
	if (dfs(graph, v1, v2) == 1){
		return 1;
	}
	//if no path present
	else{
		return 0;
	}
}


void graph_print(Graph *graph){
	if (graph == NULL){
		return;
	}
	int i = 0;
	int j = 0;
	printf("\n 	Adjacency Matrix for the Graph\n\n");
	printf("'.' -> no vertex \n'0' -> no edge (but vertex present for vertices)\n\n");
	printf("   ");
	//print the column header i.e. 'to' vertices
	for (i = 0; i <= graph->max_vertex; i++){
		printf("    %d", i);
	}
	printf("\n  ------------------------------------------\n");
	for (i = 0; i <= graph->max_vertex; i++){
		//print the row header i.e. 'from' vertices
		printf("%d |", i);
		for (j = 0; j <= graph->max_vertex; j++){
			//vertex not present
			if (graph->adj_matrix[i][j] == -1){
				printf("    .");
			}
			//vertex present and edges
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
	fprintf(fptr, "digraph {\n");
	for (i = 0; i < MAX_VERTICES; i++){
		//if vertex not present
		if (graph->adj_matrix[i][i] < 0){
			continue;
		}
		//else write the vertex
		fprintf(fptr, "%d;\n", i);
		for (j = 0; j < MAX_VERTICES; j++){
			//if edge is present
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
	free(graph);
	graph = graph_initialize();
	FILE *fptr;
	char line[FILE_ENTRY_MAX_LEN];
	char *pt[3] = {NULL, NULL, NULL};
	fptr = fopen(filename, "r");
	if (fptr == NULL){
		return -1;
	}
	//run until end -of-file is reached
	while (fgets(line, FILE_ENTRY_MAX_LEN, fptr) != NULL){
		//get the first token i.e. the 'from' vertex
		pt[0] = strtok(line, ",");
		int v1 = 0;
		//turn the string token into int and store in v1
		sscanf(pt[0], "%d", &v1);
		//add the vertex
		graph_add_vertex(graph, v1);
		//get the second token i.e. the 'to' vertex
		pt[1] = strtok(NULL, ",");
		//if the 'to' vertex is present
		if (pt[1] != NULL){
			int v2 = 0;
			int wt = 0;
			pt[2] = strtok(NULL, ",");
			//turn the string tokens into int and store in v2 and wt
			sscanf(pt[1], "%d", &v2);					
			sscanf(pt[2], "%d", &wt);
			//if vertex not present, add vertex
			if (graph_contains_vertex(graph, v2) == 0){
				graph_add_vertex(graph, v2);
			}
			//then add the edge
			graph_add_edge(graph, v1, v2, wt);
		}
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
		//if vertex not present
		if (graph->adj_matrix[i][i] < 0){
			continue;
		}
		//else write the vertex
		fprintf(fptr, "%d\n", i);
		for (j = 0; j < MAX_VERTICES; j++){
			//if edge is present
			if (graph->adj_matrix[i][j] > 0){
				fprintf(fptr, "%d,%d,%d\n", i, j, graph->adj_matrix[i][j]);
			}
		}
	}
	fclose(fptr);
	return 0;
}