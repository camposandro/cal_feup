#pragma once

#include <vector>
#include "graph.h"

/* ------------------ Point Class ------------------- */
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

/* ------------------ Node Class ------------------- */
class Node {

private:
	int id;
	Point coords;
	std::vector<Edge<int>> adj;

public:
	Node();
	Node(int id, int x, int y);
	int getId();
	Point getCoords();
	std::vector<Edge<int>> getAdj();
	void setId(int id);
	void setCoords(Point coords);
	void setAdj(std::vector<Edge<int>> adj);
	bool operator== (const Node &node);
};