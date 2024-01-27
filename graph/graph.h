// graph implementation
#include <vector>
#include<iostream>
#include<map>
#include <queue>
#include <set>
#include <climits>
#include <utility>
#include "dsu.h"
#include "../utils/helper.cpp"

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

        static bool compareBySize(const pair<int, vector<Edge>>& a, const pair<int, vector<Edge>>& b) {
            return a.second.size() < b.second.size();
        }
        static bool compareEdgeWeight(const Edge &a, const Edge &b)
        {
            return a.weight < b.weight;
        }
        vector<pair<int, vector<Edge>>> sort_adjacencyList()
        {
            vector<pair<int, vector<Edge>>> adj_list(this->adjacencyList.begin(), this->adjacencyList.end());
            sort(adj_list.begin(), adj_list.end(), compareBySize);
            return adj_list;
        }
        vector<Edge> get_edges()
        {
            vector<Edge> edges;
            set<pair<int,int>> visitedEdges;
            for (const auto &item: adjacencyList)
            {
                int source_node = item.first;
                for(const auto &edge: item.second)
                {
                    int destination_node = edge.destination_node;
                    pair<int,int> current_edge = make_pair(min(source_node,destination_node),max(source_node,destination_node));
                    if(visitedEdges.find(current_edge) == visitedEdges.end())
                    {
                        edges.push_back(Edge(source_node,destination_node,edge.weight));
                        visitedEdges.insert(current_edge);
                    }
                }
            }
            return edges;
        }
        vector<int> get_vertices()
        {
            vector<int> vertices;
            for(const auto &item : adjacencyList)
            {
                vertices.push_back(item.first);
            }
            return vertices;
        }
        map<int,int> init_degree()
        {
            map<int,int> degree;
            for(const auto it: this->adjacencyList)
            {
                degree[it.first] = 0;
            }
            return degree;
        }
        int get_weight( vector<Edge> mst)
        {
            int wght = 0;
            for(const auto edge: mst)wght+=edge.weight;
            return wght;
        }
        vector<vector<Edge>> get_combinations_from_string(int edge_count, vector<Edge> edge_list)
        {
            vector<string> listing = generateStrings(edge_count);
            vector<vector<Edge>> all_combinations;
            for(auto item:listing)
            {
                vector<Edge> current_combination;
                for(int i= 0 ; i < item.size(); i++)
                {
                    if (item[i] == '1')
                    {
                        current_combination.push_back(edge_list[i]);
                    }
                }
                all_combinations.push_back(current_combination);
            }
            return all_combinations;
        }
        bool is_acylic(vector<Edge> tree_edges)
        {
            vector<int> vertices = get_vertices();
            DSU_map dsu_obj(vertices);
            for(const auto edge:tree_edges)
            {
                if(dsu_obj.find(edge.source_node) == dsu_obj.find(edge.destination_node))
                {
                    return false;
                }
                dsu_obj.union_dsu(edge.source_node,edge.destination_node);
            }   
            return true;
        }
        bool is_connected(vector<Edge> tree_edges)
        {
            vector<int> vertices = get_vertices();
            DSU_map dsu_obj(vertices);
            for(const auto edge: tree_edges)
            {
                dsu_obj.union_dsu(edge.source_node,edge.destination_node);
            }
            int start_vertex = this->adjacencyList.begin()->first;
            int root_set = dsu_obj.find(start_vertex);

            for(auto item: adjacencyList)
            {
                if(dsu_obj.find(item.first)!= root_set)return false;
            }
            return true;
        }
        bool is_mst(vector<Edge> tree_edges)
        {
            if(is_connected(tree_edges) && is_acylic(tree_edges))return true;
            return false;

        }
        bool is_binary_st(vector<Edge> edges)
        {
            map<int,int> degree_list = init_degree();
            for(const auto edge:edges)
            {
                degree_list[edge.source_node]+=1;
            }
            for(const auto degree:degree_list)
            {
                if(degree.second>3)return false;
            }
            return true;
        }
        vector<vector<Edge>> mst_permutations(vector<Edge> edges)
        {
            int edge_count = edges.size();
            int tree_edge_count = this->adjacencyList.size()-1; // vertices-1
            vector<vector<Edge>> combinations =this->get_combinations_from_string(edge_count,edges);
            vector<vector<Edge>> accepted_combinations;
            for(auto combination: combinations)
            {
                if(combination.size()!=tree_edge_count)continue;
                // check if this is mst and binary
                if(is_mst(combination) && is_binary_st(combination))accepted_combinations.push_back(combination);
        
            }
            return accepted_combinations;
        }
    public:
        void insert_edge(int source , int dest, int weight)
        {
            adjacencyList[source].emplace_back(source,dest,weight);
            // adjacencyList[dest].emplace_back(dest,source,weight);
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
            }// reuires connectedness and acyclicity
        }
        vector<Edge> kruskal_mst()
        {
            vector<Edge> edges = this->get_edges();
            vector<int> vertices = this->get_vertices();
            auto compareByWeight = [](const Edge &a, const Edge &b) {
                return a.weight < b.weight;
                };
            sort(edges.begin(), edges.end(), compareByWeight);

            DSU_map dsu_obj(vertices);
            vector<Edge> mstEdges;
            for(auto edge: edges)
            {
                if (dsu_obj.find(edge.source_node) != dsu_obj.find(edge.destination_node))
                {
                    dsu_obj.union_dsu(edge.source_node,edge.destination_node);
                    mstEdges.push_back(edge);
                }
            }
            return mstEdges;
        }
        void displayKruskal()
        {
            vector<Edge> mst = this->kruskal_mst();
            for(const auto edge: mst)
            {
                cout<<"Edge: "<<edge.source_node<<"-"<<edge.destination_node<<" Weight: "<<edge.weight<<endl;
            }
        }
        vector<Edge> jaggeryMBST()
        {
            vector<pair<int, vector<Edge>>> sortedAdj = this->sort_adjacencyList();
            map<int,int> degree = this->init_degree();
            vector<int> vertices = get_vertices();
            DSU_map dsu_obj(vertices);
            vector<Edge> mstEdges;
            for(auto it: sortedAdj)
            {
                sort(it.second.begin(),it.second.end(),compareEdgeWeight);
                for(const auto edge: it.second)
                {
                    if(degree[edge.destination_node]<3 && degree[edge.source_node]<3)
                    {
                        if(dsu_obj.find(edge.destination_node) != dsu_obj.find(edge.source_node))
                        {
                            dsu_obj.union_dsu(edge.source_node,edge.destination_node);
                            mstEdges.push_back(edge);
                            degree[edge.destination_node]+=1;
                            degree[edge.source_node]+=1;
                        }
                    }
                }
            }
            return mstEdges;
        }
        void jaggery_display()
        {
            vector<Edge> mst = this->jaggeryMBST();
            for(const auto edge: mst)
            {
                cout<<"Edge: "<<edge.source_node<<"-"<<edge.destination_node<<" Weight: "<<edge.weight<<endl;
            }
            cout<<"Obtained weight: "<<this->get_weight(mst)<<endl;
        }
        
        vector<Edge> bruteMBST()
        {
            vector<Edge> edges = this->get_edges();
            vector<vector<Edge>> binary_st_list = mst_permutations(edges);
            vector<Edge> mbst;
            int min_weight = INT_MAX;
            for (const auto st: binary_st_list)
            {
                if(get_weight(st)< min_weight)
                {
                    mbst = st;
                    min_weight = get_weight(st);
                }
            }
            return mbst;
        }
        void bruteMBST_display()
        {
            vector<Edge> mbst = bruteMBST();
            cout<<"Brute MBST"<<endl;
            for(const auto edge: mbst)
            {
                cout<<"Edge: "<<edge.source_node<<"-"<<edge.destination_node<<" Weight: "<<edge.weight<<endl;
            }
            cout<<"Obtained optimal weight: "<<this->get_weight(mbst)<<endl;
        }
        float get_approximation_ratio(string algo)
        {
            vector<Edge> optimal_mbst =bruteMBST(),predicted_mbst;
            float optimal_weight = get_weight(optimal_mbst) , predicted_weight;
            if(algo == "jaggery")
            {
                predicted_mbst = jaggeryMBST();
                predicted_weight = get_weight(predicted_mbst);
                return predicted_weight/optimal_weight;
            }
            return 0;
        }
        
};
#endif // WEIGHTEDGRAPH_H