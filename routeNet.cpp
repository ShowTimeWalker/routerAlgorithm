#include "routeNet.h"

proxyNode::proxyNode(int id) {
	nodePosition.x = generateRandom() % MapSize;
	nodePosition.y = generateRandom() % MapSize;
	nodeId = id;
	return;
}

int proxyNode::getDistance(proxyNode* peer) {
	return sqrt((peer->nodePosition.x - this->nodePosition.x) *
		(peer->nodePosition.x - this->nodePosition.x) +
		(peer->nodePosition.y - this->nodePosition.y) *
		(peer->nodePosition.y - this->nodePosition.y)
	);
}

bool proxyNode::isNewNodeLegal(std::vector<proxyNode*> proxyNodes) {
	for (auto peer : proxyNodes) {
		if (this->getDistance(peer) < MinDist)
			return false;
	}
	return true;
}

routeNetMatrix::routeNetMatrix() {
	srand(time(0));

	// intializa proxy nodes (set best 3 peers as adjacent nodes)
	for (int i = 0; i < ProxyNodeNum; i++) {
		proxyNode* newNode = new proxyNode(i);
		while (!newNode->isNewNodeLegal(proxyNodes)) {
			delete newNode;
			newNode = new proxyNode(i);
		}
		proxyNodes.push_back(newNode);
	}
	for (auto& node : proxyNodes) {
		std::vector<std::pair<int, proxyNode*>> peersInfo;
		for (auto& peer : proxyNodes) {
			if (node == peer)
				continue;
			peersInfo.push_back(std::make_pair(node->getDistance(peer), peer));
		}
		std::sort(peersInfo.begin(), peersInfo.end(),
			[](std::pair<int, proxyNode*>left, std::pair<int, proxyNode*> right) {return left.first < right.first; });

		for (int i = 0; i < AdjacentNum; i++) {
			node->adjacentNodes[peersInfo[i].second] = peersInfo[i].first;
			peersInfo[i].second->adjacentNodes[node] = peersInfo[i].first;
		}
	}

	// initialize route table
	routeTable.assign(ProxyNodeNum, std::vector<routeInfo>(ProxyNodeNum));
	for (int row = 0; row < ProxyNodeNum; row++) {
		for (int col = 0; col < ProxyNodeNum; col++) {
			routeTable[row][col].start = proxyNodes[row];
			routeTable[row][col].end = proxyNodes[col];
			routeTable[row][col].distance = row == col ?
				0 :(proxyNodes[row]->adjacentNodes.count(proxyNodes[col]) ?
					proxyNodes[row]->adjacentNodes[proxyNodes[col]] : -1);
			routeTable[row][col].distanceBeforeRoute = routeTable[row][col].distance;
			routeTable[row][col].routeTrace.push_front(proxyNodes[row]);
			routeTable[row][col].routeTrace.push_back(proxyNodes[col]);
		}
	}
	displayRouteGraph();
	displayRouteTable();

	flodyRouterAlgorithm();

	displayRouteTable();
	return;
	}
	
void routeNetMatrix::flodyRouterAlgorithm() {
	for (int trans = 0; trans < ProxyNodeNum; trans++) {
		for (int start = 0; start < ProxyNodeNum; start++) {
			int firstDist = routeTable[trans][start].distance;
			if (firstDist <= 0)
				continue;
			for (int end = 0; end < ProxyNodeNum; end++) {
				int secondDist = routeTable[trans][end].distance;
				if (secondDist <= 0)
					continue;
				int directDist = routeTable[start][end].distance;
				if (firstDist + secondDist < directDist || directDist == -1) {
					routeTable[start][end].distance = firstDist + secondDist;
					routeTable[start][end].routeTrace = routeTable[start][trans].routeTrace;
					routeTable[start][end].routeTrace.pop_back();
					routeTable[start][end].routeTrace.insert(
						routeTable[start][end].routeTrace.end(),
						routeTable[trans][end].routeTrace.begin(),
						routeTable[trans][end].routeTrace.end());
				}
			}
		}
	}
}

void routeNetMatrix::displayRouteTable() {
	std::cout << "st\\en\t\|\t";
	for (int i = 0; i < ProxyNodeNum; i++)
		std::cout << i << "\t";
	std::cout << std::endl;
	for (int i = 0; i < ProxyNodeNum + 2; i++)
		std::cout << "--------";
	std::cout << std::endl;
	for (int st = 0; st < ProxyNodeNum; st++) {
		std::cout << st << "\t\|\t";
		for (int en = 0; en < ProxyNodeNum; en++) {
			std::cout << std::setiosflags(std::ios::right) << routeTable[st][en].distance << '\t';
		}
		std::cout << std::endl << std::endl;
	}
	std::cout << "route table" << std::endl << std::endl << std::endl;
}

void routeNetMatrix::displayRouteGraph() {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursor;
	for (int i = 0; i < ProxyNodeNum; i++) {
		cursor.X = proxyNodes[i]->nodePosition.x * 2;
		cursor.Y = proxyNodes[i]->nodePosition.y;
		SetConsoleCursorPosition(handle, cursor);
		std::cout << i;//¡ï¡ö¡ô¡ñ
	}
	cursor.X = 0;
	cursor.Y = MapSize + 1;
	SetConsoleCursorPosition(handle, cursor);
	std::cout << "node graph" << std::endl << std::endl << std::endl;
}