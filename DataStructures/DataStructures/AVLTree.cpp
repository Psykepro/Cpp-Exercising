#include <iostream>
#include <math.h>

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

	unsigned char Height(Node* n)
	{
		return n ? n->height : 0;
	}

	int BalanceFactor(Node* n)
	{
		if (n == nullptr)
			return 0;

		return Height(n->left) - Height(n->right);
	}

	void FixHeight(Node* n)
	{
		n->height = std::max(Height(n->left), Height(n->right)) + 1;
	}

	Node* Balance(Node* n)
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

	Node* RightRotation(Node* &n)
	{
		Node* l = n->left;
		n->left = l->right;
		l->right = n;
		FixHeight(n);
		FixHeight(l);
		return l;
	}

	Node* LeftRotation(Node* &n)
	{
		Node* r = n->right;
		n->right = r->left;
		r->left = n;
		FixHeight(n);
		FixHeight(r);
		return r;
	}

	Node* Insert(T v, Node* n)
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

	Node* FindMin(Node* n)
	{
		return n->left ? findmin(n->left) : n;
	}

	Node* FindMax(Node* n)
	{
		return n->Right ? FindMax(n->right) : n;
	}

	void* PopMax(Node* n)
	{
		Node* max = FindMax(n);
		void* key = max->key;
		Remove(n, key);
		return key;
	}

	Node* Remove(T v, Node* n)
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

	void Clear(Node* n)
	{
		if (n == nullptr)
			return;

		Clear(n->left);
		Clear(n->right);
		delete n;
	}

	void InOrder(Node* n)
	{
		if (!n)
			return;

		InOrder(n->left);
		std::cout << n->data << " ";
		InOrder(n->right);

	}

public:
	AVLTree()
	{
		root = nullptr;
	}

	void Insert(T v)
	{
		root = Insert(v, root);
	}

	void Remove(T v)
	{
		root = Remove(v, root);
	}

	void Display()
	{
		InOrder(root);
		std::cout << std::endl;
	}
};

//
//int main()
//{
//	//AVLTree<int> t;
//	//t.Insert(20);
//	//t.Insert(25);
//	//t.Insert(15);
//	//t.Insert(10);
//	//t.Insert(30);
//	//t.Insert(5);
//	//t.Insert(35);
//	//t.Insert(67);
//	//t.Insert(43);
//	//t.Insert(21);
//	//t.Insert(10);
//	//t.Insert(89);
//	//t.Insert(38);
//	//t.Insert(69);
//	//t.Display();
//
//	//t.Remove(35);
//	//t.Remove(38);
//	//t.Display();
//
//	unsigned long long res = pow(2, 3);
//	unsigned long long res2 = log(8) / log(2);
//	std::cout << res << std::endl << res2 << std::endl;
//
//	std::cin.ignore();
//	std::cin.get();
//	return 0;
//}
