#include <iostream>

#include "graph.h"
#include "graphviewer.h"
#include "project.h"

/* Functions prototypes */
Project* initProj();

int main() {

	Project* proj = initProj();
	Sleep(3000);

	return 0;
}

Project* initProj() {

	Project *proj = new Project();

	proj->openWindowGV();
	proj->readNodesFile();
	proj->readEdgesFile();
	proj->printGV();
	
	return proj;
}
