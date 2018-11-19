//--------------------------------------------------------------------
//
//  Laboratory 11                                           

//  Class declarations for the linked implementation of the
//  Expression Tree ADT -- including the recursive partners of the
//  public member functions
//
//--------------------------------------------------------------------
class ExprTree;
class ExprTreeNode;

class ExprTreeNode         // Facilitator class for the ExprTree class
{
private:

	// Constructor
	ExprTreeNode(char elem,
		ExprTreeNode *leftPtr, ExprTreeNode *rightPtr);

	// Data members
	char element;           // Expression tree element
	ExprTreeNode *left,     // Pointer to the left child
				 *right;    // Pointer to the right child

	friend class ExprTree;
};

//--------------------------------------------------------------------

class ExprTree
{
public:

	// Constructor
	ExprTree();
	// Destructor
	~ExprTree();

	//Copy Constructor for In-Lab. 2
	ExprTree(const ExprTree &valueTree);

	// Expression tree manipulation operations
	void build();              // Build tree from prefix expression
	void expression() const;   // Output expression in infix form
	float evaluate() const;    // Evaluate expression
	void clear();              // Clear tree

	// Output the tree structure -- used in testing/debugging
	void showStructure() const;

private:

	// Recursive partners of the public member functions -- insert
	// prototypes of these functions here.
	void buildSub(ExprTreeNode *&p, char *&expr);
	void exprSub(ExprTreeNode *p) const;
	float evaluateSub(ExprTreeNode *p) const;
	void clearSub(ExprTreeNode *p);
	void showSub(ExprTreeNode *p, int level) const;
	void copySub(ExprTreeNode *&p);
 
	// Data member
	ExprTreeNode *root;   // Pointer to the root node
};