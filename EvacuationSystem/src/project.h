#pragma once

#include <fstream>
#include <sstream>
#include <ctime>
#include <chrono>
#include "Graph.h"
#include "Graphviewer.h"
#include "Node.h"
#include "Vehicle.h"

#define GRAPH_WIDTH		600
#define GRAPH_HEIGHT	600
#define NODES_FILE		"EvacuationSystem/res/nodes.txt"
#define EDGES_FILE		"EvacuationSystem/res/edges.txt"
#define TRAFFIC_FILE	"EvacuationSystem/res/traffic.txt"

class Project {

private:
	Graph<Node> *graph;
	GraphViewer *gv;
	std::queue<Vehicle*> *traffic;

public:
	Project();

	Graph<Node> *getGraph();
	GraphViewer *getGV();
	void setGraph(Graph<Node> *graph);
	void setGV(GraphViewer *gv);
	Vertex<Node>* getVertexByNodeId(int idNode);
	vector<Edge<Node>*> getDijkstraPath(Node dest);
	vector<Edge<Node>*> getAstarPath(Node dest);

	void generateRandomGraph();
	void generateRandomTraffic();
	void readNodesFile();
	void readEdgesFile();
	void readTrafficFile();
	void resetGraph();
	void resetTraffic();

	void openWindowGv();
	void loadNodesGv();
	void loadEdgesGv();
	void printGv();
	void updateGv();
	void cleanGv();
	void resetGv();

	void testDijkstra();
	void testAstar();

	void reportAccident();
	void printTraffic();
	void divertTraffic();

	void printPath(vector<Edge<Node>*> path);
	void printAllPaths();
};
