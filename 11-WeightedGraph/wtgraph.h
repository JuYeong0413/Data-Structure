//--------------------------------------------------------------------
//
//  Laboratory 14                                            wtgraph.h
//
//  Class declaration for the adjacency matrix implementation of
//  the Weighted Graph ADT
//
//--------------------------------------------------------------------



const int defMaxGraphSize = 10,      // Default number of vertices
vertexLabelLength = 11,  // Length of a vertex label
infiniteEdgeWt = 9999;   // "Weight" of a missing edge

//--------------------------------------------------------------------

class Vertex
{
public:

	char label[vertexLabelLength];   // Vertex label
};

//--------------------------------------------------------------------

class WtGraph
{
public:

	// Constructor
	WtGraph(int maxNumber = defMaxGraphSize);

	// Destructor
	~WtGraph();

	// Graph manipulation operations
	void insertVertex(Vertex newVertex);           // Insert vertex
	void insertEdge(char *v1, char *v2, int wt);   // Insert edge
	int retrieveVertex(char *v, Vertex &vData) const;
	// Get vertex
	int edgeWeight(char *v1, char *v2, int &wt);
	// Get edge wt.
	void removeVertex(char *v);                    // Remove vertex
	void removeEdge(char *v1, char *v2);           // Remove edge
	void clear();                                    // Clear graph

	// Graph status operations
	int empty() const;                           // Graph is empty
	int full() const;                            // Graph is full

	// Output the graph structure -- used in testing/debugging
	void showStructure();

	// In-lab operation	
	void computePaths();

private:

	// Facilitator functions
	int index(char *v) const;       // Converts vertex label to an adjacency matrix index
	
	int& edge(int row, int col);    // Set/get edge weight using adjacency matrix indices


	// Data members
	int     maxSize,          // Maximum number of vertices in the graph
		    size;             // Actual number of vertices in the graph
	Vertex* vertexList;       // Vertex list
	int*    adjMatrix;        // Adjacency matrix

};