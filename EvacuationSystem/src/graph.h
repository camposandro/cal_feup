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
	T getInfo();
	vector<Edge<T>*> getAdj();
	Edge<T>* getPath();
	double getDist();
	bool operator== (const Vertex<T> &v);
	friend class Graph<T>;
};

template <class T>
Vertex<T>::Vertex(T in) : info(in) {}

template <class T>
T Vertex<T>::getInfo() {
	return info;
}

template <class T>
vector<Edge<T>*> Vertex<T>::getAdj() {
	return adj;
}

template <class T>
Edge<T>* Vertex<T>::getPath() {
	return path;
}

template <class T>
double Vertex<T>::getDist() {
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
	int getId();
	Vertex<T>* getSrc();
	Vertex<T>* getDest();
	double getWeight();
	int getMaxNumVehicles();
	int getCurrentNumVehicles();
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
int Edge<T>::getId() {
	return id;
}

template <class T>
Vertex<T>* Edge<T>::getSrc() {
	return src;
}

template <class T>
Vertex<T>* Edge<T>::getDest() {
	return dest;
}

template <class T>
double Edge<T>::getWeight() {
	return weight;
}

template<class T>
int Edge<T>::getMaxNumVehicles() {
	return maxNumVehicles;
}

template<class T>
int Edge<T>::getCurrentNumVehicles() {
	return currentNumVehicles;
}

template <class T>
bool Edge<T>::operator== (const Edge<T> edge) {
	return dest->getInfo() == edge.dest->getInfo() && weight == edge.weight;
}


template <class T>
class Graph {
	vector<Vertex<T>*> vertexSet;   

	void dfsVisit(Vertex<T> *v, vector<T> & res) const;
	bool dfsIsDAG(Vertex<T> *v) const;
public:
	vector<Vertex<T> *> getVertexSet();
	int getNumVertex() const;
	bool addVertex(const T &in);
	bool removeVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w);
	bool removeEdge(Edge<T>* e);
	bool removeEdge(const T &sourc, const T &dest);
	vector<T> dfs() const;
	vector<T> bfs(const T &source) const;
	vector<T> topsort() const;
	int maxNewChildren(const T &source, T &inf) const;
	bool isDAG() const;

	Vertex<T>* findVertexByIndex(int idx) const;
	Vertex<T>* findVertex(const T &in) const;
	Edge<T>* findEdgeById(int idx) const;

	void randomizeNumVehicles();
	void dijkstraShortestPath(const T &s);
};

template<class T>
vector<Vertex<T>*> Graph<T>::getVertexSet() {
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
	for (Vertex<T>* v : vertexSet)
		for (Edge<T>* e : v->getAdj())
			if (e->currentNumVehicles != e->maxNumVehicles) {
				int numNewVehicles = rand() % (e->maxNumVehicles - e->currentNumVehicles);
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

template <class T>
vector<T> Graph<T>::dfs() const {
	vector<T> res;
	for (auto v : vertexSet)
		v->visited = false;
	for (auto v : vertexSet)
		if (!v->visited)
			dfsVisit(v, res);
	return res;
}

template <class T>
void Graph<T>::dfsVisit(Vertex<T> *v, vector<T> & res) const {
	v->visited = true;
	res.push_back(v->info);
	for (auto & e : v->adj) {
		auto w = e.dest;
		if (!w->visited)
			dfsVisit(w, res);
	}
}

template <class T>
vector<T> Graph<T>::bfs(const T & source) const {
	vector<T> res;
	auto s = findVertex(source);
	if (s == NULL)
		return res;
	queue<Vertex<T> *> q;
	for (auto v : vertexSet)
		v->visited = false;
	q.push(s);
	s->visited = true;
	while (!q.empty()) {
		auto v = q.front();
		q.pop();
		res.push_back(v->info);
		for (auto & e : v->adj) {
			auto w = e.dest;
			if (!w->visited) {
				q.push(w);
				w->visited = true;
			}
		}
	}
	return res;
}

template<class T>
vector<T> Graph<T>::topsort() const {
	vector<T> res;

	for (auto v : vertexSet)
		v->indegree = 0;
	for (auto v : vertexSet)
		for (auto & e : v->adj)
			e.dest->indegree++;

	queue<Vertex<T>*> q;
	for (auto v : vertexSet)
		if (v->indegree == 0)
			q.push(v);

	while (!q.empty()) {
		Vertex<T>* v = q.front();
		q.pop();
		res.push_back(v->info);
		for (auto & e : v->adj) {
			auto w = e.dest;
			w->indegree--;
			if (w->indegree == 0)
				q.push(w);
		}
	}

	if (res.size() != vertexSet.size()) {
		cout << "Ordenacao Impossivel!" << endl;
		res.clear();
		return res;
	}

	return res;
}

template <class T>
int Graph<T>::maxNewChildren(const T & source, T &inf) const {
	auto s = findVertex(source);
	if (s == NULL)
		return 0;
	queue<Vertex<T> *> q;
	int maxChildren = 0;
	inf = s->info;
	for (auto v : vertexSet)
		v->visited = false;
	q.push(s);
	s->visited = true;
	while (!q.empty()) {
		auto v = q.front();
		q.pop();
		int nChildren = 0;
		for (auto & e : v->adj) {
			auto w = e.dest;
			if (!w->visited) {
				w->visited = true;
				q.push(w);
				nChildren++;
			}
		}
		if (nChildren>maxChildren) {
			maxChildren = nChildren;
			inf = v->info;
		}
	}
	return maxChildren;
}


template <class T>
bool Graph<T>::isDAG() const {
	for (auto v : vertexSet) {
		v->visited = false;
		v->processing = false;
	}
	for (auto v : vertexSet)
		if (!v->visited)
			if (!dfsIsDAG(v))
				return false;
	return true;
}

template <class T>
bool Graph<T>::dfsIsDAG(Vertex<T> *v) const {
	v->visited = true;
	v->processing = true;
	for (auto & e : v->adj) {
		auto w = e.dest;
		if (w->processing)
			return false;
		if (!w->visited)
			if (!dfsIsDAG(w))
				return false;
	}
	v->processing = false;
	return true;
}

template<class T>
void Graph<T>::dijkstraShortestPath(const T & s) {
	vector<Vertex<T>*> p_queue;

	// initializing all vertices
	for (Vertex<T> *v : vertexSet) {
		v->dist = INF;
		v->path = NULL;
		v->processing = false;
	}
	
	// get initial vertex
	Vertex<T> *v = findVertex(s);
	// set its distance to 0
	v->dist = 0;
	p_queue.push_back(v);

	make_heap(p_queue.begin(), p_queue.end());

	while (!p_queue.empty()) {
		Vertex<T> *v = p_queue.back();

		p_queue.pop_back();
		// pop vertex of minimum distance out of the heap
		pop_heap(p_queue.begin(), p_queue.end());
		
		for (Edge<T>* e : v->adj) {
			Vertex<T> *w = e->dest;
			if (e->currentNumVehicles < e->maxNumVehicles && w->dist > v->dist + e->weight) {
				e->currentNumVehicles++;
				w->dist = v->dist + e->weight;
				w->path = e;
				
				// if vertex is not in p_queue, insert it
				if (!w->processing) {
					w->processing = true;
					p_queue.push_back(w);
				}
				
				// reorganize p_queue - vertex of lower distance in the back
				make_heap(p_queue.begin(), p_queue.end(), vertexPointerGreatherThan<T>());
			}
		}
	}
}