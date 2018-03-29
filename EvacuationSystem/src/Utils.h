#pragma once

#include <vector>
#include <sstream>

#include "Project.h"

Project* initProj();
void menu(Project* proj);
void menuDijkstra(Project* proj);
void printAllPaths(Project* proj);
void printPath(std::vector<Node> path);
