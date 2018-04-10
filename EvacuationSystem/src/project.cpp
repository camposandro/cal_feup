#include "Project.h"

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
	}
	
	edgesFile.close();
}

void Project::loadNodesGV() {

	for (Vertex<Node>* vertex : graph->getVertexSet()) {
		Node node = vertex->getInfo();
		gv->addNode(node.getId(), node.getCoords().getX(), node.getCoords().getY());
	}
}

void Project::loadEdgesGV() {

	int edgeId = 1;
	for (Vertex<Node>* vertex : graph->getVertexSet()) {
		Node startNode = vertex->getInfo();
		for (Edge<Node>* e : vertex->getAdj()) {
			Node destNode = e->getDest()->getInfo();
			gv->addEdge(edgeId, startNode.getId(), destNode.getId(), EdgeType::DIRECTED);
			gv->setEdgeLabel(edgeId, to_string(e->getWeight()));
			edgeId++;
		} 
	}
}

Node Project::getNodeById(int idNode) {
	for (Vertex<Node>* node : graph->getVertexSet()) {
		if (node->getInfo().getId() == idNode) {
			return node->getInfo();
		}
	}
	return Node();
}

void Project::computeDijkstra() {

	char answer;
	int idStart, idDest;

	cout << "Insert vertex of start (out of " <<
		graph->getNumVertex() << "): ";
	cin >> idStart;
	cin.ignore();

	/* gets starting node */
	Node start = getNodeById(idStart);

	/* calculates all paths from starting node */
	graph->dijkstraShortestPath(start);

	do {
		cout << "Print all paths ? (Y/N) ";
		cin >> answer;
		answer = toupper(answer);
		cin.ignore();
	} while (answer != 'Y' && answer != 'N');

	if (answer == 'N') {
		cout << "Insert vertex of destination (out of " <<
			graph->getNumVertex() << "): ";
		cin >> idDest;
		cin.ignore();

		/* gets destination node */
		Node dest = getNodeById(idDest);

		vector<Node> path = getDijkstraPath(dest);
		this->printPath(path);
	}
	else {
		cout << endl << "Paths from Vertex " << start.getId() << ":\n";
		this->printAllPaths();
	}
}

vector<Node> Project::getDijkstraPath(Node dest) {
	vector<Node> fullPath;

	Vertex<Node>* v = graph->findVertex(dest);
	do {
		fullPath.push_back(v->getInfo());
		v = v->getPath();
	} while (v != NULL);

	return fullPath;
}

void Project::computeAstar() {

}

void Project::printPath(vector<Node> path) {
	ostringstream pathStr;

	if (path.size() == 1) {
		pathStr << "No path available!";
	}
	else {
		for (size_t i = path.size() - 1;; i--) {
			pathStr << path.at(i).getId();
			if (i == 0) break;
			else pathStr << "-";
		}
	}
	cout << pathStr.str() << endl;
}

void Project::printAllPaths() {
	for (Vertex<Node>* vertex : graph->getVertexSet()) {
		vector<Node> path = getDijkstraPath(vertex->getInfo());
		if (path.size() != 1) {
			cout << "to Vertex " << vertex->getInfo().getId() << ": ";
			printPath(path);
		}
	}
	cout << endl;
}
