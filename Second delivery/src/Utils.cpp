#include "Utils.h"

struct cmpSimRoads {
	bool operator()(pair<int, Edge<Node>*> p1, pair<int, Edge<Node>*> p2) const {
		return p1.first > p2.first;
	}
};

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

		proj->randomizeRoadNames();
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
			dijkstraMenu(proj);
			break;
		case 2:
			aStarMenu(proj);
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

void dijkstraMenu(Project *proj) {

	while (int option = searchOptions()) {
		switch (option) {
		case 1:
			proj->dijkstra("ID");
			break;
		case 2:
			proj->dijkstra("NAME");
			break;
		default:
			break;
		}
	}
}

void aStarMenu(Project *proj) {

	while (int option = searchOptions()) {
		switch (option) {
		case 1:
			proj->aStar("ID");
			break;
		case 2:
			proj->aStar("NAME");
			break;
		default:
			break;
		}
	}
}

int searchOptions() {

	cout << "EvacuationSystem - type of search:\n";
	vector<string> searchOptions = {
		"-> 1. Search by node id",
		"-> 2. Search by road name",
		"-> 0. Return",
	};

	for (string option : searchOptions)
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

void cpf(string p, int pi[]) {
	int m = p.length();
	pi[0] = 0;

	int k = 0;
	for (int q = 1; q < m; q++) {
		while (k > 0 && p[k] != p[q])
			k = pi[k];

		if (p[k] == p[q])
			k++;

		pi[q] = k;
	}
}

int kmpMatcher(string text, string pattern) {
	int count = 0;
	int n = text.length();
	int m = pattern.length();
	int *pi = new int[n];

	cpf(pattern, pi);

	int q = 0;
	for (int i = 0; i < n; i++) {
		while (q > 0 && pattern[q] != text[i]) {
			q = pi[q - 1];
		}
			
		if (pattern[q] == text[i])
			q++;
		
		if (q == m) {
			q = pi[q - 1];
			count++;
		}
	}

	delete [] pi;

	return count;
}

vector<string> processString(string str) {
	vector<string> words;

	string word;
	istringstream ss(str);
	while (ss >> word)
		words.push_back(word);

	return words;
}

int aproxMatcher(string pattern, string text) {
	int totEditDist = 0, currEditDist, currTotDist = 0;
	vector<string> patternStr, textStr;

	patternStr = processString(pattern);
	textStr = processString(text);

	int ptrnSize = patternStr.size();
	int textSize = textStr.size();
	int diffSize = abs(ptrnSize - textSize);

	if (diffSize > 0) totEditDist += diffSize;

	vector<string>::iterator itPtrn, itText;
	for (itPtrn = patternStr.begin(); itPtrn != patternStr.end(); itPtrn++) {
		for (itText = textStr.begin(); itText != textStr.end(); itText++) {
			currEditDist = editDistance(*itPtrn, *itText);
			if (currEditDist == 0) {
				currTotDist /= 2;
				break;
			}
			currTotDist += currEditDist;
		}
		totEditDist += currTotDist;
	}

	return totEditDist;
}

int editDistance(string pattern, string text) {
	int P = pattern.length();
	int T = text.length();
	int min1 = 0;
	vector<int> D(T + 1);
	int old_d, new_d;

	for (int j = 0; j <= T; j++) {
		D[j] = j;
	}

	for (int i = 1; i <= P; i++) {
		old_d = D[0];
		D[0] = i;
		for (int j = 1; j <= T; j++) {
			if (pattern[i - 1] == text[j - 1])
				new_d = old_d;
			else {
				new_d = 1 + min(min(old_d, D[j]), D[j - 1]);
			}

			old_d = D[j];
			D[j] = new_d;
		}
	}

	return D[T];
}

vector<Edge<Node>*> getSimRoads(vector<Edge<Node>*> edges, string road) {
	vector<Edge<Node>*> roads;

	vector<pair<int, Edge<Node>*>> heap;
	for (auto it = edges.begin(); it != edges.end(); it++) {
		int value = aproxMatcher(road, (*it)->getName());
		heap.push_back(pair<int, Edge<Node>*>(value, *it));
	}
	make_heap(heap.begin(), heap.end(), cmpSimRoads());

	for (auto it = heap.begin(); it != heap.begin() + 3; it++)
		roads.push_back(it->second);

	return roads;
}

Edge<Node>* selectRoad(vector<Edge<Node>*> roads) {
	size_t opt;

	do {
		cout << "\n. Road not found. Similar roads:\n";
		for (size_t i = 0; i < roads.size(); i++)
			cout << "[" << i + 1 << "]: "
			<< roads.at(i)->getName() << endl;
		cout << "[0]: Try inserting another name\n";
	
		cout << "-> Option: ";
		cin >> opt;
		cin.ignore();

		if (opt == 0) return NULL;

	} while (opt < 1 || opt > roads.size());

	return roads.at(opt - 1);
}