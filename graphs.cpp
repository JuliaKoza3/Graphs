// Graphs.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Queue.h"
#include <iostream>
#include <vector>
#include <queue>

using namespace std;


void merge(int degrees[], int vertices[], int left, int mid, int right)
{
	int n1 = mid - left + 1;
	int n2 = right - mid;

	int* leftSideDegrees = new int[n1];
	int* rightSideDegrees = new int[n2];
	int* leftSideVertices = new int[n1];
	int* rightSideVertices = new int[n2];


	for (int i = 0; i < n1; i++)
	{
		leftSideDegrees[i] = degrees[left + i];
		leftSideVertices[i] = vertices[left + i];
	}
	for (int j = 0; j < n2; j++) 
	{
		rightSideDegrees[j] = degrees[mid + 1 + j];
		rightSideVertices[j] = vertices[mid + 1 + j];
	}

	int i = 0, j = 0, k = left;
	while (i < n1 && j < n2) 
	{
		if (leftSideDegrees[i] >= rightSideDegrees[j]) 
		{
			degrees[k] = leftSideDegrees[i];
			vertices[k] = leftSideVertices[i];
			i++;
		}
		else {
			degrees[k] = rightSideDegrees[j];
			vertices[k] = rightSideVertices[j];
			j++;
		}
		k++;
	}

	while (i < n1) {
		degrees[k] = leftSideDegrees[i];
		vertices[k] = leftSideVertices[i];
		i++;
		k++;
	}

	while (j < n2) {
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

// Merge sort function to sort the array in decreasing order
void mergeSort(int degrees[], int vertices[], int left, int right)
{
	if (left < right) 
	{
		int mid = left + (right - left) / 2;

		mergeSort(degrees, vertices, left, mid);
		mergeSort(degrees, vertices,mid + 1, right);

		merge(degrees, vertices,left, mid, right);
	}
}

void degreeSequenec(int degrees[], int sortedVertices[], int amountOfVertices)
{
	mergeSort(degrees, sortedVertices, 1, amountOfVertices);

	for (int i = 1; i <=amountOfVertices; i++)
	{
		printf("%d ", degrees[i]);
	}
}


bool checkIfBipartite(vector<vector<int>>& Graph, int amountOfVertices)
{
	//int* colors = new int[amountOfVertices + 1]();
	vector<int> colors(amountOfVertices + 1, 0);
	Queue coloredVertices;

	for (int i = 1; i <= amountOfVertices; i++)
	{
		if (colors[i] == 0)
		{
			coloredVertices.push(i);
			colors[i] = 1;
		}
		
		while (!coloredVertices.isEmpty())
		{
			int currentVertex = coloredVertices.front();
			coloredVertices.pop();

			int currentVertexColor = colors[currentVertex];

			for (int adjVtx : Graph[currentVertex])
			{
				if (colors[adjVtx] == currentVertexColor)
				{
					return false;
				}
				else if (colors[adjVtx] == 0)
				{
					colors[adjVtx] = (currentVertexColor == 1) ? 2 : 1;
					coloredVertices.push(adjVtx);
				}
			}
		}
	}

	//delete[] colors;

	return true;
}

long long amountOfComplementsEdges(int amountOfVertices, unsigned long long sumOfDegrees)
{
	unsigned long long vertices = amountOfVertices;
	unsigned long long vertices_1 = amountOfVertices - 1;

	unsigned long long edges = (sumOfDegrees / 2);
	unsigned long long maxEdges = (vertices * vertices_1) / 2;
	long long result = static_cast<long long>(maxEdges - edges);

	return result;	
}


void coloringGreedyAlgorithm(int amountOfVertices, vector<vector<int>>& Graph) 
{
	int* colored = new int[amountOfVertices + 1];
	bool* available = new bool[amountOfVertices + 1];

	for (int i = 1; i <= amountOfVertices; i++) 
	{
		colored[i] = 0;
	}
	
	colored[1] = 1; 


	for (int current = 2; current <= amountOfVertices; current++) 
	{
		if (colored[current] != 0) continue;

		if (Graph[current].empty()) // If the vertex has no neighbors
		{
			colored[current] = 1; // Assign color 1
			continue; // Skip the rest of the loop iteration
		}

		for (int i = 1; i <= amountOfVertices; i++)
		{
			available[i] = true;
		}

		for (int j : Graph[current]) 
		{
			if (colored[j] != 0) 
			{
				available[colored[j]] = false;
			}
		}

		int chosenColor = 1;
		while (!available[chosenColor])
		{
			chosenColor++;
		}

		colored[current] = chosenColor;

	}

	for (int i = 1; i <= amountOfVertices; i++) 
	{
		printf("%d ", colored[i]);
	}

	delete[] colored;
	delete[] available;
}


void coloringLFAlgorithm(vector<vector<int>>& Graph, int amountOfVertices, int* sortedVertices)
{
	int* colored = new int[amountOfVertices + 1];
	bool* available = new bool[amountOfVertices + 1];

	for (int i = 1; i <= amountOfVertices; i++)
	{
		colored[i] = 0;
	}

	for (int i = 1; i <= amountOfVertices; i++) 
	{
		int vertex = sortedVertices[i];

		if (Graph[vertex].empty()) 
		{
			colored[vertex] = 1;
			continue;
		}

		for (int j = 1; j <= amountOfVertices; j++)
		{
			available[j] = true;
		}


		for (int neighbor : Graph[vertex]) 
		{
			if (colored[neighbor] != 0) 
			{
				available[colored[neighbor]] = false;
			}
		}

		for (int color = 1; color <= amountOfVertices; color++) 
		{
			if (available[color]) {
				colored[vertex] = color;
				break;
			}
		}
	}

	for (int i = 1; i <= amountOfVertices; i++)
	{
		cout << colored[i] << " ";
	}

	delete[] colored;
	delete[] available;
}

void DFSforSizeOfComponents(int v, bool visited2[], vector<vector<int>>& Graph, int& component_size, int* sizeOfComponents)
{
	visited2[v] = true;
	sizeOfComponents[v] = component_size - 1;
	for (int neighbor : Graph[v])
	{
		if (!visited2[neighbor])
		{
			DFSforSizeOfComponents(neighbor, visited2, Graph, component_size, sizeOfComponents);
		}
	}
}


void DFSforNumberOfComponents(int v, bool visited[], vector<vector<int>>& Graph, int& component_size, int* componentIDs, int component_id)
{
	visited[v] = true;
	component_size++;
	componentIDs[v] = component_id;

	for (int neighbor : Graph[v])
	{
		if (!visited[neighbor])
		{
			DFSforNumberOfComponents(neighbor, visited, Graph, component_size, componentIDs, component_id);
		}
	}
}

int numberOfComponents(int amountOfVertices, vector<vector<int>>& Graph, int* sizeOfComponents)
{
	bool* visited = new bool[amountOfVertices + 1]();
	bool* visited2 = new bool[amountOfVertices + 1]();
	int* componentsIDs = new int[amountOfVertices + 1]();
	int count = 0;

	for (int v = 1; v <= amountOfVertices; v++)
	{
		if (!visited[v])
		{
			int component_size = 0;
			DFSforNumberOfComponents(v, visited, Graph, component_size, componentsIDs, count);

			DFSforSizeOfComponents(v, visited2, Graph, component_size, sizeOfComponents);

			count++;
		}
	}

	delete[] visited;
	delete[] componentsIDs;
	delete[] visited2;

	return count;
}


int BFS(int v, vector<vector<int>>& Graph, int component, int amountOfVertices)
{
	int* distance = new int[amountOfVertices + 1]();
	int* componentVertices = new int[amountOfVertices + 1];
	int front = 0, back = 0;

	componentVertices[back++] = v;
	distance[v] = 1;
	int checkedVertices = 1;
	int max_distance = 0;

	while (checkedVertices < component+1)
	{
		int current = componentVertices[front++];

		for (int neighbor : Graph[current])
		{
			if (distance[neighbor] == 0)
			{
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

void eccentricity(int amountOfVertices, vector<vector<int>>& Graph, int* sizeOfComponents)
{

	for (int v = 1; v <= amountOfVertices; v++)
	{
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


int main()
{
	int amountOfGraphs;
	int amountOfVertices;
	int sumOfDegrees = 0;

	vector<vector<int>> Graph;

	cin >> amountOfGraphs;

	for (int k = 0; k < amountOfGraphs; k++)
	{
		cin >> amountOfVertices;
		Graph.resize(amountOfVertices+1);
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

		int* sortedVertices = new int[amountOfVertices + 1];
		for (int i = 1; i <= amountOfVertices; i++)
		{
			sortedVertices[i] = i;
		}

		int* sizeOfComponents = new int[amountOfVertices + 1]();

		degreeSequenec(degrees, sortedVertices,amountOfVertices);
		printf("\n");
		int count = numberOfComponents(amountOfVertices, Graph, sizeOfComponents);
		printf("%d \n", count);
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
		printf("%lld \n",amountOfComplementsEdges(amountOfVertices, sumOfDegrees));

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
