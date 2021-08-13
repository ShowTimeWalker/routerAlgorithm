#include <iostream>
#include "main.h"

using namespace std;

int main() {
	routeNetMatrix* RouteNet = new routeNetMatrix();
	int start, end;
	cin >> start >> end;
	list<proxyNode*> bestRouteTrace = RouteNet->getAndDisplayBestRoutePath(start, end);
	return 0;
}