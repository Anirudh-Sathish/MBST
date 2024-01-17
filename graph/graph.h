// graph implementation
#include <vector>
#include<iostream>
#include<map>
#include <queue>
#include <set>
#include <climits>

#ifndef WEIGHTEDGRAPH_H
#define WEIGHTEDGRAPH_H
using namespace std;
struct Edge
{
    int source_node;
    int destination_node;
    int weight;
    Edge(int s,int d , int w) : source_node(s), destination_node(d) , weight(w) {}

    friend ostream& operator<<(ostream& os, const Edge& edge) {
        os << "Source Node: " << edge.source_node << ", Destination Node: " << edge.destination_node << ", Weight: " << edge.weight;
        return os;
    }
};

class WeightedGraph
{
    private:
        map<int, vector<Edge>> adjacencyList;

    public:
        void insert_edge(int source , int dest, int weight)
        {
            adjacencyList[source].emplace_back(source,dest,weight);
            adjacencyList[dest].emplace_back(dest,source,weight);
        }
        map<int , vector<Edge>> get_representation()
        {
            return adjacencyList;
        }
        void display_graph()
        {
            for (const auto &item : adjacencyList)
            {
                cout << "Vertex " << item.first << " : ";
                for (const auto &edge : item.second)
                {
                    cout << "(" << edge.destination_node << ", " << edge.weight << ") ";
                }
                cout << endl;
            }
        }
        map<int,int> primMST() {
            priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
            map<int,bool> visited;
            map<int,int> parent, keyScore;
            for (const auto &item : adjacencyList)
            {
                visited[item.first] = false;
                keyScore[item.first] = INT_MAX;
            }
            int startVertex = this->adjacencyList.begin()->first;
            pq.push({0,startVertex});
            keyScore[startVertex] = 0;
            while(!pq.empty())
            {
                int vertex = pq.top().second;
                pq.pop();
                if(visited[vertex] == true)continue;
                visited[vertex] = true;
                for(auto edge: this->adjacencyList[vertex])
                {
                    int destination_vertex = edge.destination_node;
                    int path_weight = edge.weight;
                    if(!visited[destination_vertex] && path_weight < keyScore[destination_vertex])
                    {
                        keyScore[destination_vertex] = path_weight;
                        parent[destination_vertex] = vertex;
                        pq.push({keyScore[destination_vertex],destination_vertex});
                    }
                }
            }
            return parent;
        }
        void displayPrim()
        {
            map<int,int> edges = this->primMST();
            cout << "MST Edges" << endl;
            for(auto it= edges.begin(); it != edges.end(); it++)
            {
                cout<<"Edge : "<<it->first<<" - "<<it->second<<endl;
            }
        }

};
#endif // WEIGHTEDGRAPH_H