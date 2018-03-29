#pragma once

#include "Node.h"

Point::Point() {
	coords.first = -1;
	coords.second = -1;
}

Point::Point(int x, int y) {
	coords.first = x;
	coords.second = y;
}

int Point::getX() {
	return coords.first;
}

int Point::getY() {
	return coords.second;
}

void Point::setX(int x) {
	coords.first = x;
}

void Point::setY(int y) {
	coords.second = y;
}

bool Point::operator==(const Point & point)
{
	return coords.first == point.coords.first &&
		coords.second == point.coords.second;
}

Node::Node() {
	this->id = -1;
	this->coords = Point();
}

Node::Node(int id, int x, int y) {
	this->id = id;
	this->coords = Point(x,y);
}

int Node::getId() {
	return id;
}

Point Node::getCoords() {
	return coords;
}

std::vector<Edge<int>>Node::getAdj() {
	return adj;
}

void Node::setId(int id) {
	this->id = id;
}

void Node::setCoords(Point coords) {
	this->coords = coords;
}

void Node::setAdj(std::vector<Edge<int>> adj) {
	this->adj = adj;
}

bool Node::operator==(const Node &node)
{
	for (auto edge : adj)
		for (auto edgeAux : node.adj)
			if (!(edge == edgeAux))
				return false;

	return id == node.id && coords == node.coords;
}
