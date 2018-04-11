#pragma once

#include "Node.h"

Point::Point() {
	coords.first = 0;
	coords.second = 0;
}

Point::Point(int x, int y) {
	coords.first = x;
	coords.second = y;
}

int Point::getX() const {
	return coords.first;
}

int Point::getY() const {
	return coords.second;
}

void Point::setX(int x) {
	coords.first = x;
}

void Point::setY(int y) {
	coords.second = y;
}

bool Point::operator==(const Point & point) {
	return coords.first == point.coords.first &&
		coords.second == point.coords.second;
}


int Node::nodeId = 1;

Node::Node() : id(nodeId++) {
	this->coords = Point();
}

Node::Node(int x, int y) : id(nodeId++) {
	this->coords = Point(x,y);
}

int Node::getId() const {
	return id;
}

Point Node::getCoords() const {
	return coords;
}

std::vector<Edge<Node>*>Node::getAdj() const {
	return adj;
}

void Node::setId(int id) {
	this->id = id;
}

void Node::setCoords(Point coords) {
	this->coords = coords;
}

void Node::setAdj(std::vector<Edge<Node>*> adj) {
	this->adj = adj;
}

double Node::calcDist(Node n) {
	return sqrt(pow(coords.getX() - n.coords.getX(), 2)
		+ pow(coords.getY() - n.coords.getY(), 2));
}

Edge<Node>* Node::findEdge(Node n) {
	for (auto edge : adj)
		if (edge->getDest()->getInfo() == n)
			return edge;
	return NULL;
}

void Node::resetNodeId() {
	nodeId = 1;
}

bool Node::operator==(const Node &node) {
	for (auto edge : adj)
		for (auto edgeAux : node.adj)
			if (!(edge == edgeAux))
				return false;
	
	return id == node.id && coords == node.coords;
}
