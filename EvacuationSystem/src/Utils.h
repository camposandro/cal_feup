#pragma once

#include <vector>
#include <sstream>
#include <random>
#include <time.h>
#include <chrono>
#include "Project.h"

Project* initProj();
void mainMenu(Project* proj);
int optionsMenu();
void menuPaths(Project* proj);
int pathsOptions();
int processInput(int inf, int sup);