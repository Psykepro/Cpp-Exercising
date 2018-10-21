#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H
#include <algorithm>
#include <queue>

namespace myDataStructures
{
	namespace RBTree
	{
		enum Color : unsigned char
		{
			RED,
			BLACK
		};

		template<typename T>
		struct Node
		{
			T data;
			unsigned char color;
			Node<T> *left, *right, *parent;

			explicit Node(T data) 
				: data(data), color(Color::RED), left(nullptr), right(nullptr), parent(nullptr)
			{
			}

			// check if node is left child of parent 
			bool IsOnLeft() { return this == parent->left; }

			// returns pointer to uncle 
			Node<T>* Uncle() {
				// If no parent or grandparent, then no uncle 
				if (parent == nullptr || parent->parent == nullptr)
					return nullptr;

				if (parent->IsOnLeft())
					// uncle on right 
					return parent->parent->right;
				else
					// uncle on left 
					return parent->parent->left;
			}

			// returns pointer to sibling 
			Node<T>* Sibling() {
				// sibling null if no parent 
				if (parent == nullptr)
					return nullptr;

				if (IsOnLeft())
					return parent->right;

				return parent->left;
			}

			bool HasRedChild() {
				return (left != nullptr && left->color == Color::RED) or
					(right != nullptr && right->color == Color::RED);
			}
		};

		template<typename T>
		class RBTree
		{
		private:
			Node<T>* root;
		protected:
			void LeftRotation(Node<T>* &n);
			void RightRotation(Node<T>* &n);
			void SetColor(Node<T>* &n, unsigned char newColor);
			void SwapValues(Node<T>* &u, Node<T>* &v);
			void FixInsertRBTree(Node<T>* &n);
			void InOrderBST(Node<T>* &n);
			void PreOrderBST(Node<T>* &n);
			void LevelOrder(Node<T>* &n);
			void FixDoubleBlack(Node<T>* &x);
			Node<T>* MinValueNode(Node<T>* &n);
			Node<T>* MaxValueNode(Node<T>* &n);
			Node<T>* InsertNode(Node<T>* &root, Node<T>* &n);
			Node<T>* Successor(Node<T>* n);
			Node<T>* BSTreplace(Node<T>* n);
			void DeleteNode(Node<T>* &v);
			unsigned char GetColor(Node<T>* &n) const;
			int GetBlackHeight(Node<T>* node);


		public:
			RBTree();
			void InsertValue(T data);
			void DeleteValue(T data);
			void InOrder();
			void PreOrder();
			void LevelOrder();
			Node<T>* Search(T data);
		};

		// Public Member Functions Implementations
		template<typename T>
		void RBTree<T>::InsertValue(T data)
		{
			Node<T>* newNode = new Node<T>(data);
			root = InsertNode(root, newNode);
			FixInsertRBTree(newNode);
		}

		template<typename T>
		void RBTree<T>::DeleteValue(T data)
		{
			if (root == nullptr)
				// Tree is empty 
				return;

			Node<T>* v = Search(data);

			if (v->data != data) {
				std::cout << "No node found to delete with value:" << data << std::endl;
				return;
			}

			DeleteNode(v);
		}

		template<typename T>
		void RBTree<T>::InOrder()
		{
			if (root == nullptr)
			{
				std::cout << "Tree is empty." << std::endl;
				return;
			}

			std::cout << "In Order:" << std::endl;
			InOrderBST(root);
			std::cout << '\n';
		}

		template<typename T>
		inline void RBTree<T>::PreOrder()
		{
			if (root == nullptr)
			{
				std::cout << "Tree is empty." << std::endl;
				return;
			}

			std::cout << "Pre Order:" << std::endl;
			PreOrderBST(root);
			std::cout << '\n';
		}

		template<typename T>
		void RBTree<T>::LevelOrder()
		{
			if (root == nullptr)
			{
				std::cout << "Tree is empty." << std::endl;
				return;
			}
				
			std::cout << "Level Order:" << std::endl;
			LevelOrder(root);
			std::cout << '\n';
		}

		template<typename T>
		Node<T>* RBTree<T>::Search(T data)
		{
			Node<T> *temp = root;
			while (temp != nullptr) {
				if (data < temp->data) {
					if (temp->left == nullptr)
						break;
					else
						temp = temp->left;
				}
				else if (data == temp->data) {
					break;
				}
				else {
					if (temp->right == nullptr)
						break;
					else
						temp = temp->right;
				}
			}

			return temp;
		}

		// Default Constructor 
		template<typename T>
		RBTree<T>::RBTree() 
			: root(nullptr)
		{
		}

		// Protected Member Functions Implementations

		template<typename T>
		void RBTree<T>::LeftRotation(Node<T>* &n)
		{
			Node<T>* rightChild = n->right;
			n->right = rightChild->left;
			
			if (n->right != nullptr)
				n->right->parent = n;


			if (n->parent == nullptr)
				root = rightChild;
			else if (n->parent->left == n)
				n->parent->left = rightChild;
			else
				n->parent->right = rightChild;

			rightChild->left = n;
			rightChild->parent = n->parent;
			n->parent = rightChild;
		}


		template<typename T>
		void RBTree<T>::RightRotation(Node<T>* &n)
		{
			Node<T>* leftChild = n->left;
			n->left = leftChild->right;

			if (n->left != nullptr)
				n->left->parent = n;

			if (n->parent == nullptr)
				root = leftChild;
			else if (n->parent->left == n)
				n->parent->left = leftChild;
			else
				n->parent->right = leftChild;

			leftChild->right = n;
			leftChild->parent = n->parent;
			n->parent = leftChild;
		}

		template<typename T>
		void RBTree<T>::SetColor(Node<T>*& n, unsigned char newColor)
		{
			if (n == nullptr)
				return;
			
			n->color = newColor;
		}

		template<typename T>
		void RBTree<T>::SwapValues(Node<T>* &u, Node<T>* &v)
		{
			T temp = u->data;
			u->data = v->data;
			v->data = temp;
		}

		template<typename T>
		Node<T>* RBTree<T>::MinValueNode(Node<T>* &n)
		{
			Node<T>* ptr = n;

			while (ptr->left != nullptr)
				ptr = ptr->left;

			return ptr;
		}

		template<typename T>
		Node<T>* RBTree<T>::MaxValueNode(Node<T>* &n)
		{
			Node<T>* ptr = n;

			while (ptr->right != nullptr)
				ptr = ptr->right;

			return ptr;
		}

		template<typename T>
		Node<T>* RBTree<T>::InsertNode(Node<T>*& root, Node<T>*& n)
		{
			if (root == nullptr)
				return n;

			if (n->data > root->data)
			{
				root->right = InsertNode(root->right, n);
				root->right->parent = root;
			}
			else if (n->data < root->data)
			{
				root->left = InsertNode(root->left, n);
				root->left->parent = root;
			}

			return root;
		}

		template<typename T>
		// find node that do not have a left child 
		// in the subtree of the given node 
		Node<T>* RBTree<T>::Successor(Node<T>* n)
		{
			Node<T>* temp = n;

			while (temp->left != nullptr)
				temp = temp->left;

			return temp;
		}


		template<typename T>
		// find node that replaces a deleted node in BST 
		Node<T>* RBTree<T>::BSTreplace(Node<T>* n)
		{
			// when node have 2 children 
			if (n->left != nullptr && n->right != nullptr)
				return Successor(n->right);

			// when leaf
			if (n->left == nullptr && n->right == nullptr)
				return nullptr;

			// when signle child
			if (n->left != nullptr)
				return n->left;
			else
				return n->right;
		}

		template<typename T>
		// deletes the given node 
		void RBTree<T>::DeleteNode(Node<T>* &v)
		{
			Node<T>* u = BSTreplace(v);
			// True when u and v are both black
			bool uvBlack = (GetColor(u) == Color::BLACK) && (GetColor(v) == Color::BLACK);
			Node<T>* parent = v->parent;

			if (u == nullptr)
			{
				// u is nullptr then v is leaf
				if (v == root)
				{
					// v is root, making root null 
					root = nullptr;
				}
				else
				{
					if (uvBlack)
					{
						// u and v are black and v is leaf, so fix double black at v
						FixDoubleBlack(v);
					}
					else
					{
						// u or v is red
						Node<T>* sibling = v->Sibling();
						if (sibling != nullptr && GetColor(v) == Color::BLACK)
						{
							// sibling is not null and v is black, make sibling red.
							sibling->color = Color::RED;
						}
					}

					// delete v from the tree
					if (v->IsOnLeft())
						parent->left = nullptr;
					else
						parent->right = nullptr;
				}

				delete (v);
				return;
			}

			if (v->left == nullptr || v->right == nullptr)
			{
				// v has one child
				if (v == root)
				{
					// v is root, assign the value of u to v, and delete u
					v->data = u->data;
					v->left = v->right = nullptr;
					delete (u);
				}
				else
				{
					// Detach v from tree and move u up
					if (v->IsOnLeft())
					{
						parent->left = u;
					}
					else
					{
						parent->right = u;
					}

					delete (v);
					u->parent = parent;

					if (uvBlack)
					{
						// u and v both black, fix double black at u
						FixDoubleBlack(u);
					}
					else
					{
						// u or v is red, color u black
						u->color = Color::BLACK;
					}
				}
				return;
			}

			// v has 2 children , swap values with successor and recurse
			SwapValues(u, v);
			DeleteNode(u);
		}

		template<typename T>
		void RBTree<T>::FixDoubleBlack(Node<T>* &x)
		{
			if (x == root)
			{
				// Reached root, so return
				return;
			}

			Node<T>* sibling = x->Sibling();
			Node<T>* parent = x->parent;

			if (sibling == nullptr)
			{
				// No sibling, double black pushed up
				FixDoubleBlack(parent);
			}
			else
			{
				if (GetColor(sibling) == Color::RED)
				{
					// Sibling Red
					parent->color = Color::RED;
					sibling->color = Color::BLACK;
					if (sibling->IsOnLeft())
					{
						// Left Case
						RightRotation(parent);
					}
					else
					{
						// Right Case
						LeftRotation(parent);
					}
					FixDoubleBlack(x);
				}
				else
				{
					// Sibling Black
					if (sibling->HasRedChild())
					{
						// Sibling has At least 1 red child
						if (GetColor(sibling->left) == Color::RED)
						{
							if (sibling->IsOnLeft())
							{
								// Left Left
								sibling->left->color = sibling->color;
								sibling->color = parent->color;
								RightRotation(parent);
							}
							else
							{
								// Right Left
								sibling->left->color = parent->color;
								RightRotation(sibling);
								LeftRotation(parent);
							}
						}
						else
						{
							if (sibling->IsOnLeft())
							{
								// Left Right
								sibling->right->color = parent->color;
								LeftRotation(sibling);
								RightRotation(parent);
							}
							else
							{
								// Right Right
								sibling->right->color = sibling->color;
								sibling->color = parent->color;
								LeftRotation(parent);
							}
						}

						parent->color = Color::BLACK;
					}
					else
					{
						// Sibling has 2 black children
						sibling->color = Color::RED;
						if (GetColor(parent) == Color::BLACK)
							// Double Black pushed up
							FixDoubleBlack(parent);
						else
							parent->color = Color::BLACK;
					}
				}
			}
		}


		template<typename T>
		inline unsigned char RBTree<T>::GetColor(Node<T>*& n) const
		{
			if (n == nullptr)
				return Color::BLACK;

			return n->color;
		}

		template<typename T>
		int RBTree<T>::GetBlackHeight(Node<T>* n)
		{
			int blackHeight = 0;
			while (n != nullptr)
			{
				if (GetColor(n) == Color::BLACK)
					blackHeight += 1;
				n = n->left;
			}

			return blackHeight;
		}

		template<typename T>
		void RBTree<T>::FixInsertRBTree(Node<T>* &n)
		{
			Node<T>* parent = nullptr;
			Node<T>* grandParent = nullptr;
			Node<T>* uncle = nullptr;

			while (n != root && GetColor(n) == Color::RED 
					&& GetColor(n->parent) == Color::RED)
			{
				parent = n->parent;
				grandParent = parent->parent;

				// Cases when Parent is Left Child of GrandParent
				if (parent == grandParent->left)
				{
					uncle = grandParent->right;
					// Subcase uncle is RED, so we make Color Shift
					if (GetColor(uncle) == Color::RED)
					{
						SetColor(grandParent, Color::RED);
						SetColor(parent, Color::BLACK);
						SetColor(uncle, Color::BLACK);
						n = grandParent;
					}
					// Subcase uncle is BLACK, so we make rotation
					else
					{
						if (n == parent->right)
						{
							// Left Rotation
							LeftRotation(parent);
							n = parent;
							parent = n->parent;
						}

						// Right Rotation
						RightRotation(grandParent);
						std::swap(parent->color, grandParent->color);
						n = parent;
					}

				}
				// Cases when Parent is Right Child of GrandParent
				else
				{
					uncle = grandParent->left;
					// Subcase uncle is RED, so we make Color Shift
					if (GetColor(uncle) == Color::RED)
					{
						SetColor(grandParent, Color::RED);
						SetColor(parent, Color::BLACK);
						SetColor(uncle, Color::BLACK);
						n = grandParent;
					}
					// Subcase uncle is BLACK, so we make rotation
					else
					{
						if (n == parent->left)
						{
							// Right Rotation
							RightRotation(parent);
							n = parent;
							parent = n->parent;
						}

						// Left Rotation
						LeftRotation(grandParent);
						std::swap(parent->color, grandParent->color);
						n = parent;
					}
				}
			}

			SetColor(root, Color::BLACK);
		}

		template<typename T>
		void RBTree<T>::InOrderBST(Node<T>*& n)
		{
			if (n == nullptr)
				return;

			InOrderBST(n->left);
			std::cout << n->data << " ";
			InOrderBST(n->right);
		}

		template<typename T>
		void RBTree<T>::PreOrderBST(Node<T>*& n)
		{
			if (n == nullptr)
				return;

			std::cout << n->data << " " << n->color << " | " << std::endl;
			PreOrderBST(n->left);
			PreOrderBST(n->right);
		}

		template<typename T>
		// prints level order for given node 
		void RBTree<T>::LevelOrder(Node<T>* &n) {
			if (n == nullptr)
				// return if node is null 
				return;

			// queue for level order 
			std::queue<Node<T>*> q;
			Node<T>* curr;

			// push n 
			q.push(n);

			while (!q.empty()) {
				// while q is not empty 
				// dequeue 
				curr = q.front();
				q.pop();

				// print node value 
				std::cout << curr->data << " ";

				// push children to queue 
				if (curr->left != nullptr)
					q.push(curr->left);
				if (curr->right != nullptr)
					q.push(curr->right);
			}
		}

	

		

	}
}
#endif