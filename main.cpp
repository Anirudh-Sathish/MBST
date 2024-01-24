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
    graph.insert_edge(4, 6, 8);
    graph.insert_edge(2, 6, 1);
    cout<<"Graph Adjacency List"<<endl;
    graph.display_graph();
    graph.bruteMBST_display();
    // graph.displayKruskalMBST();
    graph.jaggery_display();
    float approx_ratio = graph.get_approximation_ratio("jaggery");
    cout<<"Approximate Ratio: "<<approx_ratio<<endl;
    // graph.displayPrim();
    // graph.displayKruskal();
}