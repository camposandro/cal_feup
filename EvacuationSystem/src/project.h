#pragma once

#include <fstream>

#include "Graph.h"
#include "Graphviewer.h"
#include "Node.h"

/* MACROS definition */
#define GRAPH_WIDTH		600
#define GRAPH_HEIGHT	600

class Project {

private:
	Graph<Node> *graph;
	GraphViewer *gv;

public:
	Project();
	Graph<Node> *getGraph();
	GraphViewer *getGV();
	void setGraph(Graph<Node> *graph);
	void setGV(GraphViewer *gv);
	void readNodesFile();
	void readEdgesFile();
	void openWindowGV();
	void printGV();
	Node getNodeById(int idNode);
	vector<Node> getDijkstraPath(Node dest);
};