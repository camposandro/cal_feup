#include "Edge.h"
#include "Node.h"
#include "Road.h"

int Edge::edgeId = 0;

Edge::Edge(Node *src, Node *dest, double weight) {
	this->id = ++edgeId;
	this->src = src;
	this->dest = dest;
	this->weight = weight;
}

int Edge::getId() {
	return id;
}

Node * Edge::getSrc() {
	return src;
}

Node* Edge::getDest() {
	return dest;
}

double Edge::getWeight() {
	return weight;
}

Road * Edge::getRoad() {
	return road;
}
