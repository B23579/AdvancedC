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

	// initializes the nodes with appropirate values
	// all the pointers are set to point to the null pointer
	void initializeNULLNode(NodePtr node, NodePtr parent) {
		node->data = 0;
		node->parent = parent;
		node->_left = nullptr;
		node->_right = nullptr;
		node->color = 0;
	}

	// fix the red black tree modified by the delete operation
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
		NodePtr z = nullptr;
		NodePtr x, y;
		while (node != nullptr){
			if (node->data == key) {
				z = node;
			}

			if (node->data <= key) {
				node = node->_right;
			} else {
				node = node->_left;
			}
		}

		if (z == nullptr) {
			cout<<"Couldn't find key in the tree"<<endl;
			return;
		} 

		y = z;
		int y_original_color = y->color;
		if (z->_left == nullptr) {
			x = z->_right;
			rbTransplant(z, z->_right);
		} else if (z->_right == nullptr) {
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
			if (k->parent == k->parent->parent->_right && k->parent->parent->_left != nullptr) {
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

				if (k->parent->parent->_right != nullptr && u->color == 1) {
					
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

	void printRBtree(NodePtr root, string indent, bool last) {
		// print the tree structure on the screen
	   	if (root != nullptr) {
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
		   printRBtree
	(root->_left, indent, false);
		   printRBtree
	(root->_right, indent, true);
		}
		// cout<<root->left->data<<endl;
	}

public:
	RBTree<T,CMP>() {
		root = nullptr;
	}
	
class const_iterator {
	private:
	NodePtr _pNode;
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

		//cout << _pNode->data << endl;

		if (this->_pNode->_right != nullptr) {
				NodePtr temp = this->_pNode->_right;
			while (temp->_left) { //find the most left node of the node
				temp = temp->_left;
			}
			this->_pNode = temp; //++Then it becomes the node
		}
		else
		{
			if(_pNode->parent != nullptr){
				if(this->_pNode == this->_pNode->parent->_left) {
					this->_pNode = this->_pNode->parent;
					} 
				else{
					if(this->_pNode->parent->parent != nullptr){
						if(this->_pNode->parent == this->_pNode->parent->parent->_left)
							_pNode = this->_pNode->parent->parent;
						else
							_pNode = nullptr;
					}else
						_pNode	 = nullptr;
				}
			}
		}
	}
};


	const_iterator begin() const
	{
		NodePtr temp = this->root;
		while (temp->_left != nullptr)
		{
			temp = temp->_left;
		}

		return const_iterator(temp);
	}

	const_iterator end() const
	{
		return const_iterator(nullptr);
	}

	// find the node with the minimum key
	NodePtr minimum(NodePtr node) {
		while (node->_left != nullptr) {
			node = node->_left;
		}
		return node;
	}

	// find the node with the maximum key
	NodePtr maximum(NodePtr node) {
		while (node->_right != nullptr) {
			node = node->_right;
		}
		return node;
	}

	// find the successor of a given node
	NodePtr successor(NodePtr x) {
		// if the right subtree is not null,
		// the successor is the leftmost node in the
		// right subtree
		if (x->_right != nullptr) {
			return minimum(x->_right);
		}

		// else it is the lowest ancestor of x whose
		// left child is also an ancestor of x.
		NodePtr y = x->parent;
		while (y != nullptr && x == y->_right) {
			x = y;
			y = y->parent;
		}
		return y;
	}

	// find the predecessor of a given node
	NodePtr predecessor(NodePtr x) {
		// if the left subtree is not null,
		// the predecessor is the right most node in the 
		// left subtree
		if (x->_left != nullptr) {
			return maximum(x->_left);
		}

		NodePtr y = x->parent;
		while (y != nullptr && x == y->_left) {
			x = y;
			y = y->parent;
		}

		return y;
	}

	// rotate left at node x
	void leftRotate(NodePtr x) {
		NodePtr y = x->_right;
		x->_right = y->_left;
		if (y->_left != nullptr) {
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
		if (y->_right != nullptr) {
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
		node->_left = nullptr;
		node->_right = nullptr;
		node->color = 1; // new node must be red

		NodePtr y = nullptr;
		NodePtr x = this->root;

		while (x != nullptr) {
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

	// delete the node from the tree
	void deleteNode(int data) {
		deleteNodeHelper(this->root, data);
	}

	// print the tree structure on the screen
	void PrintRBT() {
	    if (root) {
    		printRBtree
	(this->root, "", true);
	    }
	}

};


int main() {
	RBTree<int,std::less<int>> bst;

	bst.insert(7);
	bst.insert(3);
	bst.insert(2);
	bst.insert(4);
	bst.insert(8);
	bst.insert(5);
	bst.insert(6);
	bst.insert(1);


	cout<< "Red-black-tree before node deletion"<<endl;
	

	bst.PrintRBT();

	bst.deleteNode(5);
	cout<<endl;
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
	//RBTree<int,std::less<int>>::const_iterator itr = bst.begin();

	for (RBTree<int,std::less<int>>::const_iterator its = bst.begin(); its != bst.end(); ++its){
        	std::cout << *its << std::endl;
	 	}
	
	

	cout<<endl;

	return 0;
}
