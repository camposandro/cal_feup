#pragma once

#include <vector>
#include <sstream>
#include <random>
#include <time.h>
#include <chrono>
#include "Project.h"

// Graph Utils
void graphSelectionMenu(Project * proj);
int graphSelectionOptions();
void mainMenu(Project* proj);
int mainMenuOptions();
void pathsMenu(Project* proj);
int pathsOptions();
void dijkstraMenu(Project *proj);
void aStarMenu(Project *proj);
int searchOptions();
void trafficMenu(Project* proj);
int trafficOptions();
int processInput(int inf, int sup);

// String matching utils
void cpf(string p, int pi[]);
int kmpMatcher(string text, string pattern);
int editDistance(string pattern, string text);
int aproxMatcher(string pattern, string text);
Edge<Node>* selectRoad(vector<Edge<Node>*> roads);
vector<Edge<Node>*> getSimRoads(vector<Edge<Node>*> edges, string road);