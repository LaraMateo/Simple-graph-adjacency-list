#include <iostream>
#include "graph.h" 

using namespace std;
using namespace graphs;

int main()
{
    graph g1;
    g1.ADDVERTEX(1);
    g1.ADDVERTEX(33);
    g1.ADDVERTEX(6);
    g1.ADDVERTEX(9);
    g1.ADDVERTEX(11);
    g1.ADDVERTEX(2);
    g1.ADDVERTEX(3);
    g1.ADDVERTEX(7);
    g1.ADDVERTEX(15);
    g1.ADDVERTEX(4);
    g1.ADDVERTEX(5);
    g1.ADDEDGE(1,9);
    g1.ADDEDGE(1,11);
    g1.ADDEDGE(1, 2);
    g1.ADDEDGE(9, 3);
    g1.ADDEDGE(9, 7);
    g1.ADDEDGE(9, 15);
    g1.ADDEDGE(9, 11);
    g1.ADDEDGE(11, 7);
    g1.ADDEDGE(2, 7);
    g1.ADDEDGE(2, 15);
    g1.ADDEDGE(3, 4);
    g1.ADDEDGE(4, 5);
    g1.DFS();
}
