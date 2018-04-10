#pragma once

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

#define INF std::numeric_limits<double>::max()

template <class T>
class Vertex {
	T info;                
	vector<Edge<T>*> adj;  
	bool visited;         
	bool processing;      
	int indegree;          

	Edge<T>* path;		
	double dist;			

	void addEdge(Vertex<T> *dest, double w);
	bool removeEdgeTo(Vertex<T> *d);
public:
	Vertex(T in);
	T getInfo() const;
	vector<Edge<T>*> getAdj() const;
	Edge<T>* getPath() const;
	double getDist() const;
	bool operator== (const Vertex<T> &v);
	friend class Graph<T>;
};

template <class T>
Vertex<T>::Vertex(T in) : info(in) {}

template <class T>
T Vertex<T>::getInfo() const {
	return info;
}

template <class T>
vector<Edge<T>*> Vertex<T>::getAdj() const {
	return adj;
}

template <class T>
Edge<T>* Vertex<T>::getPath() const {
	return path;
}

template <class T>
double Vertex<T>::getDist() const {
	return dist;
}

template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
	adj.push_back(new Edge<T>(this, d, w));
}

template <class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
	for (auto it = adj.begin(); it != adj.end(); it++)
		if ((*it)->dest == d) {
			adj.erase(it);
			return true;
		}
	return false;
}

template <class T>
bool Vertex<T>::operator== (const Vertex<T> &v) {
	return info == v.info && adj == v.adj;
}

template <class T>
struct vertexPointerGreatherThan {
	bool operator()(Vertex<T>* v1, Vertex<T>* v2) {
		return v1->getDist() > v2->getDist();
	}
};


template <class T>
class Edge {
	static int edgeId;
	int id;
	Vertex<T> *src;
	Vertex<T> *dest;      
	double weight;
	int maxNumVehicles;
	int currentNumVehicles;
public:
	Edge(Vertex<T> *s, Vertex<T> *d, double w);
	int getId() const;
	Vertex<T>* getSrc() const;
	Vertex<T>* getDest() const;
	double getWeight() const;
	int getMaxNumVehicles() const;
	int getCurrentNumVehicles() const;
	void resetEdgeId();
	bool operator== (const Edge<T> edge);
	friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
int Edge<T>::edgeId = 1;

template <class T>
Edge<T>::Edge(Vertex<T> *s, Vertex<T> *d, double w) : id(edgeId++) {
	this->src = s;
	this->dest = d;
	this->weight = w;
	this->maxNumVehicles = (int) weight;
	this->currentNumVehicles = rand() % maxNumVehicles;
}

template <class T>
int Edge<T>::getId() const {
	return id;
}

template <class T>
Vertex<T>* Edge<T>::getSrc() const {
	return src;
}

template <class T>
Vertex<T>* Edge<T>::getDest() const {
	return dest;
}

template <class T>
double Edge<T>::getWeight() const {
	return weight;
}

template<class T>
int Edge<T>::getMaxNumVehicles() const {
	return maxNumVehicles;
}

template<class T>
int Edge<T>::getCurrentNumVehicles() const {
	return currentNumVehicles;
}

template<class T>
void Edge<T>::resetEdgeId() {
	edgeId = 1;
}

template <class T>
bool Edge<T>::operator== (const Edge<T> edge) {
	return dest->getInfo() == edge.dest->getInfo() && weight == edge.weight;
}


template <class T>
class Graph {
	vector<Vertex<T>*> vertexSet;   

public:
	vector<Vertex<T> *> getVertexSet() const;
	int getNumVertex() const;
	bool addVertex(const T &in);
	bool removeVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w);
	bool removeEdge(Edge<T>* e);
	bool removeEdge(const T &sourc, const T &dest);

	Vertex<T>* findVertexByIndex(int idx) const;
	Vertex<T>* findVertex(const T &in) const;
	Edge<T>* findEdgeById(int idx) const;

	void randomizeNumVehicles();
	void dijkstraShortestPath(const T &s);
};

template<class T>
vector<Vertex<T>*> Graph<T>::getVertexSet() const {
	return vertexSet;
}

template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}

template <class T>
bool Graph<T>::addVertex(const T &in) {
	if (findVertex(in) != NULL)
		return false;
	vertexSet.push_back(new Vertex<T>(in));
	return true;
}

template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
	auto v1 = findVertex(sourc);
	auto v2 = findVertex(dest);
	if (v1 == NULL || v2 == NULL)
		return false;
	v1->addEdge(v2, w);
	return true;
}

template <class T>
Vertex<T>* Graph<T>::findVertexByIndex(int idx) const {
	return vertexSet.at(idx);
}

template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
	for (auto v : vertexSet)
		if (v->info == in)
			return v;
	return NULL;
}

template <class T>
Edge<T> * Graph<T>::findEdgeById(int idx) const {
	for (Vertex<T>* v : vertexSet)
		for (Edge<T>* e : v->adj)
			if (e->id == idx)
				return e;
	return NULL;
}

template<class T>
void Graph<T>::randomizeNumVehicles() {
	int numNewVehicles;
	for (Vertex<T>* v : vertexSet)
		for (Edge<T>* e : v->getAdj())
			if (e->currentNumVehicles != e->maxNumVehicles) {
				numNewVehicles = rand() % (e->maxNumVehicles - e->currentNumVehicles);
				if (rand() % 100 > 30)
					e->currentNumVehicles += numNewVehicles;
				else {
					e->currentNumVehicles -= numNewVehicles;
					if (e->currentNumVehicles < 0) 
						e->currentNumVehicles = 0;
				}
			}
}

template <class T>
bool Graph<T>::removeEdge(Edge<T>* e) {
	return removeEdge(e->src->info, e->dest->info);
}

template <class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
	auto v1 = findVertex(sourc);
	auto v2 = findVertex(dest);
	if (v1 == NULL || v2 == NULL)
		return false;
	return v1->removeEdgeTo(v2);
}

template <class T>
bool Graph<T>::removeVertex(const T &in) {
	for (auto it = vertexSet.begin(); it != vertexSet.end(); it++)
		if ((*it)->info == in) {
			auto v = *it;
			vertexSet.erase(it);
			for (auto u : vertexSet)
				u->removeEdgeTo(v);
			delete v;
			return true;
		}
	return false;
}

template<class T>
void Graph<T>::dijkstraShortestPath(const T & s) {
	vector<Vertex<T>*> p_queue;

	for (Vertex<T> *v : vertexSet) {
		v->dist = INF;
		v->path = NULL;
		v->processing = false;
	}
	
	Vertex<T> *v = findVertex(s);
	v->dist = 0;
	p_queue.push_back(v);

	make_heap(p_queue.begin(), p_queue.end());
	
	while (!p_queue.empty()) {

		Vertex<T> *v = p_queue.back();

		p_queue.pop_back();
		pop_heap(p_queue.begin(), p_queue.end());
		
		for (Edge<T>* e : v->adj) {
			Vertex<T> *w = e->dest;
			if (e->currentNumVehicles < e->maxNumVehicles && w->dist > v->dist + e->weight) {

				e->currentNumVehicles++;
				w->dist = v->dist + e->weight;
				w->path = e;
				
				if (!w->processing) {
					w->processing = true;
					p_queue.push_back(w);
				}

				make_heap(p_queue.begin(), p_queue.end(), vertexPointerGreatherThan<T>());
			}
		}
	}
}