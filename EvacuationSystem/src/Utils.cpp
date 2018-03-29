#include "Utils.h"

Project* initProj() {

	cout << "EvacuationSystem - CAL 1718\n";
	cout << ". Loading graph files ...";

	Project *proj = new Project();
	proj->readNodesFile();
	proj->readEdgesFile();	
	
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
			proj->openWindowGV();
			proj->loadNodesGV();
			proj->loadEdgesGV();
			proj->printGV();
			break;
		case 2:
			break;
		case 3:
			menuPaths(proj);
			break;
		default:
			break;
		}
	}
}

int optionsMenu() {

	cout << "EvacuationSystem - main menu:\n";
	vector<string> menuOptions = {
		"-> 1. Open GraphViewer",
		"-> 2. Report accident",
		"-> 3. Calculate paths",
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
			proj->computeDijkstra();
			break;
		case 2:
			proj->computeAstar();
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