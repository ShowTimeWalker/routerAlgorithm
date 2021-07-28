#pragma once
#include <vector>
#include <unordered_map>
#include <random>
#include <ctime>
#include <algorithm>

#define AdjacentNum 2
#define ProxyNodeNum 6
#define FixedDelay 1
#define MapSize 1000

typedef struct {
	int x;
	int y;
}position;

class proxyNode {
private:
	position nodePosition;
	int generateRandom() {
		return rand();
	}
public:
	std::unordered_map<proxyNode*, int> adjacentNodes;
	proxyNode();
	int getDistance(proxyNode* peer);
};

typedef struct {
	proxyNode* start;
	proxyNode* end;
	std::vector<int> routeTrace;
	int distance;
	int distanceBeforeRoute;
}routeInfo;

class routeNetMatrix {
private:
	std::vector<proxyNode*> proxyNodes;
	std::vector<std::vector<routeInfo>> routeTable;
public:
	routeNetMatrix();
	void flodyRouterAlgorithm();
};

