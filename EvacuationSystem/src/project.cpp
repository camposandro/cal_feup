#include "Project.h"

Project::Project() {
	srand((unsigned int) time(NULL));
	this->graph = new Graph<Node>();
	this->traffic = new queue<Vehicle*>();
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

void Project::generateRandomGraph() {
	int numNodes, numEdges, destIndex;

	do {
		numNodes = rand() % 30;
	} while (numNodes == 0);

	for (int i = 0; i < numNodes; i++)
		graph->addVertex(Node(rand() % 600, rand() % 600));

	for (Vertex<Node>* v : graph->getVertexSet()) {
		Node startNode = v->getInfo();
		
		do {
			numEdges = rand() % 4;
		} while (numEdges == 0);
		
		for (int j = 0; j < numEdges; j++) {
			Node destNode;
			do {
				destIndex = rand() % graph->getNumVertex();
				destNode = graph->getVertexSet().at(destIndex)->getInfo();
			} while (startNode == destNode || startNode.findEdge(destNode) != NULL);
			
			graph->addEdge(startNode, destNode, startNode.calcDist(destNode));
		}
	}
}

void Project::generateRandomTraffic() {
	int numVehicles, startIndex, destIndex;

	if (traffic->empty()) {
		do {
			numVehicles = rand() % 10;
		} while (numVehicles == 0);

		for (int i = 0; i < numVehicles; i++) {
			startIndex = rand() % graph->getNumVertex();
			do {
				destIndex = rand() % graph->getNumVertex();
			} while (startIndex == destIndex);

			Node startNode = graph->findVertexByIndex(startIndex)->getInfo();
			Node destNode = graph->findVertexByIndex(destIndex)->getInfo();

			traffic->push(new Vehicle(startNode, destNode));
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

		traffic->push(new Vehicle(startNode, destNode));
	}
}

void Project::resetGraph() {
	if (graph != NULL) {
		graph->findVertexByIndex(0)->getInfo().resetNodeId();
		graph->findEdgeById(0)->resetEdgeId();

		delete graph;
		graph = new Graph<Node>();
	}
}

void Project::resetTraffic() {
	if (!traffic->empty()) {
		traffic->back()->resetVehicleId();
		delete traffic;
		traffic = new queue<Vehicle*>();
	}
}

void Project::openWindowGv() {
	gv->createWindow(600, 600);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");
	//gv->defineEdgeCurved(false);
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

void Project::cleanGv() {
	for (Vertex<Node>* node : graph->getVertexSet()) {
		gv->setVertexColor(node->getInfo().getId(), BLUE);
		for (Edge<Node>* edge : node->getAdj()) {
			gv->setEdgeColor(edge->getId(), BLACK);
			gv->setEdgeThickness(edge->getId(), 1);
		}
	}
}

void Project::resetGv() {
	if (gv != NULL) {
		gv->closeWindow();
		delete gv;
		gv = new GraphViewer(GRAPH_WIDTH, GRAPH_HEIGHT, false);
	}
}

void Project::testDijkstra() {

	char answer;
	int idStart, idDest;
	bool validIndex;

	cleanGv();

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

void Project::reportAccident() {

	int id;
	Edge<Node>* e = NULL;

	cout << ". To leave insert 0!" << endl;
	do {
		cout << "-> Insert occurrence's location (edge id): ";
		cin >> id;
		cin.ignore();

		e = graph->findEdgeById(id);
		if (id != 0) {
			if (e == NULL)
				cout << ". Edge inserted does not exist!\n";
			else
				if (graph->removeEdge(e)) {
					gv->setEdgeThickness(e->getId(), 3);
					gv->setEdgeColor(e->getId(), RED);
					printGv();
				}
				else cout << ". Could not remove edge!\n";
		}
	} while (id != 0);

	cout << endl;
}

void Project::printTraffic() {
	if (!traffic->empty()) {
		queue<Vehicle*> aux(*traffic);
		while (!aux.empty()) {
			cout << *aux.front() << endl;
			aux.pop();
		}
	}
	else cout << ". Currently there's no traffic!\n\n";
}

void Project::divertTraffic() {
	int numVehicles = traffic->size();
	double totalDijkstraTime = 0;
	Vehicle* v = NULL;

	if (!traffic->empty()) {
		cout << ". Processing traffic ..." << endl;

		while (!traffic->empty()) {

			v = traffic->front();
			traffic->pop();

			auto start = chrono::high_resolution_clock::now();
			graph->dijkstraShortestPath(v->getStartNode());
			auto finish = chrono::high_resolution_clock::now();
			totalDijkstraTime += chrono::duration_cast<chrono::microseconds>(finish - start).count();

			vector<Edge<Node>*> path = getDijkstraPath(v->getDestNode());
			cout << ". Path for vehicle " << v->getId() << ": ";
			printPath(path);
			Sleep(2000);

			cleanGv();
			updateGv();
			graph->randomizeNumVehicles();
		}

		cout << ". Dijkstra processing average time (micro-seconds) = "
			<< (totalDijkstraTime / (graph->getNumVertex())) << endl;
	}
	else cout << ". No traffic to be processed!\n";
	cout << endl;
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