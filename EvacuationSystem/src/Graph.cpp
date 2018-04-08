#include "Graph.h"

using namespace std;

vector<Node*> Graph::getNodes() {
	return nodes;
}

vector<Edge*> Graph::getEdges() {
	return edges;
}

vector<Road*> Graph::getRoads() {
	return roads;
}

int Graph::getNumNodes() const {
	return nodes.size();
}

bool Graph::addNode(Node *in) {
	if (findNode(*in) != NULL)
		return false;
	nodes.push_back(in);
	return true;
}

bool Graph::removeNode(const Node &in) {
	for (auto it = nodes.begin(); it != nodes.end(); it++) {
		auto v = *it;
		if (*v == in) {
			nodes.erase(it);
			for (auto u : nodes)
				u->removeRoadTo(v);
			delete v;
			return true;
		}
	}
	return false;
}

bool Graph::addEdge(Edge* in) {
	edges.push_back(in);
	auto v1 = findNode(*in->src);
	auto v2 = findNode(*in->dest);
	if (v1 == NULL || v2 == NULL)
		return false;
	v1->addEdge(v2, in->weight);
	return true;
}

bool Graph::removeEdge(const Node &sourc, const Node &dest) {
	auto v1 = findNode(sourc);
	auto v2 = findNode(dest);
	if (v1 == NULL || v2 == NULL)
		return false;
	return v1->removeRoadTo(v2);
}

void Graph::addRoad(Road *r) {
	roads.push_back(r);
}

Node* Graph::findNode(const Node &in) const {
	for (auto v : nodes)
		if (*v == in)
			return v;
	return NULL;
}

void Graph::dijkstraShortestPath(const Node &s) {
	vector<Node*> p_queue;

	// initializing all vertices
	for (Node *v : nodes) {
		v->dist = numeric_limits<double>::max();
		v->path = NULL;
		v->processing = false;
	}

	// get initial vertex
	Node *v = findNode(s);
	// set its distance to 0
	v->dist = 0;
	p_queue.push_back(v);

	make_heap(p_queue.begin(), p_queue.end());

	while (!p_queue.empty()) {
		Node *v = p_queue.front();

		p_queue.pop_back();
		// pop vertex of minimum distance out of the heap
		pop_heap(p_queue.begin(), p_queue.end());

		for (Edge* e : v->adj) {
			Node *w = e->dest;
			if (w->dist > v->dist + e->weight) {
				w->dist = v->dist + e->weight;
				w->path = v;

				// if vertex is not in p_queue, insert it
				if (!w->processing) {
					w->processing = true;
					p_queue.push_back(w);
				}

				// reorganize p_queue - vertex of lower distance in the back
				make_heap(p_queue.begin(), p_queue.end(), Node::vertexPointerGreatherThan());
			}
		}
	}
}

void Graph::printInfo() {
	cout << ". Graph information" << endl;
	cout << "Number of nodes: " << nodes.size() << endl;
	cout << "Number of edges: " << edges.size() << endl;
	cout << "Number of roads: " << roads.size() << endl;
	cout << endl;
}