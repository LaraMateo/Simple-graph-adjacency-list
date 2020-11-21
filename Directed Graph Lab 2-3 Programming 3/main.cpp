#include <iostream>
#include "graph.h" 

using namespace std;
using namespace graphs;

int main()
{
    graph g1;
    g1.ADDVERTEX(1);
    g1.ADDVERTEX(2);
    g1.ADDVERTEX(3);
    g1.ADDVERTEX(4);
    g1.ADDVERTEX(5);
    g1.ADDVERTEX(6);
    g1.ADDEDGE(1, 2);
    g1.ADDEDGE(1, 3);
    g1.ADDEDGE(1, 4);
    g1.ADDEDGE(2, 4);
    g1.ADDEDGE(4, 3);
    g1.Cycle4();
}
