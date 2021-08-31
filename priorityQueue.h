#ifndef MST
#define MST

#include<iostream>
#include<vector>
#include<array>
#include<tuple>

using namespace std;

#endif


	// class to represent edges in spanning tree
class nodeEdge
{
	public:
		int node;
		array<int, 2> edge;
		int cost; // edge cost
		
		nodeEdge(int N = 0, array<int, 2> A = array<int, 2>{0, 0}, int C = 0):
												node(N), edge(A), cost(C) {}
};

class priorityQueue
{
	vector<nodeEdge> pqArray;
	int size;
	
		// make subtree with root at given index priority queue compliant
	void heapify(int);
	
		// get parent node index of node at index i
	int parent(int i) { return (i-1)/2; }
	
		// get index of left child of node at index i
    int left(int i) { return (2*i + 1); }
  
    	// get index of right child of node at index i
    int right(int i) { return (2*i + 2); }
	
	public:
		priorityQueue(int S = 0) { size = S; pqArray = vector<nodeEdge>(size); }
	
			// removes the top element of the queue
		nodeEdge getMin(); 

			// checks to see if the priority queue contains node <n> 
			// if so return the index, if not return -1
		int contains(int EC);
		
			// insert queue element "OE" into queue
		void insert(nodeEdge QE);
		
			// Decreases value of key at index 'i' to new_val
		void decreaseKey(int i, int new_val);
		
			// returns the top element of the queue.
		nodeEdge top() { return pqArray[0]; }
		
			// returns the number of queue elements
		int getSize() { return size; } 
		
		vector<nodeEdge> getQueContents();
		
		bool isEmpty() { return size == 0 ? true: false; }
		
		bool notEmpty() { return size > 0 ? true: false; }
		
			// emtpy out the Priority Queue
		void emptyPQ()
		{
			pqArray.clear();
			size = 0;
		}
		
			// modify a value in the Priority Queue
		void modVal(int idx, nodeEdge n) { pqArray[idx] = n; }
};
