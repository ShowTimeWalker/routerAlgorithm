#include <random>
#include <ctime>
#include "routeNet.h"


routeNetMatrix::routeNetMatrix() {
	srand(time(0));
	nodeNum = rand() % (NODE_NUM_MAX - NODE_NUM_MIN) + NODE_NUM_MIN;
	peerNums.resize(nodeNum);
	mat.assign(nodeNum, std::vector<int>(nodeNum));

	for (auto& n : peerNums) {
		int rand_factor = rand() % UNDULATION - UNDULATION / 2;
		n = nodeNum * SPRASE_FACTOR + rand_factor;
	}
	

}