#include "routeNet.h"

proxyNode::proxyNode() {
	nodePosition.x = generateRandom() % MapSize;
	nodePosition.y = generateRandom() % MapSize;
	return;
}

int proxyNode::getDistance(proxyNode* peer) {
	return sqrt((peer->nodePosition.x - this->nodePosition.x) *
		(peer->nodePosition.x - this->nodePosition.x) +
		(peer->nodePosition.y - this->nodePosition.y) *
		(peer->nodePosition.y - this->nodePosition.y)
	);
}

routeNetMatrix::routeNetMatrix() {
	srand(time(0));

	// intializa proxy nodes (set best 3 peers as adjacent nodes)
	for (int i = 0; i < ProxyNodeNum; i++) {
		proxyNodes.push_back(new proxyNode());
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
		}
	}

	return;
}

void routeNetMatrix::flodyRouterAlgorithm() {
	
}