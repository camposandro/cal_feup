#pragma once

#include <vector>
#include "Graph.h"

class Point {

private:
	std::pair<int, int> coords;

public:
	Point();
	Point(int x, int y);
	int getX();
	int getY();
	void setX(int x);
	void setY(int y);
	bool operator== (const Point &point);
};


class Node {
	
private:
	static int nodeId;
	int id;
	Point coords;
	std::vector<Edge<Node>*> adj;

public:
	Node();
	Node(int x, int y);
	int getId();
	Point getCoords();
	std::vector<Edge<Node>*> getAdj();
	void setId(int id);
	void setCoords(Point coords);
	void setAdj(std::vector<Edge<Node>*> adj);
	double calcDist(Node n);
	Edge<Node>* findEdge(Node n);
	bool operator== (const Node &node);
};