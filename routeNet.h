#pragma once
#include <vector>

#define NODE_NUM_MAX 100	//������ɵĽڵ�������
#define NODE_NUM_MIN 40		//������ɵĽڵ����ٸ���
#define UNDULATION 10		//����ϡ�裬�ڵ�֮����Ч��·�����Ĳ���
#define SPRASE_FACTOR 0.2	//ϡ�����ӣ�����ÿ���ڵ���ͨ����ռ���ܽڵ�ĸ����ı���
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
