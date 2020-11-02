#include "graph.h"

std::map<int, std::list<int>> vertices_edges;

using namespace std;

namespace graphs
{

	bool graph::ADDVERTEX(int n) { //add_node
		std::cout << "Adding vertex " << n << " \n";
		map<int, list<int>>::iterator it = vertices_edges.find(n);
		if (it != vertices_edges.end()) {
			std::cout << "Vertex " << n << " already exists\n";
			return(false); // The graph already contains node n
		}
		vertices_edges[n];
		vector<int> vertices = nodes();
		vector<int>::iterator it1;
		for (it1 = vertices.begin(); it1 != vertices.end(); it1++) {
			out_edges(*it1);
		}
		std::cout << "\n";
		return(true); // The graph does not contain node n
	}

	bool graph::REMOVEVERTEX(int n) { // del_node
		std::cout << "Removing vertex " << n << " \n";
		map<int, list<int>>::iterator it = vertices_edges.find(n);
		if (it == vertices_edges.end()) {
			std::cout << "Vertex " << n << " do not exist\n";
			return(false); // The graph does not contain node n
		}
		vertices_edges.erase(it);
		for (it = vertices_edges.begin(); it != vertices_edges.end(); it++) {
			it->second.remove(n); // it->second is an inner list
		}
		vector<int> vertices = nodes();
		vector<int>::iterator it1;
		for (it1 = vertices.begin(); it1 != vertices.end(); it1++) {
			out_edges(*it1);
		}
		std::cout << "\n";
		return(true); // The graph already contains node n
	}

	bool graph::ADDEDGE(int n1, int n2, const int flag) {
		std::cout << "Adding edge " << n1 << "-" << n2 << " \n";
		map<int, list<int>>::iterator it;
		int counter = 0;
		pair<const int, list<int>> *edges_n1 = nullptr;
		for (it = vertices_edges.begin(); it != vertices_edges.end(); it++) {
			int key = it->first;
			if (key == n1) {
				counter++;
				edges_n1 = &(*it);
			}
			if (key == n2) {
				counter++;
			}
			if (counter == 2) {
				break;
			}
		}
		if (counter != 2) {
			std::cout << "At least one vertex do not exist\n";
			return(false); // The graph does not contain a node
		}
		else {
			list<int>::iterator it;
			list<int> innerList = edges_n1->second;
			for (it = innerList.begin(); it != innerList.end(); it++) {
				if (*it == n2) {
					std::cout << "The edge " << n1 << "-" << n2 << " already exists\n";
					return(false); // The graph already contains the edge <n1,n2>
				}
			}
			edges_n1->second.push_back(n2);

			if (flag == 1) {
				vector<int> vertices = nodes();
				vector<int>::iterator it1;
				for (it1 = vertices.begin(); it1 != vertices.end(); it1++) {
					out_edges(*it1);
				}
				std::cout << "\n";
				return(true);
			}
			
			ADDEDGE(n2, n1, 1);
			return(true); // The edge was successfully added
		}
	}

	bool graph::REMOVEEDGE(int n1, int n2, const int flag) {
		std::cout << "Removing edge " << n1 << "-" << n2 << " \n";
		map<int, list<int>>::iterator it = vertices_edges.find(n1);
		if (it == vertices_edges.end()) {
			std::cout << "At least one vertex do not exist\n";
			return(false); // The graph does not contain node n
		}
		else {
			list<int> *i = &(it->second);
			list<int>::iterator it;
			for (it = i->begin(); it != i->end(); it++) {
				if (*it == n2) {
					i->erase(it);

					if (flag == 1) {
						vector<int> vertices = nodes();
						vector<int>::iterator it1;
						for (it1 = vertices.begin(); it1 != vertices.end(); it1++) {
							out_edges(*it1);
						}
						std::cout << "\n";
						return(true);
					}
					REMOVEEDGE(n2, n1, 1);
					return(true); // The edge was successfully deleted
				}
			}
			std::cout << "The edge " << n1 << "-" << n2 << " do not exist\n";
			return(false); // The graph does not contain the edge <n1,n2>
		}
	}

	vector<int> graph::nodes() {
		map<int, list<int>>::iterator it;
		vector<int> nodes;
		cout << "Vertex: ";
		for (it = vertices_edges.begin(); it != vertices_edges.end(); it++) {
			cout << it->first << " ";
			nodes.push_back(it->first);
		}
		cout << "\n";
		return(nodes);
	}

	vector<pair<int, int>> graph::out_edges(int n) {
		vector<pair<int, int>> edges_n{};
		list<int>::iterator it;
		map<int, list<int>>::iterator innerList = vertices_edges.find(n);
		if (innerList == vertices_edges.end()) {
			return(edges_n); // The graph does not contain node n
		}
		pair<int, int> thisPair;
		thisPair.first = n;
		cout << "Vertex " << n << " -> ";
		for (it = innerList->second.begin(); it != innerList->second.end(); it++) {
			cout << *it << " ";
			thisPair.second = *it;
			edges_n.push_back(thisPair);
		}
		cout << "\n";
		return(edges_n);
	}
}
