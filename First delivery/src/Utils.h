#pragma once

#include <vector>
#include <sstream>
#include <random>
#include <time.h>
#include <chrono>
#include "Project.h"

void graphSelectionMenu(Project * proj);
int graphSelectionOptions();
void mainMenu(Project* proj);
int mainMenuOptions();
void pathsMenu(Project* proj);
int pathsOptions();
void trafficMenu(Project* proj);
int trafficOptions();
int processInput(int inf, int sup);