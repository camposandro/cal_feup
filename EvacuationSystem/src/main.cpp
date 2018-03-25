#include <iostream>
#include <fstream>

#include "graphviewer.h"

/* MACROS definition */
#define GRAPH_WIDTH		600
#define GRAPH_HEIGHT	600

/* Functions prototypes */
void initGraph(GraphViewer *gv);
void menu(GraphViewer *gv);
void readNodesFile(GraphViewer *gv);
void readEdgesFile(GraphViewer *gv);

int main() {

	GraphViewer *gv = new GraphViewer(GRAPH_WIDTH, GRAPH_HEIGHT, false);
	initGraph(gv);
	//menu(gv);

	return 0;
}

void initGraph(GraphViewer *gv) {

	gv->createWindow(600, 600);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");

	readNodesFile(gv);
	readEdgesFile(gv);

	gv->rearrange();
}


void readNodesFile(GraphViewer *gv) {

	ifstream nodesFile;
	string line;
	int semicolon1, semicolon2, idNode, x, y;

	/* reading nodes */
	nodesFile.open("nos.txt");

	while (getline(nodesFile, line)) {
		semicolon1 = line.find_first_of(';');
		idNode = atoi(line.substr(0, semicolon1).c_str());
		semicolon2 = line.find_last_of(';');
		x = atoi(line.substr(semicolon1 + 1, semicolon2).c_str());
		y = atoi(line.substr(semicolon2 + 1).c_str());
		gv->addNode(idNode, x, y);
	}

	nodesFile.close();
}

void readEdgesFile(GraphViewer *gv) {

	ifstream edgesFile;
	string line;
	int semicolon1, semicolon2, idEdge, idStart, idEnd;

	/* reading edges */
	edgesFile.open("arestas.txt");

	while (getline(edgesFile, line)) {
		semicolon1 = line.find_first_of(';');
		semicolon2 = line.find_last_of(';');
		idEdge = atoi(line.substr(0, semicolon1).c_str());
		idStart = atoi(line.substr(semicolon1 + 1, semicolon2).c_str());
		idEnd = atoi(line.substr(semicolon2 + 1).c_str());
		gv->addEdge(idEdge, idStart, idEnd, EdgeType::DIRECTED);
	}

	edgesFile.close();
}
