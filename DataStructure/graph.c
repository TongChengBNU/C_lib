/************************************************************************
 > File Name: undirected_graph.c
 > Author: Tong Cheng
 > Mail: tong.cheng.8819@outlook.com 
 > Created Time: Sun 01 Dec 2019 11:57:02 AM CST
************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define HEAD_ID -1
#define EDGE_ERROR 0
#define MAX_DIST 0x7fffffff


/* Graph 1: 
 * simple case
 *  A--B--E
 *  |\ |  |
 *  | \|  |
 *  D  C  G
 *  | /
 *  |/
 *  F--H--I
 *
 *
 * Graph 2:
 * not connected
 * A---------          J         N--K--L
 * |  |  |  |         / \           |  |
 * B  C  D  E        /   \          M--N
 * |       /|       H-----I
 * | ------ |
 * |/       |
 * F--------G
 *
 * 
 * Graph 3:
 * weighted undirected graph
 *
 *    A---28---B
 *   /        / \
 * 10        14  16
 * /        /     \
 * F       G      C
 * \     /  \     /
 * 25  24   18   12
 *   \ /      \  /
 *    E---22----D
 *
 *
 * Graph 4:
 * weighted directed graph
 *   A ---100---> E
 *   |\        /\/|\
 *   | 30     60  |
 *   |  \/   /    |
 *   |   D---     |
 *   |       \    |
 *   10       20 10
 *  \|/        \/ |
 *   B ---50--->  C
 *         
 * What could be improved:
 * a function which creates edge with **variant parameters**, then insert_edge only utilize this function;
 *
 *
 * */




//typedef unsigned int ele_t;
typedef char ele_t;
typedef unsigned int id_t;
typedef int weight_t;
typedef unsigned int dist_t;

typedef enum{
	FALSE,
	TRUE
}Boolean;

typedef struct{
	dist_t dist;	
	Boolean tag;  // in S or not
}Dist_t;

typedef enum graph_type{
	Undirected,
	Directed
}GraphType;

typedef enum traversal_state{
	NotVisited,
	Visited
}TraversalState;

typedef struct edge{
	unsigned int id;	
	int weight;
	struct edge *nextEdge;
}Edge;

typedef struct vertex{
	unsigned int id;
	ele_t data;
	struct vertex *nextVertex;
	struct edge *neighbor;
}Vertex;

typedef struct graph{
	unsigned int vertex_num;
	unsigned int edge_num;
	GraphType type;
	Vertex *head;
}Graph;

void initialization(Graph *g, GraphType type);
void graph1(Graph *g);
void graph2(Graph *g);
void graph3(Graph *g);
void graph4(Graph *g);

void insert_vertex(ele_t data, Graph *g);
int insert_edge_directed(id_t id1_in, id_t id2, Graph *g);
int insert_edge_directed_weighted(id_t id1_in, id_t id2, weight_t weight, Graph *g);
void insert_edge_undirected(id_t id1, id_t id2, Graph *g);
void insert_edge_undirected_weighted(id_t id1, id_t id2, weight_t weight, Graph *g);


void show_state(Graph *g);
Vertex *search_vertex(id_t id, Graph *g);
void interactive_mode(Graph *g);

void depth_first_search(Vertex *begin_vertex, Graph *g);
void subDFS(Vertex *cur_vertex, Graph *g, TraversalState *tsTable);
void breadth_first_search(Vertex *begin_vertex, Graph *g);
void show_components(Graph *g);

void minimum_cost_spanning_tree(Graph *g);
void shortest_path(Vertex *source_vertex, Graph *g);

int main(int argc, char *argv[])
{
	Graph *g = (Graph *)malloc(sizeof(Graph));
	graph4(g);
	//initialization(g);
	// insert_vertex('A', g);
	// insert_vertex('B', g);
	// // Vertex *ptr = search_vertex(0,g);
	// // printf("%d", ptr->id);
	// insert_edge_directed(0,1,g);
	// show_state(g);
	interactive_mode(g);

	return 0;
}

void initialization(Graph *g, GraphType type)
{
	g->vertex_num = 0;
	g->edge_num = 0;
	g->type = type;
	g->head = (Vertex *)malloc(sizeof(Vertex));
	g->head->id = HEAD_ID;
	g->head->nextVertex = NULL;
	g->head->neighbor = NULL;
	return;
}
void graph1(Graph *g)
{
	initialization(g, Undirected);	
	insert_vertex('A', g);
	insert_vertex('B', g);
	insert_vertex('C', g);
	insert_vertex('D', g);
	insert_vertex('E', g);
	insert_vertex('F', g);
	insert_vertex('G', g);
	insert_vertex('H', g);
	insert_vertex('I', g);
	
	insert_edge_undirected(0, 1, g);
	insert_edge_undirected(0, 2, g);
	insert_edge_undirected(0, 3, g);
	insert_edge_undirected(1, 2, g);
	insert_edge_undirected(1, 4, g);
	insert_edge_undirected(2, 5, g);
	insert_edge_undirected(3, 5, g);
	insert_edge_undirected(4, 6, g);
	insert_edge_undirected(5, 7, g);
	insert_edge_undirected(7, 8, g);
}
void graph2(Graph *g)
{
	initialization(g, Undirected);	
	insert_vertex('A', g);
	insert_vertex('B', g);
	insert_vertex('C', g);
	insert_vertex('D', g);
	insert_vertex('E', g);
	insert_vertex('F', g);
	insert_vertex('G', g);
	insert_edge_undirected(0, 1, g);
	insert_edge_undirected(0, 2, g);
	insert_edge_undirected(0, 3, g);
	insert_edge_undirected(0, 4, g);
	insert_edge_undirected(5, 1, g);
	insert_edge_undirected(5, 4, g);
	insert_edge_undirected(5, 6, g);
	insert_edge_undirected(6, 4, g);

	// 7-9
	insert_vertex('H', g);
	insert_vertex('I', g);
	insert_vertex('J', g);
	insert_edge_undirected(7, 8, g);
	insert_edge_undirected(7, 9, g);
	insert_edge_undirected(8, 9, g);

	// 10-14
	insert_vertex('K', g);
	insert_vertex('L', g);
	insert_vertex('M', g);
	insert_vertex('N', g);
	insert_vertex('O', g);
	insert_edge_undirected(10, 11, g);
	insert_edge_undirected(10, 12, g);
	insert_edge_undirected(10, 13, g);
	insert_edge_undirected(11, 14, g);
	insert_edge_undirected(12, 14, g);
}
void graph3(Graph *g)
{
	initialization(g, Undirected);	
	insert_vertex('A', g);
	insert_vertex('B', g);
	insert_vertex('C', g);
	insert_vertex('D', g);
	insert_vertex('E', g);
	insert_vertex('F', g);
	insert_vertex('G', g);
	
	insert_edge_undirected_weighted(0, 1, 28, g);
	insert_edge_undirected_weighted(0, 5, 10, g);
	insert_edge_undirected_weighted(1, 2, 16, g);
	insert_edge_undirected_weighted(1, 6, 14, g);
	insert_edge_undirected_weighted(2, 3, 12, g);
	insert_edge_undirected_weighted(3, 6, 18, g);
	insert_edge_undirected_weighted(3, 4, 22, g);
	insert_edge_undirected_weighted(4, 5, 25, g);
	insert_edge_undirected_weighted(4, 6, 24, g);
}
void graph4(Graph *g)
{
	initialization(g, Directed);	
	insert_vertex('A', g);
	insert_vertex('B', g);
	insert_vertex('C', g);
	insert_vertex('D', g);
	insert_vertex('E', g);
	
	// 0-4
	insert_edge_directed_weighted(0, 4, 100, g);
	insert_edge_directed_weighted(0, 3, 30, g);
	insert_edge_directed_weighted(0, 1, 10, g);
	insert_edge_directed_weighted(1, 2, 50, g);
	insert_edge_directed_weighted(2, 4, 10, g);
	insert_edge_directed_weighted(3, 4, 60, g);
	insert_edge_directed_weighted(3, 2, 20, g);
}

void insert_vertex(ele_t data, Graph *g)
{
	Vertex *ptr = g->head;
	while(ptr->nextVertex) ptr=ptr->nextVertex;
	Vertex *newVertex = (Vertex *)malloc(sizeof(Vertex));
	newVertex->id = g->vertex_num++;
	newVertex->data = data;
	newVertex->nextVertex = NULL;
	newVertex->neighbor = NULL;

	ptr->nextVertex = newVertex;
	printf("Vertex insertion success;\n");
	return;	
}

Vertex *search_vertex(id_t id, Graph *g)
{
	// linearly search
	if(!g->head->nextVertex)
		return NULL;

	Vertex *ptr = g->head->nextVertex;
	while(ptr)
	{
		if(ptr->id == id)
			return ptr;
		ptr = ptr->nextVertex;
	}
	return NULL;
}

int insert_edge_directed(id_t id1_in, id_t id2, Graph *g)
{
	Vertex *vertex_ptr = search_vertex(id1_in, g);	
	if((!vertex_ptr) || (!(search_vertex(id2, g))))
	{
		printf("Invalid edge;\n");
		return EDGE_ERROR;
	}
		
	Edge *new_edge = (Edge *)malloc(sizeof(Edge));
	new_edge->id = id2;
	new_edge->nextEdge = NULL;

	Edge *edge_ptr = vertex_ptr->neighbor;
	if(edge_ptr)
	{
		while(edge_ptr->nextEdge) edge_ptr = edge_ptr->nextEdge;
		edge_ptr->nextEdge = new_edge;
	}
	else
	{
		vertex_ptr->neighbor = new_edge;
	}

	g->edge_num++;
	//printf("Edge insertion success;\n");
	return 1;
}

void insert_edge_undirected(id_t id1, id_t id2, Graph *g)
{
	int check = insert_edge_directed(id1, id2, g);
	//printf("%d\n", check);
	if(!check)
	{
		return;
	}
	insert_edge_directed(id2, id1, g);

	g->edge_num--;
	printf("Edge insertion success;\n");
	return;
}
int insert_edge_directed_weighted(id_t id1_in, id_t id2, weight_t weight, Graph *g)
{
	Vertex *vertex_ptr = search_vertex(id1_in, g);	
	if((!vertex_ptr) || (!(search_vertex(id2, g))))
	{
		printf("Invalid edge;\n");
		return EDGE_ERROR;
	}
		
	Edge *new_edge = (Edge *)malloc(sizeof(Edge));
	new_edge->id = id2;
	new_edge->weight = weight;
	new_edge->nextEdge = NULL;

	Edge *edge_ptr = vertex_ptr->neighbor;
	if(edge_ptr)
	{
		while(edge_ptr->nextEdge) edge_ptr = edge_ptr->nextEdge;
		edge_ptr->nextEdge = new_edge;
	}
	else
	{
		vertex_ptr->neighbor = new_edge;
	}

	g->edge_num++;
	//printf("Edge insertion success;\n");
	return 1;
}
void insert_edge_undirected_weighted(id_t id1, id_t id2, weight_t weight, Graph *g)
{
	int check = insert_edge_directed_weighted(id1, id2, weight, g);
	//printf("%d\n", check);
	if(!check)
	{
		return;
	}
	insert_edge_directed_weighted(id2, id1, weight, g);

	g->edge_num--;
	printf("Edge insertion success;\n");
	return;
}

void show_state(Graph *g)
{
	printf("--------------------Info of Graph---------------------\n");
	switch(g->type){
		case Undirected:
			printf("Type of graph: %d Undirected\n", g->type);
			break;
		case Directed:
			printf("Type of graph: %d Directed\n", g->type);
			break;
	}
	printf("Num of Vertex: %d      Num of Edge: %d    \n", g->vertex_num, g->edge_num);
	Vertex *v_ptr = g->head->nextVertex;
	Edge *e_ptr;
	while(v_ptr)
	{
		printf("Node %c (id-%d): ", v_ptr->data, v_ptr->id);
		e_ptr = v_ptr->neighbor;
		while(e_ptr)
		{
			printf("%d(w.t.-%d) ", e_ptr->id, e_ptr->weight);
			e_ptr = e_ptr->nextEdge;
		}
		v_ptr = v_ptr->nextVertex;
		putchar('\n');
	}
	printf("--------------------End of Graph---------------------\n\n");
	return;
}
void interactive_mode(Graph *g)
{
	unsigned int option;
	unsigned int id1, id2;
	ele_t data;
	id_t id;
	while(1)
	{
		printf("1. Insert vertex; 2. Insert edge; 3. Show; 4. DFS; 5. BFS; 6. Components; 7. Shortest Path Table; 8. Exit;\n");
		scanf("%d", &option);
		switch(option){
			case 1: 
				printf("Please input the name of new vertex: \n");
				scanf(" %c", &data);
				//fflush(stdin);
				//data = getchar();
				insert_vertex(data, g);
				break;
			case 2: 
				printf("Please input the ids of new edge: \n");
				scanf("%d %d", &id1, &id2);
				insert_edge_undirected(id1, id2, g);
				break;
			case 3: 
				show_state(g);
				break;
			case 4:
				printf("Please input the id of begin vertex:\n");
				scanf(" %d", &id);
				depth_first_search(search_vertex(id, g), g);
				break;
			case 5:
				printf("Please input the id of begin vertex:\n");
				scanf(" %d", &id);
				breadth_first_search(search_vertex(id, g), g);
				break;
			case 6:
				show_components(g);
				break;
			case 7:
				printf("Please input the id of source vertex:\n");
				scanf(" %d", &id);
				shortest_path(search_vertex(id, g), g);
				break;
			case 8: 
				exit(0);
				break;
		}
		putchar('\n');
	}
}
void depth_first_search(Vertex *begin_vertex, Graph *g)
{
	// all vertice and only one access
	if(!g->vertex_num)
	{
		printf("Empty graph.\n");	
		return;
	}
	
	TraversalState tsTable[g->vertex_num];
	for(int i=0;i<g->vertex_num;i++)
		tsTable[i] = NotVisited;
	printf("DFS result:\n");
	subDFS(begin_vertex, g, tsTable);
	putchar('\n');
	return;
}
void subDFS(Vertex *cur_vertex, Graph *g, TraversalState *tsTable)
{
	if(!tsTable[cur_vertex->id])
	{
		printf("%c ", cur_vertex->data);
		tsTable[cur_vertex->id] = Visited;
	}

	Vertex *vertex_ptr;
	Edge *edge_ptr = cur_vertex->neighbor;
	while(edge_ptr)
	{
		if(tsTable[edge_ptr->id])
		{
			edge_ptr = edge_ptr->nextEdge;
			continue;
		}

		vertex_ptr = search_vertex(edge_ptr->id, g);	
		subDFS(vertex_ptr, g, tsTable);
		edge_ptr = edge_ptr->nextEdge;
	}
	
	return;
}
void breadth_first_search(Vertex *begin_vertex, Graph *g)
{
	if(!g->vertex_num)
	{
		printf("Empty graph.\n");	
		return;
	}
	
	TraversalState tsTable[g->vertex_num];	
	for(int i=0;i<g->vertex_num;i++)
		tsTable[i] = NotVisited;
	
	// queue
	Vertex *queue[g->vertex_num];
	unsigned int head, tail;
	head = 0, tail = head;
	Vertex *cur_vertex;
	Vertex *vertex_ptr;
	Edge *edge_ptr;

	printf("%c ", begin_vertex->data);
	tsTable[begin_vertex->id] = Visited;
	queue[tail++] = begin_vertex;
	while((tail-head))
	{
		cur_vertex = queue[head++];
		edge_ptr = cur_vertex->neighbor;
		while(edge_ptr)
		{
			if(!tsTable[edge_ptr->id])
			{
				vertex_ptr = search_vertex(edge_ptr->id, g);
				printf("%c ", vertex_ptr->data);
				tsTable[edge_ptr->id] = Visited;
				queue[tail++] = vertex_ptr;
			}
			edge_ptr = edge_ptr->nextEdge;
		}
	}
}
void show_components(Graph *g)
{
	TraversalState tsTable[g->vertex_num];		
	for(int i=0;i<g->vertex_num;i++)
		tsTable[i] = NotVisited;
	unsigned int first_not_visited_index, search_begin_position=0;
	unsigned int component_count = 0;

	putchar('\n');
	do{
		first_not_visited_index=-1;
		for(int i=search_begin_position;i<g->vertex_num;i++)
		{
			if(!tsTable[i])
			{
				first_not_visited_index = i;
				break;
			}
 		}	

		search_begin_position = first_not_visited_index +1;
		if(first_not_visited_index == -1)
			break;

		Vertex *cur_vertex = search_vertex(first_not_visited_index, g);
		printf("(DFS) Component %d: ", ++component_count);
		subDFS(cur_vertex, g, tsTable);
		putchar('\n');
	}while(1);
	
	printf("Num. of components: %d\n", component_count);
}

// to be continued ...
// maybe a lot of ways to implement this function
// like minimum heap and union find set
void minimum_cost_spanning_tree(Graph *g)
{
	// Kruskal	
	// establish T = (V(g), NULL) graph and U = E(g) set;
	// while(  E(T)<|V(g)| && U is non-empty  )
	// {
	//		candidate_edge = min_cost(U);
	//		U = U / {candidate_edge};
	//		v1, v2 in candidate_edge
	//		if(v1 and v2 are not in the same component)
	//			E(T) += candidate_edge
	// }
	//
	// if( |E(T)| < |V(g)|-1 )
	//		Failed;
	//		
}
void shortest_path(Vertex *source_vertex, Graph *g)
{
	if(!g->vertex_num)
	{
		printf("Empty graph.\n");
		return;
	}

	Vertex *S[g->vertex_num+1];
	unsigned int length_S = 0;
	Dist_t distTable[g->vertex_num];

	// init dist[]
	for(int i=0;i<g->vertex_num;i++)
	{
		distTable[i].dist = MAX_DIST;
		distTable[i].tag = FALSE;	
	}

	S[(length_S)++] = source_vertex;
	distTable[source_vertex->id].dist = 0;
	distTable[source_vertex->id].tag = TRUE;
	Edge *edge_ptr = source_vertex->neighbor;	
	while(edge_ptr)
	{
		distTable[edge_ptr->id].dist = edge_ptr->weight;
		edge_ptr = edge_ptr->nextEdge;
	}

	unsigned int min_index;
	// update_dist = distTable[min_index].dist + dist(min_index->i)
	dist_t min_dist, update_dist;
	while(length_S < g->vertex_num)
	{
		min_index=0;	
		min_dist=MAX_DIST;
		// Step 2:
		for(int i=0;i<g->vertex_num;i++)
		{
			if(!distTable[i].tag && distTable[i].dist<min_dist)
			{
				min_index=i;
				min_dist=distTable[i].dist;
			}
		}
		S[length_S++] = search_vertex(min_index, g);
		distTable[min_index].tag = TRUE;
		// Step 3:
		for(int i=0;i<g->vertex_num;i++)
		{
			if(!distTable[i].tag)
			{
				edge_ptr = S[length_S-1]->neighbor;
				while(edge_ptr)
				{
					if(edge_ptr->id == i)
					{
						update_dist = distTable[min_index].dist + edge_ptr->weight;
						break;
					}
					edge_ptr = edge_ptr->nextEdge;
				}
				// if edge_ptr is NULL, it means no dist(min_index->i)
				if(!edge_ptr)
				{
					update_dist = MAX_DIST;
				}


				distTable[i].dist = (distTable[i].dist<update_dist)? distTable[i].dist:update_dist;
			}
		}
	}

	printf("Shortest path table: \n");	
	for(int i=0;i<length_S;i++)
		printf("%d ", distTable[i].dist);
	putchar('\n');

	return;
}
