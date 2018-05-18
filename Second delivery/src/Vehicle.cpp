#include "Vehicle.h"

using namespace std;

int Vehicle::vehicleId = 1;

Vehicle::Vehicle(Node s, Node d) : id(vehicleId++) {
	this->startNode = s;
	this->destNode = d;
}

int Vehicle::getId() const {
	return id;
}

Node Vehicle::getStartNode() const {
	return startNode;
}

Node Vehicle::getDestNode() const {
	return destNode;
}

void Vehicle::resetVehicleId() {
	vehicleId = 1;
}

ostream& operator<<(ostream &out, const Vehicle v) {

	out << ".Vehicle " << v.id << ": " << endl
		<< "Starting node: " << v.startNode.getId() << endl
		<< "Destiny node: " << v.destNode.getId() << endl;
	
	return out;
}
