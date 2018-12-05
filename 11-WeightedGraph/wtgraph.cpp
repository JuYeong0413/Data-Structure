#include <iostream>
#include <assert.h>
#include "wtgraph.h"
using namespace std;

WtGraph::WtGraph(int maxNumber)
// Constructor. Creates an empty graph.
// Allocates enough memory for a graph containing maxNumber vertices.
{
	maxSize = maxNumber;
	size = 0;
	vertexList = new Vertex[maxSize];
	adjMatrix = new int[maxSize*maxSize];
}

WtGraph::~WtGraph()
// Destructor. Deallocates (frees) the memory used to store a graph.
{
	delete[] vertexList;
	delete[] adjMatrix;
}

void WtGraph::insertVertex(Vertex newVertex)
// Inserts newVertex into a graph.
// If the vertex already exists in the graph, then updates it.
{
	if (full()) cout << "Failed -- Graph is full" << endl;
	else {
		int position; // position of the vertex in the vertex list

		position = index(newVertex.label);
		vertexList[position] = newVertex;

		if (position == size) { // new vertex
			size++;
			for (int i = 0; i < size; i++) {
				edge(size - 1, i) = infiniteEdgeWt;
				edge(i, size - 1) = infiniteEdgeWt;
			}
		}
	}
}

void WtGraph::insertEdge(char *v1, char *v2, int wt)
// Inserts an undirected edge connecting vertices v1 and v2 into a graph.
// The weight of the edge is wt.
// If there is already an edge connecting these vertices, then updates the weight of the edge.
{
	int index1 = index(v1); // index of vertex v1
	int index2 = index(v2); // index of vertex v2

	edge(index1, index2) = wt;
	edge(index2, index1) = wt;
}

int WtGraph::retrieveVertex(char *v, Vertex &vData) const
// Searches a graph for vertex v. If this vertex is found, then copies the vertex¡¯s data to
// vData and returns true.Otherwise, returns false with vData undefined.
{
	int position; // position of v in the vertex list
	int result = 0;

	position = index(v);
	if (position != size) {
		vData = vertexList[position];
		result = 1;
	}

	return result;
}

int WtGraph::edgeWeight(char *v1, char *v2, int &wt)
// Searches a graph for the edge connecting vertices v1 and v2. If this edge exists, then
// returns true with wt returning the weight of the edge. Otherwise, returns false with
// wt undefined.
{
	int index1 = index(v1); // index of vertex v1
	int index2 = index(v2); // index of vertex v2

	wt = edge(index1, index2);
	if (wt != infiniteEdgeWt) return 1;
	else return 0;
}

void WtGraph::removeVertex(char *v)
// Removes vertex v from a graph.
{
	if (empty()) cout << "Failed -- Graph is empty" << endl;
	else {
		int vIndex = index(v); // Index of vertex v
		int i, j; // Loop counters

		// shift vertex list
		for (i = vIndex; i < size - 1; i++) {
			vertexList[i] = vertexList[i + 1];
		}

		// shift row
		for (i = vIndex; i < size - 1; i++) {
			for (j = 0; j < size; j++)
				edge(i, j) = edge(i + 1, j);
		}

		// shift column
		for (i = vIndex; i < size - 1; i++) {
			for (j = 0; j < size; j++)
				edge(j, i) = edge(j, i + 1);
		}

		size--;
	}
}

void WtGraph::removeEdge(char *v1, char *v2)
// Removes the edge connecting vertices v1 and v2 from a graph.
{
	if (empty()) cout << "Failed -- Graph is empty" << endl;
	else {
		int index1 = index(v1); // index of vertex v1
		int index2 = index(v2); // index of vertex v2

		edge(index1, index2) = infiniteEdgeWt;
		edge(index2, index1) = infiniteEdgeWt;
	}
}

void WtGraph::clear()
// Removes all the vertices and edges in a graph.
{
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {
			adjMatrix[maxSize * row + col] = 0;
		}
	}
	size = 0;
}

int WtGraph::empty() const
// Returns true if a graph is empty (no vertices). Otherwise, returns false.
{
	return (size == 0);
}

int WtGraph::full() const
// Returns true if a graph is full. Otherwise, returns false.
{
	return (size == maxSize);
}

void WtGraph::showStructure()
// Outputs a graph with the vertices in array form and the edges in adjacency matrix
// form(with their weights). If the graph is empty, outputs "Empty graph".
// Note that this operation is intended for testing / debugging purposes only.
{
	int weight, row, col;

	if (empty()) cout << "Empty graph" << endl;
	else {
		// print vertex list
		cout << endl << "Vertex list : " << endl;
		for (row = 0; row < size; row++) {
			cout << row << "\t" << vertexList[row].label << endl;
		}

		// print edge matrix
		cout << endl << "Edge matrix : " << endl << "\t";
		for (col = 0; col < size; col++) {
			cout << col << "\t";
		}
		cout << endl;
		for (row = 0; row < size; row++) {
			cout << row << "\t";
			for (col = 0; col < size; col++) {
				weight = edge(row, col);
				if (weight == infiniteEdgeWt) cout << "- \t";
				else cout << weight << "\t";
			}
			cout << endl;
		}
	}
}

//--------------------------------------------------------------------

void WtGraph::computePaths()
// Computes a graph¡¯s path matrix.
{
	if (empty()) cout << "Empty path" << endl;
	else
	{
		int* pathMatrix = new int[maxSize*maxSize]; // path matrix
		int row, col, weight;
		int k, i, j, weight1, weight2, weight3;

		// copy adjMatrix to pathMatrix
		for (row = 0; row < size; row++) {
			for (col = 0; col < size; col++) {
				pathMatrix[maxSize * row + col] = edge(row, col);
			}
		}

		// compute paths
		for (k= 0; k < size; k++) {
			for (i = 0; i < size; i++) {
				for (j = 0; j < size; j++) {
					weight1 = pathMatrix[maxSize * i + j];
					weight2 = pathMatrix[maxSize * i + k];
					weight3 = pathMatrix[maxSize * k + j];
					
					if (k != i && i != j && j != k) {
						if (weight1 > weight2 + weight3) {
							pathMatrix[maxSize * i + j] = weight2 + weight3;
						}
					}
				}
			}
		}

		// print path matrix
		cout << endl << "Path matrix : " << endl << "\t";
		for (col = 0; col < size; col++) {
			cout << col << "\t";
		}
		cout << endl;
		for (row = 0; row < size; row++) {
			cout << row << "\t";
			for (col = 0; col < size; col++) {
				weight = pathMatrix[maxSize * row + col];
				if (weight == infiniteEdgeWt) cout << "- \t";
				else cout << weight << "\t";
			}
			cout << endl;
		}
	}
}

//--------------------------------------------------------------------

int WtGraph::index(char *v) const
{
	int i;
	for (i = 0; i < size  &&  strcmp(vertexList[i].label, v) != 0; i++);
	return i;
}

int& WtGraph::edge(int row, int col)
{
	return adjMatrix[maxSize * row + col];
}