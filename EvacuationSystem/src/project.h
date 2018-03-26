#pragma once

#include <fstream>

#include "graph.h"
#include "graphviewer.h"
#include "node.h"

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
	void openWindowGV();
	void printGV();
	void readNodesFile();
	void readEdgesFile();
	Node getNodeById(int idNode);
};