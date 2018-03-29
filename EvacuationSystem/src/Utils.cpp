#include "Utils.h"

Project* initProj() {

	Project *proj = new Project();

	proj->openWindowGV();
	proj->readNodesFile();
	proj->readEdgesFile();
	proj->printGV();

	return proj;
}

void menu(Project* proj) {
	menuDijkstra(proj);
}

void menuDijkstra(Project* proj) {

	char answer;
	int idStart, idDest;

	cout << "DIJKSTRA SHORTEST PATHS\n";

	cout << "Insert vertex of start (out of " <<
		proj->getGraph()->getNumVertex() << "): ";
	cin >> idStart;
	cin.ignore();

	/* gets starting node */
	Node start = proj->getNodeById(idStart);

	/* calculates all paths from starting node */
	proj->getGraph()->dijkstraShortestPath(start);

	do {
		cout << "Print all paths ? (Y/N) ";
		cin >> answer;
		answer = toupper(answer);
		cin.ignore();
	} while (answer != 'Y' && answer != 'N');
	
	if (answer == 'N') {
		cout << "Insert vertex of destination (out of " <<
			proj->getGraph()->getNumVertex() << "): ";
		cin >> idDest;
		cin.ignore();

		/* gets destination node */
		Node dest = proj->getNodeById(idDest);

		vector<Node> path = proj->getDijkstraPath(dest);
		printPath(path);
	}
	else {
		cout << "Paths from Vertex " << start.getId() << ":\n";
		printAllPaths(proj);
	}
}

void printPath(vector<Node> path) {
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

void printAllPaths(Project* proj) {
	for (Vertex<Node>* vertex : proj->getGraph()->getVertexSet()) {
		vector<Node> path = proj->getDijkstraPath(vertex->getInfo());
		if (path.size() != 1) {
			cout << "to Vertex " << vertex->getInfo().getId() << ": ";
			printPath(path);
		}
	}
}