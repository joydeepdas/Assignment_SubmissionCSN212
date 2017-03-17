/*
	Bellman-ford algorithm implementation which gives shotest distance to all vertices from the given source 
	vertex or report the presence of negative cycle if present.
	---->by Joydeep Das ,14116032, ECE 3rd year
	
*/

#include <bits/stdc++.h>
using namespace std;
struct Edge
{
    int source, dst, weight;
};

struct Graph
{
    // V,E-> Number of vertices,Number of edges
    int V, E;
    // array of edges.
    struct Edge* edge;
};
 
// Constructs graph with V vertices and E edges 
// initialization of graph;
struct Graph* createGraph(int V, int E)
{
    struct Graph* graph = (struct Graph*) malloc( sizeof(struct Graph) );
    graph->V = V;
    graph->E = E;
 
    graph->edge = (struct Edge*) malloc( graph->E * sizeof( struct Edge ) );
 
    return graph;
}
//print function
void printArr(int dist[], int n)
{
    cout<< "Vertex number   Distance from Source"<<endl;
    for (int i = 0; i < n; ++i)
        cout<<"  "<<i<<"\t\t"<<dist[i]<<endl;
}
 
// Bellman-Ford algorithm implementation as par described on class.
void BellmanFord_shorstestpath (struct Graph* graph, int source)
{
    int V = graph->V;
    int E = graph->E;
    int dist[V];
 
    // Initial step: distance from source to itself as 0 , remaining as infinity
    for (int i = 0; i < V; i++)
        dist[i]   = INT_MAX;
    dist[source] = 0;
 
    // Relaxtion step: Shortest path from source to any other vertex can have at-most |V| - 1 edges
    for (int i = 1; i <= V-1; i++)
    {
        for (int j = 0; j < E; j++)
        {
            int u = graph->edge[j].source;
            int v = graph->edge[j].dst;
            int weight = graph->edge[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
                dist[v] = dist[u] + weight;
        }
    }
    // Step 3: checking for negative-weight cycles if exists.
    bool negative_cycle=false;
    for (int i = 0; i < E; i++)
    {
        int u = graph->edge[i].source;
        int v = graph->edge[i].dst;
        int weight = graph->edge[i].weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]){
            cout<<"Graph contains negative weight cycle"<<endl;
            negative_cycle=true;
            break;
        }
    }
    
 	if(negative_cycle==false){
    	printArr(dist, V);
    }
 
    return;
}
 
int main()
{
    
    
    int V = 5;  // Number of vertices 
    int E = 8;  // Number of edges 
    struct Graph* graph = createGraph(V, E);
 
    // add edge 0-1 
    graph->edge[0].source = 0;
    graph->edge[0].dst = 1;
    graph->edge[0].weight = -4;
    
    // add edge 0-2 
    graph->edge[1].source = 0;
    graph->edge[1].dst = 2;
    graph->edge[1].weight = 14;
    
    // add edge 1-2 
    graph->edge[2].source = 1;
    graph->edge[2].dst = 2;
    graph->edge[2].weight = 8;
 
    // add edge 1-3 
    graph->edge[3].source = 1;
    graph->edge[3].dst = 3;
    graph->edge[3].weight = -3;
 
    // add edge 1-4 
    graph->edge[4].source = 1;
    graph->edge[4].dst = 4;
    graph->edge[4].weight = 12;
 
    // add edge 3-2 
    graph->edge[5].source = 3;
    graph->edge[5].dst = 2;
    graph->edge[5].weight = -1;
    
    // add edge 3-1 
    graph->edge[6].source = 3;
    graph->edge[6].dst = 1;
    graph->edge[6].weight = 5;
 
    
    // add edge 4-3 
    graph->edge[7].source = 4;
    graph->edge[7].dst = 3;
    graph->edge[7].weight = -2;
 
 	clock_t t1,t2;
    t1=clock();
 	
    BellmanFord_shorstestpath (graph, 0);
 
 	t2=clock();
    float diff=((float)t2-(float)t1);
	float seconds = diff / CLOCKS_PER_SEC;	
	cout<<"clocks_per_sec--> "<<CLOCKS_PER_SEC<<endl;
	cout<<"clock_ticks--> "<<diff<<endl;
    cout<<"RUNNNING TIME --> "<<seconds<<endl;
    return 0;
}
