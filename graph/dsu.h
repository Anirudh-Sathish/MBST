#include<iostream>
#include<algorithm>
#include<vector>


#ifndef DSU_H
#define DSU_H
class DSU
{
    private:
        int *representative;
        int *height;
    public:
        DSU(int n)
        {
            representative = new int[n];
            height = new int[n];
            for(int i = 0 ; i < n; i++)
            {
                representative[i] = i;
                height[i] = 0;
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