 //The structure of a binary tree ：
 #include<iostream>

enum Color{red,black};
template<class T>
struct RBTreeNode
{
	RBTreeNode(const T& x=T(),Color c=red)
		:left(nullptr)
	    ,right(nullptr)
		,parent(nullptr)
		,data(x)
		,color(c)
	{
	}
	RBTreeNode<T>* left;
	RBTreeNode<T>* right;
	RBTreeNode<T>* parent;
	T data;
	Color color;
};

//Here is the iterator of red black tree ：

template<class T>
struct RBTreeIterator {
public:
	typedef RBTreeNode<T> Node;
	typedef RBTreeIterator<T> Self;
	RBTreeIterator(Node* n=nullptr) 
		:_pNode(n)// Constructors 
	{
	}
	T& operator*() {
		return _pNode->data;
	}
	T* operator->() {
		return &(_pNode->data);
	}

	Self& operator++() {
		Increment();
		return *this;
	}
	Self& operator++(int) {
		Self tmp = this;
		Increment();
		return tmp;
	}
	Self& operator--() {
		Decrement();
		return *this;
	}
	Self& operator--(int) {
		Self tmp = this;
		Decrement();
		return tmp;
	}
	bool operator==(const Self& s) {
		return _pNode == s._pNode;
	}
	bool operator!=(const Self& s) {
		return _pNode != s._pNode;
	}
private:
	void Increment() {
		if (_pNode->right) {
			Node* temp = _pNode->right;
			while (temp->left) {
				temp = temp->left;
			}
			_pNode = temp;

		}
		else
		{
			Node* tmp = _pNode->parent;
			if (tmp->right==_pNode) {
				while (_pNode==tmp->right)
				{
					_pNode = tmp;
					tmp = tmp->parent;
				}
			}
			if (_pNode->right != tmp)
				_pNode = tmp;
		}
	}
	void Decrement() {
		if (_pNode->parent->parent == _pNode && _pNode->color==red)
			_pNode = _pNode->left;

		else if (_pNode->left) {
			    while (_pNode->right)
			    {
				    _pNode = _pNode->right;
			    }
		}
		else {
			Node* parent = _pNode->parent;
			while (parent->left == _pNode)
			{
				_pNode = parent;
				parent = parent->parent;
			}
			_pNode = parent;
		}
	}
private:
	Node* _pNode;
};