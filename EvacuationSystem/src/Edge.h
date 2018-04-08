#pragma once

#include "Road.h"

class Edge {

private:
	static int edgeId;

	int id;
	Node* src;
	Node* dest;
	double weight;
	Road* road;

public:
	Edge(Node *src, Node *dest, double weight);
	int getId();
	Node* getSrc();
	Node* getDest();
	double getWeight();
	Road* getRoad();
	friend class Graph;
	friend class Node;
};