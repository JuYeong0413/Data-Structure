#include <assert.h>
#include "bstree.h"

template < class TE, class KF >
BSTreeNode<TE, KF>::BSTreeNode(const TE &elem, BSTreeNode *leftPtr, BSTreeNode *rightPtr)
{
	element = elem;
	left = leftPtr;
	right = rightPtr;
}

//--------------------------------------------------------------------

template < class TE, class KF >
BSTree<TE, KF>::BSTree()
// Constructor. Creates an empty binary search tree.
{
	root = NULL;
}

template < class TE, class KF >
BSTree<TE, KF>::~BSTree()
// Destructor. Deallocates (frees) the memory used to store a binary search tree.
{
	clear();
}

template < class TE, class KF >
void BSTree<TE, KF>::insert(const TE &newElement)
// Inserts newDataItem into a binary search tree. If a data item with the same key as
// newDataItem already exists in the tree, then updates that data item¡¯s nonkey fields
// with newDataItem¡¯s nonkey fields.
{
	if (full()) cout << "Failed -- Tree is full" << endl;
	else insertSub(root, newElement);
}

template < class TE, class KF >
int BSTree<TE, KF>::retrieve(KF searchKey, TE &searchElement) const
// Searches a binary search tree for the data item with key searchKey. If this data item is
// found, then copies the data item to searchDataItem and returns true. Otherwise,
// returns false with searchDataItem undefined.
{
	if (empty()) {
		cout << "Failed -- Tree is empty" << endl;
		return 0;
	}
	else return retrieveSub(root, searchKey, searchElement);
}

template < class TE, class KF >
int BSTree<TE, KF>::remove(KF deleteKey)
// Deletes the data item with key deleteKey from a binary search tree. If this data item
// is found, then deletes it from the tree and returns true. Otherwise, returns false.
{
	if (empty()) {
		cout << "Failed -- Tree is empty" << endl;
			return 0;
	}
	else return removeSub(root, deleteKey);
}

template < class TE, class KF >
void BSTree<TE, KF>::writeKeys() const
// Outputs the keys of the data items in a binary search tree. The keys are output in
// ascending order, one per line.
{
	if (empty()) cout << "Failed -- Tree is empty" << endl;
	else writeKeysSub(root);
}

template < class TE, class KF >
void BSTree<TE, KF>::clear()
// Removes all the data items in a binary search tree.
{
	if (empty()) cout << "Failed -- Tree is already empty" << endl;
	else {
		clearSub(root);
		root = NULL;
	}
}

template < class TE, class KF >
int BSTree<TE, KF>::empty() const
// Returns true if a binary search tree is empty. Otherwise, returns false.
{
	if (root == NULL) return 1;
	else return 0;
}

template < class TE, class KF >
int BSTree<TE, KF>::full() const
// Returns true if a binary search tree is full. Otherwise, returns false.
{
	return 0;
}

template < class TE, class KF >
void BSTree<TE, KF>::showStructure() const
// Outputs the keys in a binary search tree. The tree is output with its branches oriented
// from left(root) to right(leaves); that is, the tree is output rotated counterclockwise 90
// degrees from its conventional orientation.If the tree is empty, outputs ¡°Empty tree¡±.
// Note that this operation is intended for debugging purposes only.
{
	if (empty()) cout << "Empty tree" << endl;
	else {
		cout << endl;
		showSub(root, 1);
		cout << endl;
	}
}

//--------------------------------------------------------------------

template < class TE, class KF >
int BSTree<TE, KF>::height() const
{
	if (empty()) {
		cout << "Failed -- Tree is empty" << endl;
		return 0;
	}
	else return heightSub(root);
}

template < class TE, class KF >
void BSTree<TE, KF>::writeLessThan(KF searchKey) const
{
	if (empty()) cout << "Failed -- Tree is empty" << endl;
	else writeLTSub(root, searchKey);
}

//--------------------------------------------------------------------

template < class TE, class KF >
void BSTree<TE, KF>::insertSub(BSTreeNode<TE, KF> *&p, const TE &newElement)
{
	if (p == NULL) {
		p = new BSTreeNode<TE, KF>(newElement, NULL, NULL);
		if (root == NULL) {
			root = p;
		}
	}
	else if (p->element.key() < newElement.key()) {
		insertSub(p->right, newElement);
	}
	else if (p->element.key() > newElement.key()) {
		insertSub(p->left, newElement);
	}
	else {
		cout << "Failed -- That number is already in the tree" << endl;
	}
}

template < class TE, class KF >
int BSTree<TE, KF>::retrieveSub(BSTreeNode<TE, KF> *p, KF searchKey, TE &searchElement) const
{
	int result;

	if (p == NULL)
		result = 0;
	else if (p->element.key() > searchKey)
		result = retrieveSub(p->left, searchKey, searchElement);
	else if (p->element.key() < searchKey)
		result = retrieveSub(p->right, searchKey, searchElement);
	else {
		searchElement = p->element;
		result = 1;
	}

	return result;
}

template < class TE, class KF >
int BSTree<TE, KF>::removeSub(BSTreeNode<TE, KF> *&p, KF deleteKey)
{
	BSTreeNode<TE, KF>* deleteNode;
	int result;

	if (p == NULL)
		result = 0;
	else if (p->element.key() > deleteKey)
		result = removeSub(p->left, deleteKey);
	else if (p->element.key() < deleteKey)
		result = removeSub(p->right, deleteKey);
	else {
		deleteNode = p;

		if (p->left == NULL) p = p->right;
		else if (p->right == NULL) p = p->left;
		else cutRightmost(p->left, deleteNode);

		delete deleteNode;
		result = 1;
	}

	return result;
}

template < class TE, class KF >
void BSTree<TE, KF>::cutRightmost(BSTreeNode<TE, KF> *&r, BSTreeNode<TE, KF> *&delPtr)
{
	if (r->right != NULL) cutRightmost(r->right, delPtr);
	else {
		delPtr->element = r->element;
		delPtr = r;
		r = r->left;
	}
}

template < class TE, class KF >
void BSTree<TE, KF>::writeKeysSub(BSTreeNode<TE, KF> *p) const
{
	if (p != NULL) {
		writeKeysSub(p->left);
		cout << p->element.key() << endl;
		writeKeysSub(p->right);
	}
}

template < class TE, class KF >
void BSTree<TE, KF>::clearSub(BSTreeNode<TE, KF> *p)
{
	if (p != NULL) {
		clearSub(p->left);
		clearSub(p->right);
		delete p;
	}
}

template < class TE, class KF >
void BSTree<TE, KF>::showSub(BSTreeNode<TE, KF> *p, int level) const
{
	int i;

	if (p != NULL) {
		showSub(p->right, level + 1);
		
		for (i = 0; i < level; i++) {
			cout << '\t';
		}
		cout << " " << p->element.key();
		if ((p->left != 0) && (p->right != 0)) {
			cout << "<";
		}
		else if (p->right != 0) {
			cout << "/";
		}
		else if (p->left != 0) {
			cout << "\\";
		}
		cout << endl;
		showSub(p->left, level + 1);
	}
}

//--------------------------------------------------------------------

template < class TE, class KF >
int BSTree<TE, KF>::heightSub(BSTreeNode<TE, KF> *p) const
{
	if (p == NULL) return 0;

	int leftHeight = heightSub(p->left);
	int rightHeight = heightSub(p->right);

	if (leftHeight >= rightHeight) {
		return leftHeight + 1;
	}
	else return rightHeight + 1;
}

template < class TE, class KF >
void BSTree<TE, KF>::writeLTSub(BSTreeNode<TE, KF> *p, KF searchKey) const
{
	if (p != NULL) {
		writeLTSub(p->left, searchKey);
		if (p->element.key() <= searchKey) cout << p->element.key() << endl;
		writeLTSub(p->right, searchKey);
	}
}