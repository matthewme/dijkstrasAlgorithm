# dijkstrasAlgorithm
//NAME: Matthew Martinez
//CLASS: CSCI 3333
//INSTRCUTOR: Dr. Schweller
//DATE:4/7/16
#pragma once
#include <iostream>
#include <list>
#include <vector>
#include <ctime>
#include "minHeapPriorityQ.h"
using namespace std;

class graph
{
private:
	class edge;

	class vertex
	{
	public:
		int vertexNumber;
		//bool relaxed = false;
		int weight = 99999999;
		vertex* predecessor = NULL;
		list<edge> neighbors;

		vertex(int i)
		{
			vertexNumber = i;
		}
	};

	class edge
	{
	public: 
		vertex * start;
		vertex * end;
		int distance;

		edge(vertex* v, vertex* u, int w)
		{
			start = v;
			end = u;
			distance = w;
		}
	};

	vector<vertex*> verticeList;//Vector of type vertex
	minHeap<vertex*> pq;//Create Min Heap Priority Queue

public:

	void addVertex(int vertices)
	{
		for (int i = 0; i < vertices; ++i)
		{
			vertex* newVertex = new vertex(i);
			verticeList.push_back(newVertex);
		}
	}

	void addEdge(int from, int to, int weight)
	{
		vertex * f = verticeList[from];//The first point
		vertex * t = verticeList[to];//The second point

		edge e(f, t, weight);
		f->neighbors.push_back(e);
	}

	//list all vertices, and who each vertex is connect to
	void testDisplay()
	{
	
		//Display vertex
		for (std::vector<vertex*>::iterator itr = verticeList.begin(); itr != verticeList.end(); ++itr)
		{
			cout << "Vertex Number: " << (*itr)->vertexNumber << endl;
			cout << "    Neighbors: ";
			
			//Dislay Neighbors
			for (list<edge>::iterator itr2 = (*itr)->neighbors.begin(); itr2 != (*itr)->neighbors.end(); ++itr2)
			{
						cout <<"S: "<<(*itr2).start->vertexNumber << ", E: "<< (*itr2).end->vertexNumber<< ", D: "<< (*itr2).distance<< " | ";
			}

			//Display Predecessor
			if ((*itr)->predecessor != NULL)
			{
				cout << endl << "     P: ";
				cout << (*itr)->predecessor->vertexNumber;
			}
			cout << endl;
		}
	}

	//
	//void checkMinHeap(int i)
	//{


	//	//Set all weights to infinity
	//	for (std::vector<vertex*>::iterator itr = verticeList.begin(); itr != verticeList.end(); ++itr)
	//	{
	//		(*itr)->weight = 999999999;
	//	}
	//	
	//	//Insert all vertices into a priority queue
	//	for (std::vector<vertex*>::iterator itr = verticeList.begin(); itr != verticeList.end(); ++itr)
	//	{
	//		pq.insert(*itr);
	//	}

	//	for (std::vector<vertex*>::iterator itr = verticeList.begin(); itr != verticeList.end(); ++itr)
	//	{
	//		vertex * extract = pq.extractMin();
	//		cout << extract->weight;
	//		cout << endl;
	//	}
	//}


	//Dijkstras Algorithm. Runtime: O(|V|log(v) + |E|log(v))
	void shortestPath(int b, int e)
	{
		//Set all weights to infinity
		for (std::vector<vertex*>::iterator itr = verticeList.begin(); itr != verticeList.end(); ++itr)
		{
			(*itr)->weight = 999999999;
			(*itr)->predecessor = NULL;
		}
		

		 verticeList[b]->weight = 0;//The first point
		vertex * end = verticeList[e];//The second point

		//Insert all vertices into a priority queue
		for (std::vector<vertex*>::iterator itr = verticeList.begin(); itr != verticeList.end(); ++itr)
		{
			pq.insert(*itr);
		}

		//Find shortest path from start to all vertices
		while (!pq.empty())//O(|V|)
		{
			vertex * smallest = pq.extractMin();//Vertex with smallest weight. O(log(v))
			//cout << "SMALLEST WEIGHT: " << smallest->weight << " || " <<smallest->vertexNumber <<endl;

			//For all edges in vertex O(|E|)
			for (std::list<edge>::iterator itr = smallest->neighbors.begin(); itr != smallest->neighbors.end(); ++itr)
			{
					relax(smallest, (*itr));//O(log(v))
			}
		}

		int path;
		cout << "Shortest Path: " ;

		if (end->predecessor != NULL)
		{
			path =  end->weight;//Store Path
			cout << end->vertexNumber;

			//read end's predecessor, go to that vertex and repeat and until there is no predecessor
			while (end->predecessor != NULL)
			{
				cout << " <- " << end->predecessor->vertexNumber;
				end = end->predecessor;
			}
			cout << endl << "Path Cost: " << path;
		}
		else
			cout << "Destination Not Reachable" << endl;
	}
	
	void relax(vertex* u, edge v)
	{
		//If the weight of the vertex + the distance to the neighbor
		//is less than the neigbors weight
		if (u->weight + v.distance < v.end->weight)
		{
			//set the neighbors weight to be the start points wieght plus the distance
			v.end->weight = u->weight + v.distance;

			//Neighbors precessesor is the the vertex with shortest path
			v.end->predecessor = u;

			//Update Heap
			pq.insert(v.end);
		}
	}

};
