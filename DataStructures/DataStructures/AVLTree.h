#pragma once
template<typename T>
class AVLTree
{
	
	struct Node
	{
		T key;
		Node* left;
		Node* right;
		unsigned char height; // It is pretty legal to use 1 byte. Because of the fact that to overflow the limit of byte the height must be over than 255. 
							  // Which means to have more keys than - 57896044618658097711785492504343953926634992332820282019728792003956564819968.
	};

	Node* root;

	unsigned char Height(Node* n);
	int BalanceFactor(Node* n);
	void FixHeight(Node* n);
	Node* Balance(Node* n);
	Node* RightRotation(Node* &n);
	Node* LeftRotation(Node* &n);
	Node* Insert(T v, Node* n);
	Node* Remove(T v, Node* n);
	Node* FindMin(Node* n);
	Node* FindMax(Node* n);
	void* PopMax(Node* n);
	void Clear(Node* n);
	void InOrder(Node* n);
	

public:
	AVLTree()
	~AVLTree();

	void Insert(T v);
	void Remove(T v);
	void Display();
};

/////////////////////////
// Private Definitions //
/////////////////////////

// The definition needs to be in the header file, because it is declared as Class Template
template<typename T>
unsigned char AVLTree<T>::Height(Node* n)
{
	return n ? n->height : 0;
}

template<typename T>
int AVLTree<T>::BalanceFactor(Node* n)
{
	if (n == nullptr)
		return 0;

	return Height(n->left) - Height(n->right);
}

template<typename T>
void AVLTree<T>::FixHeight(Node* n)
{
	n->height = std::max(Height(n->left), Height(n->right)) + 1;
}

template<typename T>
AVLTree<T>::Node* AVLTree<T>::Balance(Node* n)
{
	FixHeight(n);
	int currentBalanceFactor = BalanceFactor(n);
	if (currentBalanceFactor == 2)
	{
		if (BalanceFactor(n->left) < 0)
			n->left = LeftRotation(n->left);

		return RightRotation(n);
	}

	if (currentBalanceFactor == -2)
	{
		if (BalanceFactor(n->right) > 0)
			n->right = RightRotation(n->right);

		return LeftRotation(n);
	}

	return n; // no balance needed
}

template<typename T>
AVLTree<T>::Node* AVLTree<T>::RightRotation(Node* &n)
{
	Node* l = n->left;
	n->left = l->right;
	l->right = n;
	FixHeight(n);
	FixHeight(l);
	return l;
}

template<typename T>
AVLTree<T>::Node* AVLTree<T>::LeftRotation(Node* &n)
{
	Node* r = n->right;
	n->right = r->left;
	r->left = n;
	FixHeight(n);
	FixHeight(r);
	return r;
}

template<typename T>
AVLTree<T>::Node* AVLTree<T>::Insert(T v, Node* n)
{
	if (n == nullptr)
	{
		return new Node(v);
	}

	if (v < n->key)
		n->left = Insert(v, n->left);
	else if (v > n->key)
		n->right = Insert(v, n->right);

	return Balance(n);
}

template<typename T>
AVLTree<T>::Node* AVLTree<T>::FindMin(Node* n)
{
	return n->left ? findmin(n->left) : n;
}

template<typename T>
AVLTree<T>::Node* AVLTree<T>::FindMax(Node* n)
{
	return n->Right ? FindMax(n->right) : n;
}

template<typename T>
void* AVLTree<T>::PopMax(Node* n)
{
	Node* max = FindMax(n);
	void* key = max->key;
	Remove(n, key);
	return key;
}

template<typename T>
AVLTree<T>::Node* AVLTree<T>::Remove(T v, Node* n)
{
	Node* temp;

	// Element not found
	if (n == nullptr)
		return nullptr;

	// Searching for element
	if (v < n->data)
		n->left = Remove(v, n->left);
	else if (v > n->data)
		n->right = Remove(v, n->right);

	// Element found
	// With 2 children
	else if (n->left && n->right)
	{
		temp = FindMin(n->right);
		n->data = temp->data;
		n->right = Remove(n->data, n->right);
	}
	// With one or zero child
	else
	{
		temp = n;
		if (n->left == nullptr)
			n = n->right;
		else if (n->right == nullptr)
			n = n->left;

		delete temp;
	}

	if (n == nullptr)
		return n;

	return Balance(n);
}

template<typename T>
void AVLTree<T>::Clear(Node* n)
{
	if (n == nullptr)
		return;

	Clear(n->left);
	Clear(n->right);
	delete n;
}

template<typename T>
void AVLTree<T>::InOrder(Node* n)
{
	if (!n)
		return;

	InOrder(n->left);
	std::cout << n->data << " ";
	InOrder(n->right);

}

////////////////////////
// Public Definitions //
////////////////////////

template<typename T>
void AVLTree<T>::Insert(T v)
{
	root = Insert(v, root);
}

template<typename T>
void AVLTree<T>::Remove(T v)
{
	root = Remove(v, root);
}

template<typename T>
void AVLTree<T>::Display()
{
	InOrder(root);
	std::cout << std::endl;
}