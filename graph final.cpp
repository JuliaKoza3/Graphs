// Graphs.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Queue.h"
#include "Vectors.h"
#include <iostream>

using namespace std;

//function for printing number sequence
void printNumberSequence(int amountOfVertices, int sequence[])
{
	for (int i = 1; i <= amountOfVertices; i++)
	{
		printf("%d ", sequence[i]);
	}
}

//function sorting the degrees in the descending order and vertices by the highest to lowest degree
void merge(int degrees[], int vertices[], int start, int middle, int end)
{
	int sizeOfFirstHalf = middle - start + 1;
	int sizeOfSecondHalf = end - middle;

	int* leftSideDegrees = new int[sizeOfFirstHalf];
	int* rightSideDegrees = new int[sizeOfSecondHalf];
	int* leftSideVertices = new int[sizeOfFirstHalf];
	int* rightSideVertices = new int[sizeOfSecondHalf];

	//making temp arrays and filling them with data from orginal ones
	for (int i = 0; i < sizeOfFirstHalf; i++)
	{
		leftSideDegrees[i] = degrees[start + i];
		leftSideVertices[i] = vertices[start + i];
	}
	for (int j = 0; j < sizeOfSecondHalf; j++) 
	{
		rightSideDegrees[j] = degrees[middle + 1 + j];
		rightSideVertices[j] = vertices[middle + 1 + j];
	}

	int i = 0, j = 0, k = start;

	//merging back temp arrays into orginal ones in descending order
	while (i < sizeOfFirstHalf && j < sizeOfSecondHalf) 
	{
		//checking which element is bigger and putting it first
		if (leftSideDegrees[i] >= rightSideDegrees[j]) 
		{
			degrees[k] = leftSideDegrees[i];
			vertices[k] = leftSideVertices[i];
			i++;
		}
		else 
		{
			degrees[k] = rightSideDegrees[j];
			vertices[k] = rightSideVertices[j];
			j++;
		}
		k++;
	}

	//if any elements left we are puting them back to orginal ararys
	while (i < sizeOfFirstHalf) 
	{
		degrees[k] = leftSideDegrees[i];
		vertices[k] = leftSideVertices[i];
		i++;
		k++;
	}

	while (j < sizeOfSecondHalf) 
	{
		degrees[k] = rightSideDegrees[j];
		vertices[k] = rightSideVertices[j];
		j++;
		k++;
	}

	delete[] leftSideDegrees;
	delete[] rightSideDegrees;
	delete[] leftSideVertices;
	delete[] rightSideVertices;
}


//recursive function for sorting
void mergeSort(int degrees[], int vertices[], int start, int end)
{
	//checkig if array needs sorting
	if (start < end) 
	{
		int middle = start + (end - start) / 2;

		//dividing arrays into halves recursively
		mergeSort(degrees, vertices, start, middle);
		mergeSort(degrees, vertices,middle + 1, end);

		//merging the halves and sorting their elements
		merge(degrees, vertices,start, middle, end);
	}
}


//function for printing degree sequence
void degreeSequenec(int degrees[], int sortedVertices[], int amountOfVertices)
{
	mergeSort(degrees, sortedVertices, 1, amountOfVertices);

	printNumberSequence(amountOfVertices, degrees);
}


//function to chck if graph is bipartipe using BFS algorithm
bool checkIfBipartite(Vector<Vector<int>>& Graph, int amountOfVertices)
{
	int* colors = new int[amountOfVertices + 1]();
	Queue coloredVertices;

	for (int i = 1; i <= amountOfVertices; i++)
	{
		//if vertex isint colored coloring it with fisrt color and adding to a queue
		if (colors[i] == 0)
		{
			coloredVertices.push(i);
			colors[i] = 1;
		}
		
		//doing BFS search for neigbours
		while (!coloredVertices.isEmpty())
		{
			int currentVertex = coloredVertices.front();
			coloredVertices.pop();

			int currentVertexColor = colors[currentVertex];

			//checcking it for all neighbour of the vertex
			for (int neighbour : Graph[currentVertex])
			{
				//if the neighbour has the same color as the current graph is not bipartite
				if (colors[neighbour] == currentVertexColor)
				{
					return false;
				}
				else if (colors[neighbour] == 0)
				{
					//setting correct color for the neighbour
					if (currentVertexColor == 1)
					{
						colors[neighbour] = 2;
					}
					else
					{
						colors[neighbour] = 1;
					}

					//adding neighbor to the queue so later we do coloring for its neighbours and so on
					coloredVertices.push(neighbour);
				}
			}
		}
	}

	delete[] colors;

	return true;
}


//Function for calculating the complement edges
long long amountOfComplementsEdges(int amountOfVertices, unsigned long long sumOfDegrees)
{
	unsigned long long allVertices = amountOfVertices;
	unsigned long long allVertices_1 = amountOfVertices - 1;

	unsigned long long edges = (sumOfDegrees / 2);
	unsigned long long maxEdges = (allVertices * allVertices_1) / 2;
	long long result = static_cast<long long>(maxEdges - edges);

	return result;	
}

//function for updating arrays for coloring vertices
void updatingAviableColorsArray(int amountOfVertices, int current, bool avaiableColors[], int colored[], Vector<Vector<int>>& Graph)
{
	for (int i = 1; i <= amountOfVertices; i++)
	{
		avaiableColors[i] = true;
	}

	for (int j : Graph[current])
	{
		//if vertex is colored setting false for this color (each vertex represant one color) in avaiable Colors
		if (colored[j] != 0)
		{
			avaiableColors[colored[j]] = false;
		}
	}
}


//Function for coloring vertices using greedy algoritm
void coloringGreedyAlgorithm(int amountOfVertices, Vector<Vector<int>>& Graph) 
{
	int* colored = new int[amountOfVertices + 1]();
	bool* avaiableColors = new bool[amountOfVertices + 1];
	
	colored[1] = 1; 


	for (int current = 2; current <= amountOfVertices; current++) 
	{
		//if vertex is colored already
		if (colored[current] != 0)
		{
			continue;
		}

		//if vertex is isolated
		if (Graph[current].empty())
		{
			colored[current] = 1; 
			continue;
		}

		updatingAviableColorsArray(amountOfVertices, current, avaiableColors, colored, Graph);


		//choosing the lowest possible color
		int chosenColor = 1;
		while (!avaiableColors[chosenColor])
		{
			chosenColor++;
		}

		colored[current] = chosenColor;

	}

	printNumberSequence(amountOfVertices, colored);

	delete[] colored;
	delete[] avaiableColors;
}


//Function for coloring vertices using LF algorithm
void coloringLFAlgorithm(Vector<Vector<int>>& Graph, int amountOfVertices, int* sortedVertices)
{
	int* colored = new int[amountOfVertices + 1]();
	bool* availableColors = new bool[amountOfVertices + 1];


	for (int i = 1; i <= amountOfVertices; i++) 
	{
		int vertex = sortedVertices[i];

		//if vertex is isolated
		if (Graph[vertex].empty())
		{
			colored[vertex] = 1;
			continue;
		}

		updatingAviableColorsArray(amountOfVertices, vertex, availableColors, colored, Graph);

		//fill the current vertex with the lowest possible color
		for (int k = 1; k <= amountOfVertices; k++) 
		{
			if (availableColors[k]) 
			{
				colored[vertex] = k;
				break;
			}
		}
	}

	printNumberSequence(amountOfVertices, colored);

	delete[] colored;
	delete[] availableColors;
}


//DFS algorithm to update array having size of component for each vertex
void DFSforSizeOfComponents(int current, bool visitedForSize[], Vector<Vector<int>>& Graph, int& componentSize, int* sizeOfComponents)
{
	visitedForSize[current] = true;
	sizeOfComponents[current] = componentSize - 1;
	for (int neighbor : Graph[current])
	{
		if (!visitedForSize[neighbor])
		{
			DFSforSizeOfComponents(neighbor, visitedForSize, Graph, componentSize, sizeOfComponents);
		}
	}
}


//DFS algorithm to update size of componnents
void DFSforNumberOfComponents(int current, bool visitedForNumber[], Vector<Vector<int>>& Graph, int& componentSize)
{
	visitedForNumber[current] = true;
	componentSize++;

	for (int neighbor : Graph[current])
	{
		if (!visitedForNumber[neighbor])
		{
			DFSforNumberOfComponents(neighbor, visitedForNumber, Graph, componentSize);
		}
	}
}


//function using dfs algorithms to count the number of componnents
int numberOfComponents(int amountOfVertices, Vector<Vector<int>>& Graph, int* sizeOfComponents)
{
	bool* visitedForNumber = new bool[amountOfVertices + 1]();
	bool* visitedForSize = new bool[amountOfVertices + 1]();
	int count = 0;

	for (int v = 1; v <= amountOfVertices; v++)
	{
		if (!visitedForNumber[v])
		{
			int componentSize = 0;
			DFSforNumberOfComponents(v, visitedForNumber, Graph, componentSize);

			DFSforSizeOfComponents(v, visitedForSize, Graph, componentSize, sizeOfComponents);

			count++;
		}
	}

	delete[] visitedForNumber;
	delete[] visitedForSize;

	return count;
}


//BFS function for calculating eccenricity
int BFS(int start, Vector<Vector<int>>& Graph, int component, int amountOfVertices)
{
	int* distance = new int[amountOfVertices + 1]();
	int* componentVertices = new int[amountOfVertices + 1];
	int front = 0, back = 0;


	componentVertices[back++] = start;
	distance[start] = 1;
	int checkedVertices = 1;
	int max_distance = 0;

	//finishing loop when it will check all the vertices in the componnet
	while (checkedVertices < component+1)
	{
		int current = componentVertices[front++];

		for (int neighbor : Graph[current])
		{
			if (distance[neighbor] == 0)
			{
				//adding neighbour to the component array and updating max distance
				componentVertices[back++] = neighbor;
				distance[neighbor] = distance[current]+1;
				checkedVertices++;

				if (distance[neighbor] > max_distance)
				{
					max_distance = distance[neighbor];
				}
			}
		}
	}


	delete[] distance;
	delete[] componentVertices;

	return max_distance-1;

}


//function for eccentricy of the vertices
void eccentricity(int amountOfVertices, Vector<Vector<int>>& Graph, int* sizeOfComponents)
{
	for (int v = 1; v <= amountOfVertices; v++)
	{
		//skip isolated vertices
		if (!Graph[v].empty())
		{
			printf("%d ", BFS(v, Graph, sizeOfComponents[v], amountOfVertices));
		}
		else
		{
			printf("%d ",0);
		}
	}

}


//function to fill sorted vertices array
void fillSortedVerticesArray(int amountOfVertices, int sortedVertices[])
{
	for (int i = 1; i <= amountOfVertices; i++)
	{
		sortedVertices[i] = i;
	}
}


//function to print the output
void printOutput(int amountOfVertices, Vector<Vector<int>>& Graph, int degrees[], int sortedVertices[], int sizeOfComponents[], int sumOfDegrees)
{
	degreeSequenec(degrees, sortedVertices, amountOfVertices);
	printf("\n");
	printf("%d \n", numberOfComponents(amountOfVertices, Graph, sizeOfComponents));
	checkIfBipartite(Graph, amountOfVertices) ? printf("%c \n", 'T') : printf("%c \n", 'F');
	eccentricity(amountOfVertices, Graph, sizeOfComponents);
	printf("\n");
	printf("%c \n", '?');
	coloringGreedyAlgorithm(amountOfVertices, Graph);
	printf("\n");
	coloringLFAlgorithm(Graph, amountOfVertices, sortedVertices);
	printf("\n");
	printf("%c \n", '?');
	printf("%c \n", '?');
	printf("%lld \n", amountOfComplementsEdges(amountOfVertices, sumOfDegrees));
}


int main()
{
	int amountOfGraphs;
	int amountOfVertices;
	int sumOfDegrees = 0;
	Vector<Vector<int>> Graph;

	cin >> amountOfGraphs;

	for (int k = 0; k < amountOfGraphs; k++)
	{
		cin >> amountOfVertices;
		Graph.resizeNow(amountOfVertices+1);
		int* degrees = new int[amountOfVertices + 1];
		sumOfDegrees = 0;

		for (int i = 1; i <= amountOfVertices; i++)
		{
			int degree;
			cin >> degree;
			sumOfDegrees += degree;
			degrees[i] = degree;
			for (int j = 0; j < degree; j++)
			{
				int element;
				cin >> element;
				Graph[i].push_back(element);
			}
		}

		int* sizeOfComponents = new int[amountOfVertices + 1]();
		int* sortedVertices = new int[amountOfVertices + 1];

		fillSortedVerticesArray(amountOfVertices, sortedVertices);

		printOutput(amountOfVertices, Graph, degrees, sortedVertices, sizeOfComponents, sumOfDegrees);

		Graph.clear();
		delete[] sizeOfComponents;
		delete[] degrees;
		delete[] sortedVertices;
	}

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
