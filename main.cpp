#include<iostream>
#include "graph/graph.h"
#include<map>
int main()
{
    WeightedGraph graph;

    graph.insert_edge(1, 2, 3);
    graph.insert_edge(1, 3, 5);
    graph.insert_edge(2, 3, 2);
    graph.insert_edge(2, 4, 7);

    std::map<int , std::vector<Edge>> adj_list = graph.get_representation();
}