#pragma once

#include "Node.h"

class Vehicle {

private:
	static int vehicleId;
	int id;
	Node startNode;
	Node destNode;

public:
	Vehicle(Node s, Node d);
	int getId();
	Node getStartNode();
	Node getDestNode();
};