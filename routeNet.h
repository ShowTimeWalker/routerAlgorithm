#pragma once
#include <vector>

#define NODE_NUM_MAX 100	//随机生成的节点最大个数
#define NODE_NUM_MIN 40		//随机生成的节点最少个数
#define UNDULATION 10		//波动稀疏，节点之间有效线路数量的波动
#define SPRASE_FACTOR 0.2	//稀疏因子，代表每个节点联通数量占比总节点的个数的比例
#define REGION_NUM 4

class routeNetMatrix {
private:
	int nodeNum;
	std::vector<int> peerNums;
	std::vector<std::vector<int>> mat;
public:
	routeNetMatrix();
};

class routeNetLink {

};
