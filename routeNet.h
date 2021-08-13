#pragma once
#include <vector>
#include <list>
#include <unordered_map>
#include <algorithm>
#include <random>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <Windows.h>

#define AdjacentNum 6
#define ProxyNodeNum 100
#define MapSize 80
#define MinDist 5

typedef struct {
	int x;
	int y;
}position;

class proxyNode {
private:
	int nodeId;
	int generateRandom() {
		return rand();
	}
public:
	position nodePosition;//const reference, read only
	const position& getPosition()const {
		return nodePosition;
	}

	std::unordered_map<proxyNode*, int> adjacentNodes;//privode methods

	proxyNode(int id);
	int getDistance(proxyNode* peer);
	bool isNewNodeLegal(std::vector<proxyNode*> proxyNodes);
	int getNodeId();
};

typedef struct {
	int distance;
	std::list<proxyNode*> routeTrace;
	int distanceBeforeRoute;
	proxyNode* start;
	proxyNode* end;
}routeInfo;

class routeNetMatrix {
private:
	int readCount;
	std::vector<proxyNode*> proxyNodes;
	std::vector<std::vector<routeInfo>> routeTable;
public:
	routeNetMatrix();
	void displayRouteTable();
	void displayRouteGraph();
	void flodyRouterAlgorithm();
	std::list<proxyNode*> getAndDisplayBestRoutePath(int start, int end);

};

