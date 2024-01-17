#include<iostream>
#include<map>
#include "graph/graph.h"
int main()
{
    WeightedGraph graph;

    graph.insert_edge(1, 2, 3);
    graph.insert_edge(1, 3, 5);
    graph.insert_edge(2, 3, 2);
    graph.insert_edge(2, 4, 7);
    cout<<"Graph Adjacency List"<<endl;
    graph.display_graph();
    graph.displayPrim();
}