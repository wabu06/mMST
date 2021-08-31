#include "priorityQueue.h"

void PQswap(nodeEdge& x, nodeEdge& y)
{
    nodeEdge temp = x;
    x = y;
    y = temp;
}

	// make subtree with root at given index priority queue compliant
void priorityQueue::heapify(int i)
{
	int l = left(i);
	int r = right(i);
	int smallest = i;
	
	if (l < size && pqArray[l].cost < pqArray[i].cost)
    	smallest = l;

	if (r < size && pqArray[r].cost < pqArray[smallest].cost)
    	smallest = r;

	if (smallest != i)
	{
    	PQswap(pqArray[i], pqArray[smallest]);
    	heapify(smallest);
	}
}

	// removes the top element of the queue
nodeEdge priorityQueue::getMin()
{
	if (size <= 0)
    	return nodeEdge(-1, array<int, 2>{-1, -1}, -1);

	nodeEdge root;

	if (size == 1)
	{
    	size--;
		
		root = pqArray[0];
		pqArray.pop_back();
		
    	return root;
	}
	
	root = pqArray[0];
	
	pqArray[0] = pqArray[size-1];
	
	size--;
	
	heapify(0);
	
	pqArray.pop_back();
	
	return root;
}

	// checks to see if the priority queue contains node <n> 
	// if so return the index, if not return -1
int priorityQueue::contains(int n)
{
	for(int i = 0; i < size; i++)
	{
		if (pqArray[i].node == n)
			return i;
	}
	
	return -1;
}

	// insert queue element "OE" into queue
void priorityQueue::insert(nodeEdge QE)
{
	size++;
	int i = size - 1;
	
	pqArray.push_back(QE);
	
		// make priority queue compliant
    while (i != 0 && pqArray[parent(i)].cost > pqArray[i].cost)
    {
       PQswap(pqArray[i], pqArray[parent(i)]);
       i = parent(i);
    }
}

	// Decreases value of key at index 'i' to new_val
void priorityQueue::decreaseKey(int i, int new_val)
{
	pqArray[i].cost = new_val;
	
		// make priority queue compliant
	while (i != 0 && pqArray[parent(i)].cost > pqArray[i].cost)
	{
	swap(pqArray[i], pqArray[parent(i)]);
	i = parent(i);
	}
}

vector<nodeEdge> priorityQueue::getQueContents()
{
	vector<nodeEdge> elements;
	
	for(auto& E: pqArray)
		elements.push_back(E);
	
	return elements;
}
