#include "graph.h"
#include "minHeapPriorityQ.h"
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	graph world;

	////////////////////////////////TEST///////////////////////
	//world.addVertex(5);
	//world.addEdge(0, 4, 3);
	//world.addEdge(1, 0, 4);
	//world.addEdge(4, 3, 4);
	//world.addEdge(3, 2, 5);
	//world.addEdge(4, 1, 7);
	//world.addEdge(1, 2, 1);

	////world.testDisplay();
	////cout << endl;
	//world.shortestPath(0, 2);
	//cout << endl;
	////world.testDisplay();

	//cout << endl;
	//world.shortestPath(4, 2);
	//cout << endl<<endl;
	//world.shortestPath(2, 1);

	/////////////////////////////////READ FILE//////////////////
	fstream myFile;
	myFile.open("nycsmall.txt");

	while (!myFile.eof())
	{
		int numVertex;
		int numEdges;
		int start;
		int end;
		int weight;

		myFile >> numVertex;//Read number of Vertex
		myFile >> numEdges;//Read number of edges

		world.addVertex(numVertex);

		for (int i = 0; i < numEdges; ++i)
		{
			myFile >> start;
			myFile >> end;
			myFile >> weight;
			world.addEdge(start, end, weight);
		}
	}
	cout << endl;


	//world.testDisplay();

	int startT = clock();
	//world.shortestPath(42615, 264340);
	world.shortestPath(0, 3);
	

	int stopT = clock();
	cout << endl << "Time: " << (stopT - startT) / double(CLOCKS_PER_SEC) * 1000 << endl;
	cout << endl<<endl;
	return 0;
}