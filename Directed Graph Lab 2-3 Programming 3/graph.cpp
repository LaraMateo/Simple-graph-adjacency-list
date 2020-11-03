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

	bool graph::REMOVEVERTEX(int n, int flag) { // del_node
		if (flag == 0) {
			std::cout << "Removing vertex " << n << " \n";
		}
		map<int, list<int>>::iterator it = vertices_edges.find(n);
		if (it == vertices_edges.end()) {
			if (flag == 0) {
				std::cout << "Vertex " << n << " do not exist\n";
			}
			return(false); // The graph does not contain node n
		}
		vertices_edges.erase(it);
		for (it = vertices_edges.begin(); it != vertices_edges.end(); it++) {
			it->second.remove(n); // it->second is an inner list
		}
		if (flag == 0) {
			vector<int> vertices = nodes();
			vector<int>::iterator it1;
			for (it1 = vertices.begin(); it1 != vertices.end(); it1++) {
				out_edges(*it1);
			}
			std::cout << "\n";
		}
		return(true); // The graph already contains node n
	}

	bool graph::ADDEDGE(int n1, int n2, int flag) {
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

	bool graph::REMOVEEDGE(int n1, int n2, int flag) {
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

	void graph::BFS() {

		map<int, list<int>>::iterator it;
		map<int, list<int>> copy_vertices_edges = vertices_edges;
		vector<int>::iterator it1;
		vector<int> order_nodes = {};
		int key;

		// Create an order vector of the nodes in the graph -> order_nodes
		for (it = vertices_edges.begin(); it != vertices_edges.end(); it++) {
			key = it->first;
			if (order_nodes.empty()) {
				order_nodes.push_back(key);
				continue;
			}
			bool itBreak = false;
			for (it1 = order_nodes.begin(); it1 != order_nodes.end(); it1++) {
				if (key < *it1) {
					order_nodes.insert(it1, key);
					itBreak = true;
					break;
				}
			}
			if (!itBreak) {
				order_nodes.push_back(key);
			}
		}

		int starting_node = order_nodes[0];
		vector<int> nodes_to_search = {starting_node};

		cout << "-------------------- BGS -------------------- \n";
		cout << "Order of search:  \n";
		while(!order_nodes.empty()) {

			if (nodes_to_search.empty()) {
				nodes_to_search = { order_nodes[0] };
			}


			int current_node = nodes_to_search[0];
			list<int> child_nodes = vertices_edges.find(current_node)->second;
			list<int>::iterator it;
			vector<int>::iterator it1;
			vector<int> order_child_nodes = {};
			bool flag = false;

			// Create an order vector of child nodes connected to current node  -> order_child_nodes
			for (it = child_nodes.begin(); it != child_nodes.end(); it++) {
				int element = *it;
				for (it1 = nodes_to_search.begin(); it1 != nodes_to_search.end(); it1++) {
					int node = *it1;
					if (element == node) {
						flag = true;
						break;
					}
				}
				if(flag){
					continue;
				}
				if (order_child_nodes.empty()) {
					order_child_nodes.push_back(element);
					continue;
				}
				bool itBreak = false;
				for (it1 = order_child_nodes.begin(); it1 != order_child_nodes.end(); it1++) {
					if (element < *it1) {
						order_child_nodes.insert(it1, element);
						itBreak = true;
						break;
					}
				}
				if (!itBreak) {
					order_child_nodes.push_back(element);
				}
			}

			nodes_to_search.insert(nodes_to_search.end(), order_child_nodes.begin(), order_child_nodes.end());
			if (current_node == starting_node) {
				cout << current_node;
			}
			else {
				cout << ", " << current_node;
			}
			nodes_to_search.erase(nodes_to_search.begin());
			REMOVEVERTEX(current_node, 1);
			for (it1 = order_nodes.begin(); it1 != order_nodes.end(); it1++) {
				if (*it1 == current_node) {
					order_nodes.erase(it1);
					break;
				}
			}
		}
		vertices_edges = copy_vertices_edges;
		cout << "\n";
	}

	void graph::DFS() {

		map<int, list<int>>::iterator it;
		map<int, list<int>> copy_vertices_edges = vertices_edges;
		vector<int>::iterator it1;
		vector<int> order_nodes = {};
		int key;

		// Create an order vector of the nodes in the graph -> order_nodes
		for (it = vertices_edges.begin(); it != vertices_edges.end(); it++) {
			key = it->first;
			if (order_nodes.empty()) {
				order_nodes.push_back(key);
				continue;
			}
			bool itBreak = false;
			for (it1 = order_nodes.begin(); it1 != order_nodes.end(); it1++) {
				if (key < *it1) {
					order_nodes.insert(it1, key);
					itBreak = true;
					break;
				}
			}
			if (!itBreak) {
				order_nodes.push_back(key);
			}
		}

		int starting_node = order_nodes[0];
		vector<int> nodes_to_search = { starting_node };

		cout << "-------------------- DFS -------------------- \n";
		cout << "Order of search:  \n";

		while (!order_nodes.empty()) {

			if (nodes_to_search.empty()) {
				nodes_to_search = { order_nodes[0] };
			}

			int current_node = nodes_to_search[0];
			list<int> child_nodes = vertices_edges.find(current_node)->second;
			list<int>::iterator it;
			vector<int>::iterator it1;
			vector<int> order_child_nodes = {};
			bool flag = false;

			// Create an order vector of child nodes connected to current node  -> order_child_nodes
			for (it = child_nodes.begin(); it != child_nodes.end(); it++) {
				int element = *it;
				for (it1 = nodes_to_search.begin(); it1 != nodes_to_search.end(); it1++) {
					int node = *it1;
					if (element == node) {
						flag = true;
						break;
					}
				}
				if (flag) {
					continue;
				}
				if (order_child_nodes.empty()) {
					order_child_nodes.push_back(element);
					continue;
				}
				bool itBreak = false;
				for (it1 = order_child_nodes.begin(); it1 != order_child_nodes.end(); it1++) {
					if (element < *it1) {
						order_child_nodes.insert(it1, element);
						itBreak = true;
						break;
					}
				}
				if (!itBreak) {
					order_child_nodes.push_back(element);
				}
			}

			nodes_to_search.insert(nodes_to_search.begin()+1 , order_child_nodes.begin(), order_child_nodes.end());
			if (current_node == starting_node) {
				cout << current_node;
			}
			else {
				cout << ", " << current_node;
			}
			nodes_to_search.erase(nodes_to_search.begin());
			REMOVEVERTEX(current_node, 1);
			for (it1 = order_nodes.begin(); it1 != order_nodes.end(); it1++) {
				if (*it1 == current_node) {
					order_nodes.erase(it1);
					break;
				}
			}
		}
		vertices_edges = copy_vertices_edges;
		cout << "\n";
	}
}