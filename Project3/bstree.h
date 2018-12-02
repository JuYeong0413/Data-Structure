//--------------------------------------------------------------------
//
//  Laboratory 12                                           bstree.h
//
//  Class declarations for the linked implementation of the Binary
//  Search Tree ADT -- including the recursive partners of the
//  public member functions
//
//--------------------------------------------------------------------
template < class TE, class KF > class BSTree;
template < class TE, class KF > class BSTreeNode;

template < class TE, class KF >
class BSTreeNode             // Facilitator class for the BSTree class
{
private:

	// Constructor
	BSTreeNode(const TE &elem,
		BSTreeNode *firstPtr, BSTreeNode *secondPtr, BSTreeNode *thirdPtr);

	// Data members
	TE element;          // Binary search tree element
	BSTreeNode *first,   // Pointer to the first child
			   *second,	 // Pointer to the second child
			   *third;   // Pointer to the third child

	friend class BSTree<TE, KF>;
};

//--------------------------------------------------------------------

template < class TE, class KF >    // TE : tree element
class BSTree                       // KF : key field
{
public:

	// Constructor
	BSTree();

	// Destructor
	~BSTree();

	// Binary search tree manipulation operations
	void insert(const TE &newElement2);			 // Insert element
	int retrieve(KF searchKey, TE &searchElement);
	// Retrieve element
	int remove(KF deleteKey);                    // Remove element
	void clear();                                // Clear tree

	// Binary search tree status operations
	int empty() const;                           // Tree is empty
	int full() const;                            // Tree is full

	// Output the tree structure -- used in testing/debugging
	void showStructure() const;

private:

	// Recursive partners of the public member functions
	void insertSub(BSTreeNode<TE, KF> *&p, const TE &newElement2);
	int retrieveSub(BSTreeNode<TE, KF> *p, KF searchKey, TE &searchElement);
	int removeSub(BSTreeNode<TE, KF> *&p, KF deleteKey);
	void clearSub(BSTreeNode<TE, KF> *p);
	void showSub(BSTreeNode<TE, KF> *p, int level) const;
	void move(BSTreeNode<TE, KF> *ptr);

	// Data member
	BSTreeNode<TE, KF> *root;   // Pointer to the root node
	BSTreeNode<TE, KF> *cursor;
};