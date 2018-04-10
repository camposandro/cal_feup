#include "Utils.h"

Project* initProj() {

	cout << "EvacuationSystem - CAL 1718\n";
	Project *proj = new Project();
	graphSelectionMenu(proj);

	proj->openWindowGv();
	proj->loadNodesGv();
	proj->loadEdgesGv();
	proj->printGv();

	#ifdef _WIN32
		system("cls");
	#endif

	return proj;
}

void graphSelectionMenu(Project * proj) {

	vector<string> menuOptions = {
		"-> 1. Load graph from files",
		"-> 2. Generate random graph",
		"-> 0. Leave",
	};

	for (string option : menuOptions)
		cout << option << endl;

	int option = processInput(0, 2);
	cout << endl;

	switch (option) {

	case 1:
	{
		cout << ". Loading graph files ...\n";
		auto start = chrono::high_resolution_clock::now();
		proj->readNodesFile();
		proj->readEdgesFile();
		proj->readTrafficFile();
		auto finish = chrono::high_resolution_clock::now();

		auto elapsed = chrono::duration_cast<chrono::microseconds>(finish - start).count();
		cout << ". Files reading time (micro-seconds) = " << elapsed << endl;

		Sleep(3000);
		break;
	}
	case 2:
		proj->generateRandomGraph();
		proj->generateRandomTraffic();
		break;
	}
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
			proj->divertTraffic();
			break;
		case 3:
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
		"-> 1. Calculate shortest routes",
		"-> 2. Divert current traffic",
		"-> 3. Report accidents",
		"-> 0. Leave",
	};

	for (string option : menuOptions)
		cout << option << endl;
	
	int option = processInput(0,3);
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
		cout << ". Option: ";
		cin >> option;
		cin.ignore();
		if (option >= inf && option <= sup)
			validOption = true;
	} while (!validOption);

	return option;
}