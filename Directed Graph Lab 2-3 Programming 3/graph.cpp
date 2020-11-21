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
		int number_of_components;

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

		int starting_node;
		vector<int> nodes_to_search;
		if (!order_nodes.empty()) {
			starting_node = order_nodes[0];
			nodes_to_search = { starting_node };

			cout << "-------------------- BGS -------------------- \n";
			cout << "Order of search:  \n";
			number_of_components = 1;
		}
		else {
			cout << "-------------------- BGS -------------------- \n";
			cout << "The graph is empty  \n";
			number_of_components = 0;
		}

		while(!order_nodes.empty()) {

			if (nodes_to_search.empty()) {
				nodes_to_search = { order_nodes[0] };
				number_of_components++;
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
		cout << "\nThe graph has " << number_of_components << " component(s) \n";
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

		int starting_node;
		int number_of_components;
		set<tuple<int, int>> edges;
		vector<int> nodes_to_search;
		if (!order_nodes.empty()) {
			starting_node = order_nodes[0];
			nodes_to_search = { starting_node };

			cout << "-------------------- DFS -------------------- \n";
			cout << "Order of search:  \n";
			number_of_components = 1;
		}
		else {
			cout << "-------------------- DFS -------------------- \n";
			cout << "The graph is empty  \n";
			number_of_components = 0;
		}


		while (!order_nodes.empty()) {

			if (nodes_to_search.empty()) {
				nodes_to_search = { order_nodes[0] };
				number_of_components++;
			}

			int current_node = nodes_to_search[0];
			list<int> child_nodes = vertices_edges.find(current_node)->second;
			list<int>::iterator it;
			vector<int>::iterator it1;
			vector<int> order_child_nodes = {};

			// Create an order vector of child nodes connected to current node  -> order_child_nodes
			for (it = child_nodes.begin(); it != child_nodes.end(); it++) {
				int element = *it;
				edges.insert(make_tuple(current_node, element));
				for (it1 = nodes_to_search.begin(); it1 != nodes_to_search.end(); it1++) {
					// Delete the nodes in nodes to search that are child nodes of current node
					// This avoid unnecessary repetitions in nodes to search
					int node = *it1;
					if (element == node) {
						nodes_to_search.erase(it1);
						break;
					}
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

			nodes_to_search.insert(nodes_to_search.begin() + 1, order_child_nodes.begin(), order_child_nodes.end());
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
		cout << "\nThe graph has " << number_of_components << " component(s) \n";
		if (number_of_components == 1) {
			cout << "The graph is connected " << "\n";

			cout << "Spanning tree of the graph:  " << "\n";
			// Calculate spanning tree
			set<tuple<int, int>>::iterator it3;
			set<tuple<int, int>>::iterator it4;
			bool repeated;
			for (it3 = edges.begin(); it3 != edges.end(); ++it3) {
				repeated = false;
				it4 = edges.find(*it3);
				for (it4.operator++(); it4 != edges.end(); ++it4) {
					if (get<1>(*it3) == get<1>(*it4)) {
						repeated = true;
						break;
					}
				}
				if (!repeated) {
					cout << " { " << get<0>(*it3) << " , " << get<1>(*it3) << " } ";
				}
			}
		}
		else if (number_of_components > 1) {
			cout << "The graph is NOT connected (NO spanning tree) " << "\n";
		}
		cout << "\n\n";
	}

	void graph::Connectivity() {
		int vertex_degree;
		bool eulerian = true;
		map<int, int> vertices_degree;
		map<int, list<int>>::iterator it;
		for (it = vertices_edges.begin(); it != vertices_edges.end(); it++) {
			vertex_degree = it->second.size();
			vertices_degree.insert(pair<int, int>(it->first, vertex_degree));
		}

		map<int, int>::iterator it2;
		for (it2 = vertices_degree.begin(); it2 != vertices_degree.end(); it2++) {
			if (it2->second % 2 != 0) {
				eulerian = false;
			}
			cout << "Vertex " << it2->first << " has degree of " << it2->second << "\n";
		}

		if (eulerian) {
			cout << "\nThe graph is Eulerian \n";
		}
		else {
			cout << "\nThe graph is NOT Eulerian \n";
		}
	}

	bool graph::Cycle4() {
		map<int, list<int>>::iterator it;
		map<int, list<int>> copy_vertices_edges = vertices_edges;
		bool cycle = false;
		for (it = vertices_edges.begin(); it != vertices_edges.end(); it++) {
			list<int>::iterator it2;
			for (it2 = it->second.begin(); it2 != it->second.end(); it2++) {
				map<int, list<int>>::iterator it3 = vertices_edges.find(*it2);
				list<int>::iterator it4;
				for (it4 = it3->second.begin(); it4 != it3->second.end(); it4++) {
					if (*it4 == it->first) {
						continue;
					}
					map<int, list<int>>::iterator it5 = vertices_edges.find(*it4);
					list<int>::iterator it6;
					for (it6 = it5->second.begin(); it6 != it5->second.end(); it6++) {
						if (*it6 == it->first || *it6 == *it2) {
							continue;
						}
						map<int, list<int>>::iterator it7 = vertices_edges.find(*it6);
						list<int>::iterator it8;
						for (it8 = it7->second.begin(); it8 != it7->second.end(); it8++) {
							if (*it8 == *it4) {
								continue;
							}
							if (*it8 == it->first) {
								bool inner_connected = false;
								map<int, list<int>>::iterator it9 = vertices_edges.find(it->first);
								list<int>::iterator it10;
								map<int, list<int>>::iterator it11 = vertices_edges.find(*it6);
								list<int>::iterator it12;
								for (it10 = it9->second.begin(); it10 != it9->second.end(); it10++) {
									if (*it10 == *it4) {
										inner_connected = true;
									}
								}
								for (it12 = it11->second.begin(); it12 != it11->second.end(); it12++) {
									if (*it12 == *it2) {
										inner_connected = true;
									}
								}
								if (!inner_connected) {
									cycle = true;
									cout << "YES, given graph contains cycle of length 4 as induced subgraph formed by the following vertices: " << it->first << " " << *it2 << " " << *it4 << " " << *it6 << " \n";
									return(cycle);
								}
							}
						}
					}
				}
			}
			//REMOVEVERTEX(it->first);
		}
		vertices_edges = copy_vertices_edges;
		cout << "NO, there exists no cycle of length 4 as induced subgraph in given graph \n";
		return(cycle);
	}
}