#include<iostream>
using namespace std;
#include <functional>

// Template


// data structure that represents a node in the tree
struct Node {
	int data; // holds the key
	Node *parent; // pointer to the parent
	Node *_left; // pointer to left child
	Node *_right; // pointer to right child
	int color; // 1 -> Red, 0 -> Black
};

typedef Node *NodePtr;


template< class T, typename CMP> 
// class RBTree implements the operations in Red Black Tree
class RBTree {
private:
	NodePtr root;
	NodePtr TNULL;

	// initializes the nodes with appropirate values
	// all the pointers are set to point to the null pointer
	void initializeNULLNode(NodePtr node, NodePtr parent) {
		node->data = 0;
		node->parent = parent;
		node->_left = nullptr;
		node->_right = nullptr;
		node->color = 0;
	}

	// fix the rb tree modified by the delete operation
	void fixDelete(NodePtr x) {
		NodePtr s;
		while (x != root && x->color == 0) {
			if (x == x->parent->_left) {
				s = x->parent->_right;
				if (s->color == 1) {
					s->color = 0;
					x->parent->color = 1;
					leftRotate(x->parent);
					s = x->parent->_right;
				}

				if (s->_left->color == 0 && s->_right->color == 0) {
					s->color = 1;
					x = x->parent;
				} else {
					if (s->_right->color == 0) {
						s->_left->color = 0;
						s->color = 1;
						rightRotate(s);
						s = x->parent->_right;
					} 

					s->color = x->parent->color;
					x->parent->color = 0;
					s->_right->color = 0;
					leftRotate(x->parent);
					x = root;
				}
			} else {
				s = x->parent->_left;
				if (s->color == 1) {
					s->color = 0;
					x->parent->color = 1;
					rightRotate(x->parent);
					s = x->parent->_left;
				}

				if (s->_right->color == 0 && s->_right->color == 0) {
					s->color = 1;
					x = x->parent;
				} else {
					if (s->_left->color == 0) {
						s->_right->color = 0;
						s->color = 1;
						leftRotate(s);
						s = x->parent->_left;
					} 

					s->color = x->parent->color;
					x->parent->color = 0;
					s->_left->color = 0;
					rightRotate(x->parent);
					x = root;
				}
			} 
		}
		x->color = 0;
	}


	void rbTransplant(NodePtr u, NodePtr v){
		if (u->parent == nullptr) {
			root = v;
		} else if (u == u->parent->_left){
			u->parent->_left = v;
		} else {
			u->parent->_right = v;
		}
		v->parent = u->parent;
	}

	void deleteNodeHelper(NodePtr node, int key) {
		// find the node containing key
		NodePtr z = TNULL;
		NodePtr x, y;
		while (node != TNULL){
			if (node->data == key) {
				z = node;
			}

			if (node->data <= key) {
				node = node->_right;
			} else {
				node = node->_left;
			}
		}

		if (z == TNULL) {
			cout<<"Couldn't find key in the tree"<<endl;
			return;
		} 

		y = z;
		int y_original_color = y->color;
		if (z->_left == TNULL) {
			x = z->_right;
			rbTransplant(z, z->_right);
		} else if (z->_right == TNULL) {
			x = z->_left;
			rbTransplant(z, z->_left);
		} else {
			y = minimum(z->_right);
			y_original_color = y->color;
			x = y->_right;
			if (y->parent == z) {
				x->parent = y;
			} else {
				rbTransplant(y, y->_right);
				y->_right = z->_right;
				y->_right->parent = y;
			}

			rbTransplant(z, y);
			y->_left = z->_left;
			y->_left->parent = y;
			y->color = z->color;
		}
		delete z;
		if (y_original_color == 0){
			fixDelete(x);
		}
	}
	
	// fix the red-black tree
	void fixInsert(NodePtr k){
		NodePtr u;
		while (k->parent->color == 1) {
			if (k->parent == k->parent->parent->_right) {
				u = k->parent->parent->_left; // uncle
				if (u->color == 1) {
				
					u->color = 0;
					k->parent->color = 0;
					k->parent->parent->color = 1;
					k = k->parent->parent;
				} else {
					if (k == k->parent->_left) {
						
						k = k->parent;
						rightRotate(k);
					}
				
					k->parent->color = 0;
					k->parent->parent->color = 1;
					leftRotate(k->parent->parent);
				}
			} else {
				u = k->parent->parent->_right; // uncle

				if (u->color == 1) {
					
					u->color = 0;
					k->parent->color = 0;
					k->parent->parent->color = 1;
					k = k->parent->parent;	
				} else {
					if (k == k->parent->_right) {
				
						k = k->parent;
						leftRotate(k);
					}
					
					k->parent->color = 0;
					k->parent->parent->color = 1;
					rightRotate(k->parent->parent);
				}
			}
			if (k == root) {
				break;
			}
		}
		root->color = 0;
	}

	void printHelper(NodePtr root, string indent, bool last) {
		// print the tree structure on the screen
	   	if (root != TNULL) {
		   cout<<indent;
		   if (last) {
		      cout<<"R----";
		      indent += "     ";
		   } else {
		      cout<<"L----";
		      indent += "|    ";
		   }
            
           string sColor = root->color?"RED":"BLACK";
		   cout<<root->data<<"("<<sColor<<")"<<endl;
		   printHelper(root->_left, indent, false);
		   printHelper(root->_right, indent, true);
		}
		// cout<<root->left->data<<endl;
	}

public:
	RBTree<T,CMP>() {
		TNULL = new Node;
		TNULL->color = 0;
		TNULL->_left = nullptr;
		TNULL->_right = nullptr;
		root = TNULL;
	}
	
class const_iterator {
	private:
	NodePtr _pNode;
	NodePtr TNULL;
	// RBTree<T,CMP> _t;

public:
	typedef const_iterator Self; //Type of forward iterator
	const_iterator(NodePtr n=nullptr) 
		:_pNode(n)// Constructors // we construct an iterator through the pointer of a node
	{}
	
	// When the iterator dereferences, we return a reference to the node data
	const T& operator*() const {
		return this->_pNode->data;
	}
	//When the iterator performs the - > operation, we return the pointer of the node data
	const T* operator->() const {
		return &(this->_pNode->data);
	}

	Self& operator++() {
		 Increment();
		return *this;
	}

	Self& operator++(int) {
		 Increment();
		Self tmp = this->_pNode;
		return tmp;
	}
	// implement = = and != To determine whether the node is the same

	bool operator==(const Self& s) {
		return this->_pNode == s._pNode;
	}
	bool operator!=(const Self& s) {
		return this->_pNode != s._pNode;
	}

	// begin and end of iterators in red black tree:

    //begin returns the iterator of the first node in the middle order, which is the left most node
    //end returns the iterator at the next position of the last node in the middle order. Here, use a null pointer.

private: 
	void Increment() {

		if (this->_pNode->_right != nullptr and this->_pNode->parent == nullptr) {
			// The next access is the first node in the middle order in the right tree
			NodePtr temp = _pNode->_right;

			while (temp->_left) {
				temp = temp->_left;
			}
				this->_pNode = temp; //++Then it becomes the node

		}
		else  //The right subtree is empty
		{// have already processed the left subtree, and
        // there is no right subtree. move up the tree,
        // looking for a parent for which nodePtr is a left child,
        // stopping if the parent becomes NULL. a non-NULL parent
        // is the successor. if parent is NULL, the original node
        // was the last node inorder, and its successor
        // is the end of the list
			//Find an ancestor whose child is not on the father's right
			NodePtr tmp = _pNode->parent;

			if (tmp->_right!=_pNode) {
				while (_pNode==tmp->_right and tmp->_right!= TNULL)
				{
					_pNode = tmp;
					tmp = tmp->parent; //++Then it becomes the node
				}
				// if we were previously at the right-most node in
        // the tree, nodePtr = nullptr, and the iterator specifies
        // the end of the list
			}
			if (_pNode->_right != tmp)
				_pNode = tmp;
		}
	}
};

	const_iterator begin() const
	{
		NodePtr left = this->root;
		while (left && left->_left!= TNULL)
		{
			left = left->_left;
		}

		return const_iterator(left);
	}

	const_iterator end() const
	{
		return const_iterator(TNULL);
	}

	// find the node with the minimum key
	NodePtr minimum(NodePtr node) {
		while (node->_left != TNULL) {
			node = node->_left;
		}
		return node;
	}

	// find the node with the maximum key
	NodePtr maximum(NodePtr node) {
		while (node->_right != TNULL) {
			node = node->_right;
		}
		return node;
	}

	// find the successor of a given node
	NodePtr successor(NodePtr x) {
		// if the right subtree is not null,
		// the successor is the leftmost node in the
		// right subtree
		if (x->_right != TNULL) {
			return minimum(x->_right);
		}

		// else it is the lowest ancestor of x whose
		// left child is also an ancestor of x.
		NodePtr y = x->parent;
		while (y != TNULL && x == y->_right) {
			x = y;
			y = y->parent;
		}
		return y;
	}

	// find the predecessor of a given node
	NodePtr predecessor(NodePtr x) {
		// if the left subtree is not null,
		// the predecessor is the rightmost node in the 
		// left subtree
		if (x->_left != TNULL) {
			return maximum(x->_left);
		}

		NodePtr y = x->parent;
		while (y != TNULL && x == y->_left) {
			x = y;
			y = y->parent;
		}

		return y;
	}

	// rotate left at node x
	void leftRotate(NodePtr x) {
		NodePtr y = x->_right;
		x->_right = y->_left;
		if (y->_left != TNULL) {
			y->_left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		} else if (x == x->parent->_left) {
			x->parent->_left = y;
		} else {
			x->parent->_right = y;
		}
		y->_left = x;
		x->parent = y;
	}

	// rotate right at node x
	void rightRotate(NodePtr x) {
		NodePtr y = x->_left;
		x->_left = y->_right;
		if (y->_right != TNULL) {
			y->_right->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		} else if (x == x->parent->_right) {
			x->parent->_right = y;
		} else {
			x->parent->_left = y;
		}
		y->_right = x;
		x->parent = y;
	}

	// insert the key to the tree in its appropriate position
	// and fix the tree
	void insert(int key) {
		// Ordinary Binary Search Insertion
		NodePtr node = new Node;
		node->parent = nullptr;
		node->data = key;
		node->_left = TNULL;
		node->_right = TNULL;
		node->color = 1; // new node must be red

		NodePtr y = nullptr;
		NodePtr x = this->root;

		while (x != TNULL) {
			y = x;
			if (node->data < x->data) {
				x = x->_left;
			} else {
				x = x->_right;
			}
		}

		// y is parent of x
		node->parent = y;
		if (y == nullptr) {
			root = node;
		} else if (node->data < y->data) {
			y->_left = node;
		} else {
			y->_right = node;
		}

		// if new node is a root node, simply return
		if (node->parent == nullptr){
			node->color = 0;
			return;
		}

		// if the grandparent is null, simply return
		if (node->parent->parent == nullptr) {
			return;
		}

		// Fix the tree
		fixInsert(node);
	}

	NodePtr getRoot(){
		return this->root;
	}

	// delete the node from the tree
	void deleteNode(int data) {
		deleteNodeHelper(this->root, data);
	}

	// print the tree structure on the screen
	void PrintRBT() {
	    if (root) {
    		printHelper(this->root, "", true);
	    }
	}

};


int main() {
	RBTree<int,std::less<int>> bst;

	bst.insert(8);
	bst.insert(18);
	bst.insert(5);
	bst.insert(15);
	bst.insert(17);
	bst.insert(25);
	bst.insert(40);
	bst.insert(87);
	bst.insert(100);
	bst.insert(3);

	cout<< "Red-black-tree before node deletion"<<endl;
	bst.PrintRBT();

	bst.deleteNode(25);
	cout<< "Red-black-tree after node deletion"<<endl;
	bst.PrintRBT();

	RBTree<int,std::less<int>>::const_iterator it = bst.begin();

	cout<<endl;

	cout<<*it << " key return by bst.begin()"<<endl; 
	
	bool l{false};

	if( it==it) {
		l=true;
		cout<< "== condition is ok"<< endl;
	}
	l=0;
	if( it!=bst.end()) {
		l=true;
		cout<< "!= condition is ok"<< endl;
	}

	cout<<endl;
	cout<< "test the iterators"<<endl;
	cout <<endl;

	for (RBTree<int,std::less<int>>::const_iterator it = bst.begin(); it != bst.end();){

        std::cout << *it << std::endl;
		++it;
		}

	cout<<endl;

	return 0;
}
