#include<iostream>
#include<vector>
#include<algorithm>
#include "graph.h"

using namespace std;

#ifndef INTERVALGRAPH_H
#define INTERVALGRAPH_H

struct IntervalEdge
{
    int task;
    int interval_start;
    int interval_end;

    explicit IntervalEdge(int num, int s, int e) : task(num), interval_start(s), interval_end(e) {}
};

class IntervalGraph
{
private:
    vector<IntervalEdge> intervals;

public:
    void insert_interval(int task, int start, int end)
    {
        intervals.push_back(IntervalEdge(task, start, end));
    }

    void display_interval() const
    {
        for (const auto& item : intervals)
        {
            cout << item.interval_start << " - " << item.interval_end << endl;
        }
    }

    WeightedGraph get_graph()
    {
        WeightedGraph graph;
        set<pair<int,int>> visitedEdges;

        for (auto it1 = intervals.begin(); it1 != intervals.end(); ++it1)
        {
            for (auto it2 = intervals.begin(); it2 != intervals.end(); ++it2)
            {
                if (it1 == it2 || it1->task == it2->task)
                    continue;

                if (!(it2->interval_start > it1->interval_end || it2->interval_end < it1->interval_start))
                {
                    pair<int,int> edge_pair = {it1->task,it2->task};
                    if(visitedEdges.find(edge_pair) == visitedEdges.end())
                    {
                        int interval_start = max(it1->interval_start, it2->interval_start);
                        int interval_end = min(it1->interval_end, it2->interval_end);
                        int weight = interval_end - interval_start;

                        graph.insert_edge(it1->task, it2->task, weight);
                        visitedEdges.insert(edge_pair);
                    }
                    
                }
            }
        }

        return graph;
    }
};
#endif