#include "Vehicle.h"

int Vehicle::vehicleId = 1;

Vehicle::Vehicle(Node s, Node d) : id(vehicleId++) {
	this->startNode = s;
	this->destNode = d;
}

int Vehicle::getId() {
	return id;
}

Node Vehicle::getStartNode() {
	return startNode;
}

Node Vehicle::getDestNode() {
	return destNode;
}
