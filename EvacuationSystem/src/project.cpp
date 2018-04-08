#include "Project.h"

Project::Project() {
	srand((unsigned int) time(NULL));
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

void Project::openWindowGv() {
	gv->createWindow(600, 600);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");
	gv->defineEdgeCurved(false);
}

void Project::printGv() {
	gv->rearrange();
}

void Project::updateGv() {
	for (Vertex<Node>* vertex : graph->getVertexSet()) {
		for (Edge<Node>* e : vertex->getAdj()) {

			string label = "ID " + to_string(e->getId()) + " - " +
				to_string(e->getCurrentNumVehicles()) +
				" | " + to_string(e->getMaxNumVehicles());

			gv->setEdgeLabel(e->getId(), label);
		}
	}
}

void Project::resetGv() {
	for (Vertex<Node>* node : graph->getVertexSet()) {
		gv->setVertexColor(node->getInfo().getId(), BLUE);
		for (Edge<Node>* edge : node->getAdj()) {
			gv->setEdgeColor(edge->getId(), BLACK);
			gv->setEdgeThickness(edge->getId(), 1);
		}
	}
}

void Project::readNodesFile() {

	ifstream nodesFile;
	string line;
	int semicolon1, semicolon2, idNode, x, y;

	nodesFile.open(NODES_FILE);

	while (getline(nodesFile, line)) {
		semicolon1 = line.find_first_of(';');
		semicolon2 = line.find_last_of(';');

		idNode = stoi(line.substr(0, semicolon1));
		x = stoi(line.substr(semicolon1 + 1, semicolon2));
		y = stoi(line.substr(semicolon2 + 1));

		graph->addVertex(Node(x, y));
	}

	nodesFile.close();
}

void Project::readEdgesFile() {

	ifstream edgesFile;
	string line;
	int semicolon1, semicolon2, idEdge, idStart, idDest;

	edgesFile.open(EDGES_FILE);

	while (getline(edgesFile, line)) {
		semicolon1 = line.find_first_of(';');
		semicolon2 = line.find_last_of(';');

		idEdge = stoi(line.substr(0, semicolon1));
		idStart = stoi(line.substr(semicolon1 + 1, semicolon2));
		idDest = stoi(line.substr(semicolon2 + 1));

		Node startNode = getVertexByNodeId(idStart)->getInfo();
		Node destNode = getVertexByNodeId(idDest)->getInfo();

		graph->addEdge(startNode, destNode, startNode.calcDist(destNode));
	}

	edgesFile.close();
}

void Project::readTrafficFile() {

	ifstream trafficFile;
	string line;
	int semicolon1, semicolon2, idVehicle, idStart, idDest;

	trafficFile.open(TRAFFIC_FILE);

	while (getline(trafficFile, line)) {
		semicolon1 = line.find_first_of(';');
		semicolon2 = line.find_last_of(';');

		idVehicle = stoi(line.substr(0, semicolon1));
		idStart = stoi(line.substr(semicolon1 + 1, semicolon2));
		idDest = stoi(line.substr(semicolon2 + 1));

		Node startNode = getVertexByNodeId(idStart)->getInfo();
		Node destNode = getVertexByNodeId(idDest)->getInfo();

		traffic.push(new Vehicle(startNode, destNode));
	}
}

void Project::loadNodesGv() {
	for (Vertex<Node>* vertex : graph->getVertexSet()) {
		Node node = vertex->getInfo();
		gv->addNode(node.getId(), node.getCoords().getX(), node.getCoords().getY());
		gv->setVertexLabel(node.getId(), to_string(node.getId()));
	}
}

void Project::loadEdgesGv() {
	for (Vertex<Node>* vertex : graph->getVertexSet()) {
		Node startNode = vertex->getInfo();
		for (Edge<Node>* e : vertex->getAdj()) {
			Node destNode = e->getDest()->getInfo();
			gv->addEdge(e->getId(), startNode.getId(), destNode.getId(), EdgeType::DIRECTED);
		}
	}
	updateGv();
}

Vertex<Node>* Project::getVertexByNodeId(int idNode) {
	for (Vertex<Node>* v : graph->getVertexSet())
		if (v->getInfo().getId() == idNode)
			return v;
	return NULL;
}

vector<Edge<Node>*> Project::getDijkstraPath(Node dest) {
	vector<Edge<Node>*> fullPath;

	Vertex<Node>* v = graph->findVertex(dest);
	while (v->getPath() != NULL) {
		fullPath.push_back(v->getPath());
		v = v->getPath()->getSrc();
	}

	return fullPath;
}

void Project::printPath(vector<Edge<Node>*> path) {
	ostringstream pathStr;

	if (path.size() == 0) {
		pathStr << "No path available!";
	}
	else {
		for (size_t i = path.size() - 1;; i--) {
			Edge<Node>* edge = path.at(i);

			// paint path edges on the Gv
			gv->setEdgeThickness(path.at(i)->getId(), 3);
			gv->setEdgeColor(path.at(i)->getId(), YELLOW);

			// paint path nodes on the Gv and on the CLI
			pathStr << edge->getSrc()->getInfo().getId() << "->";
			if (i != 0) {
				if (i == path.size() - 1)
					gv->setVertexColor(edge->getSrc()->getInfo().getId(), RED);
			}
			else {
				gv->setVertexColor(edge->getDest()->getInfo().getId(), GREEN);
				pathStr << edge->getDest()->getInfo().getId();
				break;
			}
		}
	}

	printGv();
	cout << pathStr.str() << endl;
}

void Project::printAllPaths() {
	for (Vertex<Node>* vertex : graph->getVertexSet()) {
		vector<Edge<Node>*> path = getDijkstraPath(vertex->getInfo());
		if (path.size() > 0) {
			cout << "to Vertex " << vertex->getInfo().getId() << ": ";
			printPath(path);
		}
	}
	cout << endl;
}

void Project::testDijkstra() {

	char answer;
	int idStart, idDest;
	bool validIndex;

	resetGv();

	do {
		validIndex = false;

		cout << "-> Insert vertex of start: ";
		cin >> idStart;
		cin.ignore();

		if (idStart > 0 && idStart < graph->getNumVertex())
			validIndex = true;
		else
			cout << ". Insert a valid vertex index!\n";

	} while (!validIndex);

	Node start = getVertexByNodeId(idStart)->getInfo();
	graph->dijkstraShortestPath(start);

	do {
		cout << ". Print all paths ? (Y/N) ";
		cin >> answer;
		answer = toupper(answer);
		cin.ignore();
	} while (answer != 'Y' && answer != 'N');

	if (answer == 'N') {

		do {
			validIndex = false;

			cout << "-> Insert vertex of destination: ";
			cin >> idDest;
			cin.ignore();

			if (idDest > 0 && idDest < graph->getNumVertex())
				validIndex = true;
			else
				cout << ". Insert a valid vertex index!\n";

		} while (!validIndex);

		Node dest = getVertexByNodeId(idDest)->getInfo();

		vector<Edge<Node>*> path = getDijkstraPath(dest);
		if (path.size() > 0) {
			cout << "\n. Path from vertex " << start.getId()
				<< " to vertex " << dest.getId() << ": ";
			this->printPath(path);
		}
		else cout << "\nNo path available!\n";

		cout << endl;
	}
	else {
		cout << "\n. Available paths from Vertex " << start.getId() << ":\n";
		this->printAllPaths();
	}

	graph->randomizeNumVehicles();
	updateGv();
}

void Project::testAstar() {

}

void Project::divertTraffic() {

	int numVehicles = traffic.size();
	double totalDijkstraTime = 0;
	Vehicle* v = NULL;
	
	if (!traffic.empty()) {
		cout << ". Processing traffic ..." << endl;

		while (!traffic.empty()) {

			v = traffic.front();
			traffic.pop();
			
			auto start = chrono::high_resolution_clock::now();
			graph->dijkstraShortestPath(v->getStartNode());
			auto finish = chrono::high_resolution_clock::now();
			totalDijkstraTime += chrono::duration_cast<chrono::microseconds>(finish - start).count();
			
			vector<Edge<Node>*> path = getDijkstraPath(v->getDestNode());
			cout << ". Path for vehicle " << v->getId() << ": ";
			printPath(path);
			Sleep(2000);

			resetGv();
			updateGv();
			graph->randomizeNumVehicles();
		}

		cout << ". Dijkstra processing average time (micro-seconds) = "
			<< (totalDijkstraTime / (graph->getNumVertex())) << endl;
	} 
	else cout << ". No traffic to be processed!\n";
	cout << endl;
}

void Project::reportAccident() {

	int id;
	Edge<Node>* e = NULL;

	cout << ". To leave insert 0!" << endl;
	do {
		cout << "-> Insert occurrence's location (edge id): ";
		cin >> id;
		cin.ignore();

		e = graph->findEdgeById(id);
		if (e == NULL)
			cout << ". Edge inserted does not exist!";
		cout << endl;

	} while (e == NULL && id != 0);

	if (graph->removeEdge(e)) {
		gv->setEdgeThickness(e->getId(), 3);
		gv->setEdgeColor(e->getId(), RED);
		printGv();
	}
	else cout << ". Could not remove edge!";
}