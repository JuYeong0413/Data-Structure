#include <assert.h>
#include "bstree.h"

template < class TE, class KF >
BSTreeNode<TE, KF>::BSTreeNode(const TE &elem, BSTreeNode *firstPtr, BSTreeNode *secondPtr, BSTreeNode *thirdPtr)
{
	element = elem;
	first = firstPtr;
	second = secondPtr;
	third = thirdPtr;
}

//--------------------------------------------------------------------

template < class TE, class KF >
BSTree<TE, KF>::BSTree()
// Constructor. Creates an empty binary search tree.
{
	root = NULL;
	cursor = NULL;
}

template < class TE, class KF >
BSTree<TE, KF>::~BSTree()
// Destructor. Deallocates (frees) the memory used to store a binary search tree.
{
	clear();
}

template < class TE, class KF >
void BSTree<TE, KF>::insert( const TE &newElement2)
// Inserts newDataItem into a binary search tree. If a data item with the same key as
// newDataItem already exists in the tree, then updates that data item’s nonkey fields
// with newDataItem’s nonkey fields.
{
	if (full()) cout << "Failed -- Tree is full" << endl;
	else insertSub(cursor, newElement2);
}

template < class TE, class KF >
int BSTree<TE, KF>::retrieve(KF searchKey, TE &searchElement)
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
	else return removeSub(cursor, deleteKey);
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
// degrees from its conventional orientation.If the tree is empty, outputs “Empty tree”.
// Note that this operation is intended for debugging purposes only.
{
	if (empty()) cout << "Empty tree" << endl;
	else {
		cout << endl;
		showSub(root, 0);
		cout << "============================================================" << endl;
	}
}

//--------------------------------------------------------------------

template < class TE, class KF >
void BSTree<TE, KF>::insertSub(BSTreeNode<TE, KF> *&p, const TE &newElement2)
{
	if (p == NULL) {
		p = new BSTreeNode<TE, KF>(newElement2, NULL, NULL, NULL);
		if (root == NULL) {
			root = p;
			cursor = root;
		}
	}
	else {
		if (p->first == NULL) insertSub(p->first, newElement2);
		else if (p->second == NULL) insertSub(p->second, newElement2);
		else if (p->third == NULL) insertSub(p->third, newElement2);
	}
}

template < class TE, class KF >
int BSTree<TE, KF>::retrieveSub(BSTreeNode<TE, KF> *p, KF searchKey, TE &searchElement)
{
	int result;

	if (p == NULL)
		result = 0;

	else if (p->element.key() != searchKey)
	{
		result = retrieveSub(p->first, searchKey, searchElement);
		if (result == 0)
			result = retrieveSub(p->second, searchKey, searchElement);
		if (result == 0)
			result = retrieveSub(p->third, searchKey, searchElement);
	}
	else
	{
		searchElement = p->element;
		cursor = p;
		result = 1;
	}

	return result;
}

template < class TE, class KF >
int BSTree<TE, KF>::removeSub(BSTreeNode<TE, KF> *&p, KF deleteKey)
{
	BSTreeNode<TE, KF>* temp;
	int result;

	if (p == NULL)
		result = 0;

	else if (p->element.key() == deleteKey)
	{
		temp = p;

		if (p->first == NULL) // deleting leaf node (no child)
		{
			BSTreeNode<TE, KF>* location;
			location = root;
			// delete하려는 node의 parent node를 가리키도록 location 이동
			while (location->first != p && location->second != p && location->third != p) {
				if (location->first == p || location->second == p || location->third == p) break;
				location = location->first;
			}

			if (location->first == p) {
				location->first = NULL;
				if (location->second != NULL) {
					location->first = location->second;
					location->second = NULL;
				}
				if (location->third != NULL) {
					location->second = location->third;
					location->third = NULL;
				}
			}
			else if (location->second == p) {
				location->second = NULL;
				if (location->third != NULL) {
					location->second = location->third;
					location->third = NULL;
				}
			}
			delete temp;
		}
		else if (temp == root) // deleting root node
		{
			TE elem;
			elem = cursor->first->element;
			cursor->element = elem;

			TE elem2;
			elem2 = cursor->first->first->element;
			cursor->first->element = elem2;

			move(cursor->first->first);
		}
		else // deleting middle node
		{	
			BSTreeNode<TE, KF>* location;
			location = root;
			while (location->first != p) { // delete하려는 node의 parent node를 가리키도록
				if (location->first == p) break;
				location = location->first;
			}

			TE elem;
			elem = cursor->first->element;
			cursor->element = elem;

			if (cursor->first->first != NULL) { // first node를 2개 이동해야 하는 경우
				move(cursor->first);
			}
			else { // first node를 1개만 이동해도 되는 경우
				if (cursor->second != NULL) {
					cursor->first = cursor->second;
					cursor->second = NULL;
				}
				if (cursor->third != NULL) {
					cursor->second = cursor->third;
					cursor->third = NULL;
				}
			}
		}
		result = 1;
	}
	return result;
}

template < class TE, class KF >
void BSTree<TE, KF>::clearSub(BSTreeNode<TE, KF> *p)
{
	if (p != NULL) {
		clearSub(p->first);
		clearSub(p->second);
		clearSub(p->third);
		delete p;
	}
}

template < class TE, class KF >
void BSTree<TE, KF>::showSub(BSTreeNode<TE, KF> *p, int level) const
{
	int i;

	if (p != NULL) {
		for (i = 0; i < level; i++) {
			cout << '+';
		}

		cout << p->element.key() << endl;		

		showSub(p->first, level + 1);
		showSub(p->second, level + 1);
		showSub(p->third, level + 1);
	}
}

//--------------------------------------------------------------------

template < class TE, class KF >
void BSTree<TE, KF>::move(BSTreeNode<TE, KF> *ptr)
{
	TE element;
	element = ptr->first->element;
	ptr->element = element;

	if (ptr->second != NULL) {
		ptr->first = ptr->second;
		ptr->second = NULL;
	}
	if (ptr->third != NULL) {
		ptr->second = ptr->third;
		ptr->third = NULL;
	}
}