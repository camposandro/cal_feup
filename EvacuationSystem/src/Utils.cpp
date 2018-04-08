#include "Utils.h"

Project* initProj() {

	cout << "EvacuationSystem - CAL 1718\n";
	cout << ". Loading graph files ...";

	Project *proj = new Project();
	proj->readNodesFile();
	proj->readEdgesFile();
	proj->readTrafficFile();
	
	proj->openWindowGv();
	proj->loadNodesGv();
	proj->loadEdgesGv();
	proj->printGv();

	#ifdef _WIN32
		system("cls");
	#endif

	return proj;
}

void mainMenu(Project* proj) {

	while (int option = optionsMenu()) {
		switch (option) {
		case 0:
			return;
		case 1:
			menuPaths(proj);
			break;
		case 2:
			proj->reportAccident();
			break;
		default:
			break;
		}
	}
}

int optionsMenu() {

	cout << "EvacuationSystem - main menu:\n";
	vector<string> menuOptions = {
		"-> 1. Calculate shortest paths",
		"-> 2. Report accident",
		"-> 0. Leave",
	};

	for (string option : menuOptions)
		cout << option << endl;
	
	int option = processInput(0,2);
	cout << endl;

	return option;
}

void menuPaths(Project* proj) {

	while (int option = pathsOptions()) {
		switch (option) {
		case 0:
			return;
		case 1:
			proj->testDijkstra();
			break;
		case 2:
			proj->testAstar();
			break;
		default:
			break;
		}
	}
}

int pathsOptions() {

	cout << "EvacuationSystem - path searching:\n";
	vector<string> pathsOptions = {
		"-> 1. Dijkstra Algorithm",
		"-> 2. A* Search Algorithm",
		"-> 0. Return",
	};

	for (string option : pathsOptions)
		cout << option << endl;

	int option = processInput(0, 2);
	cout << endl;

	return option;
}

int processInput(int inf, int sup) {

	int option;
	bool validOption;
	do {
		validOption = false;
		cout << "Option: ";
		cin >> option;
		cin.ignore();
		if (option >= inf && option <= sup)
			validOption = true;
	} while (!validOption);

	return option;
}

//void Project::test_performance_dijkstra() {
//	cout << "Dijkstra processing graph ..." << endl;
//
//	auto start = std::chrono::high_resolution_clock::now();
//	for (Vertex<Node> *vertex : graph->getVertexSet())
//		graph->dijkstraShortestPath(vertex->getInfo());
//	auto finish = std::chrono::high_resolution_clock::now();
//
//	auto elapsed = std::chrono::duration_cast<chrono::microseconds>(finish - start).count();
//	cout << "Dijkstra processing average time (micro-seconds) = "
//		<< (elapsed / (GRAPH_WIDTH * GRAPH_HEIGHT)) << endl;
//}