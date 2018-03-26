#include "project.h"

Project::Project() {
	this->graph = new Graph<Node>();
	this->gv = new GraphViewer(GRAPH_WIDTH, GRAPH_HEIGHT, false);
}

Graph<Node>* Project::getGraph() {
	return graph;
}

GraphViewer* Project::getGV() {
	return gv;
}

void Project::setGraph(Graph<Node> *graph) {
	this->graph = graph;
}

void Project::setGV(GraphViewer *gv) {
	this->gv = gv;
}

void Project::openWindowGV() {
	gv->createWindow(600, 600);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");
}

void Project::printGV() {
	gv->rearrange();
}

void Project::readNodesFile() {

	ifstream nodesFile;
	string line;
	int semicolon1, semicolon2, idNode, x, y;

	/* reading nodes */
	nodesFile.open("EvacuationSystem/res/nodes.txt");

	while (getline(nodesFile, line)) {
		semicolon1 = line.find_first_of(';');
		idNode = stoi(line.substr(0, semicolon1));
		semicolon2 = line.find_last_of(';');
		x = stoi(line.substr(semicolon1 + 1, semicolon2));
		y = stoi(line.substr(semicolon2 + 1));
		
		graph->addVertex(Node(idNode, x, y));
		gv->addNode(idNode, x, y);
	}
	
	nodesFile.close();
}

void Project::readEdgesFile() {
	
	ifstream edgesFile;
	string line;
	int semicolon1, semicolon2, idEdge, idStart, idEnd;

	/* reading edges */
	edgesFile.open("EvacuationSystem/res/edges.txt");

	while (getline(edgesFile, line)) {
		semicolon1 = line.find_first_of(';');
		semicolon2 = line.find_last_of(';');
		idEdge = stoi(line.substr(0, semicolon1));
		idStart = stoi(line.substr(semicolon1 + 1, semicolon2));
		idEnd = stoi(line.substr(semicolon2 + 1));

		Node startNode = getNodeById(idStart);
		Node endNode = getNodeById(idEnd);

		double weight = sqrt(pow(startNode.getCoords().getX() - endNode.getCoords().getX(), 2)
			+ pow(startNode.getCoords().getY() - endNode.getCoords().getY(), 2));

		graph->addEdge(startNode, endNode, weight);
		gv->addEdge(idEdge, idStart, idEnd, EdgeType::DIRECTED);
	}
	
	edgesFile.close();
}

Node Project::getNodeById(int idNode) {

	for (auto node : graph->getVertexSet()) {
		if (node->getInfo().getId() == idNode) {
			return node->getInfo();
		}
	}
	return Node();
}