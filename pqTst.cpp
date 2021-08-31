#include<iostream>
#include<vector>
#include<queue>
#include<array>
#include <functional>


using namespace std;

class nodeEdge
{
	public:
		int node;
		array<int, 2> edge;
		int cost; // edge cost
		
		nodeEdge(int N = 0, array<int, 2> A = array<int, 2>{0, 0}, int C = 0):
												node(N), edge(A), cost(C) {}
};

bool cmpCost(nodeEdge n1, nodeEdge n2) { return n1.cost > n2.cost; }


int main(int argc, char** argv)
{
	priority_queue<nodeEdge, vector<nodeEdge>, greater<int> > PQ;
	
	return 0;
}
