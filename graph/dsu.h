#include<iostream>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;
#ifndef DSU_H
#define DSU_H
class DSU_map
{
    private:
        map<int,int> representative;
        map<int,int> height;
    public:
        DSU_map(vector<int> vertices)
        {
            for(const auto v :vertices)
            {
                representative[v] = v;
                height[v] = v;
            }
        }
        int find(int idx)
        {
            if(representative[idx] == idx)return idx;
            representative[idx] = find(representative[idx]);
            return representative[idx];
        }
        void union_dsu(int x ,int y)
        {
            int repX = representative[x];
            int repY = representative[y];
            if(repX != repY)
            {
                if(height[x] <= height[y])
                {
                    representative[repX] = repY;
                    height[repY] = std::max(height[repY],1+height[repX]);
                }
                else{
                    representative[repY] = repX;
                    height[repX] = std::max(height[repX],1+height[repY]);
                }
            }
        }
};
#endif