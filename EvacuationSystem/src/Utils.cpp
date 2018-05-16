#include "Utils.h"

void graphSelectionMenu(Project * proj) {

	chrono::high_resolution_clock::time_point start, finish;
	_int64 elapsed;

	while (int option = graphSelectionOptions()) {
		switch (option) {

		case 1:
			cout << ". Loading files ...\n";
			start = chrono::high_resolution_clock::now();
			proj->readNodesFile();
			proj->readEdgesFile();
			proj->readTrafficFile();
			finish = chrono::high_resolution_clock::now();

			elapsed = chrono::duration_cast<chrono::microseconds>(finish - start).count();
			cout << ". Files reading time (micro-seconds) = " << elapsed << endl << endl;
			
			Sleep(3000);
			break;

		case 2:
			start = chrono::high_resolution_clock::now();
			proj->generateRandomGraph();
			finish = chrono::high_resolution_clock::now();
			elapsed = chrono::duration_cast<chrono::microseconds>(finish - start).count();
			cout << ". Random graph created in (micro-seconds) = " << elapsed << endl;

			start = chrono::high_resolution_clock::now();
			proj->generateRandomTraffic();
			finish = chrono::high_resolution_clock::now();
			elapsed = chrono::duration_cast<chrono::microseconds>(finish - start).count();
			cout << ". Random traffic created in (micro-seconds) = " << elapsed << endl << endl;

			Sleep(3000);
			break;
		}
		
		#ifdef _WIN32
			system("cls");
		#endif

		proj->openWindowGv();
		proj->loadNodesGv();
		proj->loadEdgesGv();
		proj->printGv();
		mainMenu(proj);
	}
}

int graphSelectionOptions() {

	#ifdef _WIN32
		system("cls");
	#endif

	cout << "EvacuationSystem - CAL 1718\n";
	vector<string> graphOptions = {
		"-> 1. Load graph from files",
		"-> 2. Generate random graph",
		"-> 0. Leave",
	};

	for (string option : graphOptions)
		cout << option << endl;

	int option = processInput(0, 2);
	cout << endl;

	return option;
}

void mainMenu(Project* proj) {
	int option;
	while ((option = mainMenuOptions()) >= 0) {
		switch (option) {
		case 0:
			proj->resetGraph();
			proj->resetTraffic();
			proj->resetGv();
			return;
		case 1:
			pathsMenu(proj);
			break;
		case 2:
			trafficMenu(proj);
			break;
		case 3:
			proj->printTraffic();
			break;
		case 4:
			proj->reportAccident();
			break;
		default:
			break;
		}
	}
}

int mainMenuOptions() {

	cout << "EvacuationSystem - main menu:\n";
	vector<string> menuOptions = {
		"-> 1. Calculate shortest routes",
		"-> 2. Divert current traffic",
		"-> 3. Watch current traffic",
		"-> 4. Report accidents",
		"-> 0. Leave",
	};
	
	for (string option : menuOptions)
		cout << option << endl;
	
	int option = processInput(0,4);
	cout << endl;

	return option;
}

void pathsMenu(Project* proj) {

	while (int option = pathsOptions()) {
		switch (option) {
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
		"-> 1. Dijkstra algorithm",
		"-> 2. A* search algortihm",
		"-> 0. Return",
	};

	for (string option : pathsOptions)
		cout << option << endl;

	int option = processInput(0, 2);
	cout << endl;

	return option;
}

void trafficMenu(Project* proj) {

	while (int option = trafficOptions()) {
		switch (option) {
		case 1:
			proj->divertTraffic("DIJKSTRA");
			break;
		case 2:
			proj->divertTraffic("ASTAR");
			break;
		default:
			break;
		}
	}
}

int trafficOptions() {

	cout << "EvacuationSystem - path searching:\n";
	vector<string> pathsOptions = {
		"-> 1. Dijkstra algorithm",
		"-> 2. A* search algortihm",
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

/* Knuth-Morris-Pratt Algorithm */


void cpf(string p, int pi[]) {
	int m = p.length();
	pi[0] = 0;
	int k = 0;
	for(int q = 1; q<m; q++){
		while(k>0 && p[k]!=p[q]){
			k = pi[k];
		}
		if(p[k]==p[q]){
			k++;
		}
		pi[q] = k;
	}
	return;
}

int kmpMatcher(string text, string pattern) {
	int count = 0;
	int n = text.length();
	int m = pattern.length();
	int pi[text.length()];
	cpf(pattern, pi);
	int q = 0;
	for(int i = 0; i < n; i++){
		while(q>0 && pattern[q] != text[i]){
			q = pi[q-1];
		}
		if(pattern[q] == text[i]){
			q++;
		}
		if(q==m){
			q = pi[q-1];
			count++;
		}
	}
	return count;
}





