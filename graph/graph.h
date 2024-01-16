// graph implementation
#include <vector>
#include<iostream>
#include<map>
struct Edge
{
    int destination_node;
    int weight;
    Edge(int d , int w) : destination_node(d) , weight(w) {}
};

class WeightedGraph
{
    private:
        std::map<int, std::vector<Edge>> adjacencyList;
    public:
        void insert_edge(int source , int dest, int weight)
        {
            adjacencyList[source].emplace_back(dest,weight);
            adjacencyList[dest].emplace_back(source,weight);
        }
        std::map<int , std::vector<Edge>> get_representation()
        {
            return adjacencyList;
        }

};