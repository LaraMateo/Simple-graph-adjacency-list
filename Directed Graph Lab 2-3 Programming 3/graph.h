//To prevent double declaration
#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include<vector>
#include<list>
#include<map>
#include <unordered_set>
#include <unordered_map>

namespace graphs
{
    class graph
        {
        public:
        bool ADDVERTEX(int n);
        bool REMOVEVERTEX(int n, int flag = 0);
        bool ADDEDGE(int n1, int n2, int flag = 0);
        bool REMOVEEDGE(int n1, int n2, int flag = 0);
        std::vector<int> nodes();
        std::vector<std::pair<int,int>> out_edges(int n);
        void BFS(); // Breadth First Search algorithm
        void DFS(); // Depth-first search
        };
}

// add any elements if needed
#endif // GRAPH_H

