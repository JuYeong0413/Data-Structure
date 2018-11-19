#include <iostream>
#include <assert.h>
#include "exprtree.h"
using namespace std;

ExprTreeNode::ExprTreeNode(char elem, ExprTreeNode *leftPtr, ExprTreeNode *rightPtr)
{
	element = elem;
	left = leftPtr;
	right = rightPtr;
}

//--------------------------------------------------------------------

ExprTree::ExprTree()
// Constructor. Creates an empty expression tree.
{
	root = NULL;
}

ExprTree::~ExprTree()
// Destructor. Deallocates (frees) the memory used to store an expression tree.
{
	clear();
}

ExprTree::ExprTree(const ExprTree &valueTree)
// Copy constructor. Creates a copy of valueTree. This constructor is automatically invoked
// whenever an expression tree is passed to a function using call by value, a function returns an
// expression tree, or an expression tree is initialized using another expression tree.
{
	copySub(root);
}

void ExprTree::build()
// Reads an arithmetic expression in prefix form from the keyboard and builds the
// corresponding expression tree.
{
	char *prefix = new char[20];
	cin >> prefix;
	buildSub(root, prefix);
}

void ExprTree::expression() const
// Outputs the corresponding arithmetic expression in fully parenthesized infix form.
{
	exprSub(root);
}

float ExprTree::evaluate() const
// Returns the value of the corresponding arithmetic expression.
{
	return evaluateSub(root);
}

void ExprTree::clear()
// Removes all the data items in an expression tree.
{
	if (root != NULL) {
		clearSub(root);
		root = NULL;
	}
}

void ExprTree::showStructure() const
/*
Outputs an expression tree with its branches oriented from left (root) to right (leaves)-
that is, the tree is output rotated counterclockwise 90 degrees from its conventional
orientation.If the tree is empty, outputs "Empty tree".Note that this operation is
intended for testing / debugging purposes only.It assumes that arithmetic expressions
contain only single - digit, nonnegative integers and the arithmetic operators for
addition, subtraction, multiplication, and division.
*/
{
	if (root == NULL) cout << "Empty tree" << endl;
	else {
		cout << endl;
		showSub(root, 1);
		cout << endl;
	}
}

//--------------------------------------------------------------------

void ExprTree::buildSub(ExprTreeNode *&p, char *&expr)
{
	ExprTreeNode *t;
	if (*expr != NULL) {
		t = new ExprTreeNode(NULL, NULL, NULL);
		t->element = *expr;
		p = t;

		if ((*expr >= '0') && (*expr <= '9')) return;
		else {
			buildSub(p->left, ++expr);
			buildSub(p->right, ++expr);
		}
	}
}

void ExprTree::exprSub(ExprTreeNode *p) const
{
	if (p != 0) {
		if (p->left != 0 && p->right != 0) {
			cout << "(";
			exprSub(p->left);
			cout << p->element;
			exprSub(p->right);
			cout << ")";
		}
		else {
			cout << p->element;
		}
	}
}

float ExprTree::evaluateSub(ExprTreeNode *p) const
{
	switch (p->element) {
	case '+':
		return (evaluateSub(p->left) + evaluateSub(p->right));
		break;
	case '-':
		return (evaluateSub(p->left) - evaluateSub(p->right));
		break;
	case '*':
		return (evaluateSub(p->left) * evaluateSub(p->right));
		break;
	case '/':
		return (evaluateSub(p->left) / evaluateSub(p->right));
		break;
	default: // if the element is operand
		return (p->element) - '0';
		break;
	}
}

void ExprTree::clearSub(ExprTreeNode *p)
{
	if (p != NULL) {
		clearSub(p->left);
		clearSub(p->right);
		delete p;
	}
}

void ExprTree::showSub(ExprTreeNode *p, int level) const
{
	int i;

	if (p != NULL) {
		showSub(p->right, level + 1);

		for (i = 0; i < level; i++) {
			cout << '\t';
		}
		cout << " " << p->element;
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

void ExprTree::copySub(ExprTreeNode *&p)
{
	ExprTreeNode* newNode;
	if (root == NULL) {
		p = NULL;
	}
	else {
		newNode = new ExprTreeNode(NULL, NULL, NULL);
		p = newNode;
		p->element = root->element;
		copySub(p->left);
		copySub(p->right);
	}
}