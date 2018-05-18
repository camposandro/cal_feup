#pragma once

#include <iostream>
#include "Node.h"

class Vehicle {

private:
	static int vehicleId;
	int id;
	Node startNode;
	Node destNode;

public:
	Vehicle(Node s, Node d);
	int getId() const;
	Node getStartNode() const;
	Node getDestNode() const;
	void resetVehicleId();
	friend ostream& operator<<(ostream &out, const Vehicle v);
};