#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H
#include <algorithm>

namespace myDataStructures
{
	namespace RBTree
	{
		enum Color : unsigned char
		{
			RED,
			BLACK,
			DOUBLE_BLACK
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
			void FixInsertRBTree(Node<T>* &n);
			void FixDeleteRBTree(Node<T>* &n);
			void InOrderBST(Node<T>* &n);
			void PreOrderBST(Node<T>* &n);
			Node<T>* MinValueNode(Node<T>* &n);
			Node<T>* MaxValueNode(Node<T>* &n);
			Node<T>* InsertBST(Node<T>* &root, Node<T>* &n);
			Node<T>* DeleteBST(Node<T>* &n, T data);
			unsigned char GetColor(Node<T>* &n) const;
			int GetBlackHeight(Node<T>* node);


		public:
			RBTree();
			void InsertValue(T data);
			void DeleteValue(T data);
			void Merge(RBTree rbTree2);
			void InOrder();
			void PreOrder();

		};

		// Public Member Functions Implementations
		template<typename T>
		void RBTree<T>::InsertValue(T data)
		{
			Node<T>* newNode = new Node<T>(data);
			root = InsertBST(root, newNode);
			FixInsertRBTree(newNode);
		}

		template<typename T>
		void RBTree<T>::DeleteValue(T data)
		{
			Node<T> *node = DeleteBST(root, data);
			FixDeleteRBTree(node);
		}

		template<typename T>
		void RBTree<T>::Merge(RBTree rbTree2)
		{
			int temp;
			Node<T>* c, *temp_ptr;
			Node<T>* root1 = root;
			Node<T>* root2 = rbTree2.root;
			int initialblackheight1 = GetBlackHeight(root1);
			int initialblackheight2 = GetBlackHeight(root2);
			if (initialblackheight1 > initialblackheight2) {
				c = MaxValueNode(root1);
				temp = c->data;
				DeleteValue(c->data);
				root1 = root;
			}
			else if (initialblackheight2 > initialblackheight1) {
				c = MinValueNode(root2);
				temp = c->data;
				rbTree2.DeleteValue(c->data);
				root2 = rbTree2.root;
			}
			else {
				c = MinValueNode(root2);
				temp = c->data;
				rbTree2.DeleteValue(c->data);
				root2 = rbTree2.root;
				if (initialblackheight1 != GetBlackHeight(root2)) {
					rbTree2.InsertValue(c->data);
					root2 = rbTree2.root;
					c = MaxValueNode(root1);
					temp = c->data;
					DeleteValue(c->data);
					root1 = root;
				}
			}
			setColor(c, RED);
			int finalblackheight1 = GetBlackHeight(root1);
			int finalblackheight2 = GetBlackHeight(root2);
			if (finalblackheight1 == finalblackheight2) {
				c->left = root1;
				root1->parent = c;
				c->right = root2;
				root2->parent = c;
				setColor(c, BLACK);
				c->data = temp;
				root = c;
			}
			else if (finalblackheight2 > finalblackheight1) {
				Node<T>* ptr = root2;
				while (finalblackheight1 != GetBlackHeight(ptr)) {
					temp_ptr = ptr;
					ptr = ptr->left;
				}
				Node<T>* ptr_parent;
				if (ptr == nullptr)
					ptr_parent = temp_ptr;
				else
					ptr_parent = ptr->parent;
				c->left = root1;
				if (root1 != nullptr)
					root1->parent = c;
				c->right = ptr;
				if (ptr != nullptr)
					ptr->parent = c;
				ptr_parent->left = c;
				c->parent = ptr_parent;
				if (GetColor(ptr_parent) == RED) {
					FixInsertRBTree(c);
				}
				else if (GetColor(ptr) == RED) {
					FixInsertRBTree(ptr);
				}
				c->data = temp;
				root = root2;
			}
			else {
				Node<T>* ptr = root1;
				while (finalblackheight2 != GetBlackHeight(ptr)) {
					ptr = ptr->right;
				}
				Node<T>* ptr_parent = ptr->parent;
				c->right = root2;
				root2->parent = c;
				c->left = ptr;
				ptr->parent = c;
				ptr_parent->right = c;
				c->parent = ptr_parent;
				if (GetColor(ptr_parent) == RED) {
					FixInsertRBTree(c);
				}
				else if (GetColor(ptr) == RED) {
					FixInsertRBTree(ptr);
				}
				c->data = temp;
				root = root1;
			}
			return;
		}

		template<typename T>
		void RBTree<T>::InOrder()
		{
			InOrderBST(root);
		}

		template<typename T>
		inline void RBTree<T>::PreOrder()
		{
			PreOrderBST(root);
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
		inline Node<T>* RBTree<T>::InsertBST(Node<T>*& root, Node<T>*& n)
		{
			if (root == nullptr)
				return n;

			if (n->data > root->data)
			{
				root->right = InsertBST(root->right, n);
				root->right->parent = root;
			}
			else if (n->data < root->data)
			{
				root->left = InsertBST(root->left, n);
				root->left->parent = root;
			}

			return root;
		}

		template<typename T>
		Node<T>* RBTree<T>::DeleteBST(Node<T>* &n, T data)
		{
			if (n == nullptr)
				return n;

			if (n->data < data)
				return DeleteBST(n->right, data);
			else if (n->data > data)
				return DeleteBST(n->left, data);

			if (n->left == nullptr || n->right == nullptr)
				return n;

			Node<T>* temp = MinValueNode(n->right);
			root->data = temp->data;
			return DeleteBST(n->right, temp->data);
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
		void RBTree<T>::FixDeleteRBTree(Node<T>* &n)
		{
			if (n == nullptr)
				return;

			Node<T>* child = n->left != nullptr ? n->left : n->right;

			// Case if we delete root
			if (n == root)
			{
				delete (n);
				if (child == nullptr)
				{
					root = nullptr;
				}
				else
				{
					child->parent = nullptr;
					root = child;
				}

				SetColor(root, Color::BLACK);
				return;
			}

			// Case when the node to delete is RED or one of the children is RED
			if (GetColor(n) == Color::RED || GetColor(n->left) == Color::RED || GetColor(n->right) == Color::RED)
			{
				if (n == n->parent->left)
				{
					n->parent->left = child;
					if (child != nullptr)
						child->parent = n->parent;
					SetColor(child, Color::BLACK);
					delete (n);
				}
				else
				{
					n->parent->right = child;
					if (child != nullptr)
						child->parent = n->parent;
					SetColor(child, Color::BLACK);
					delete (n);
				}
			}
			// Cases when the node to delete is BLACK and his children are BLACK
			else
			{
				Node<T>* sibling = nullptr;
				Node<T>* parent = nullptr;
				Node<T>* ptr = n;
				SetColor(ptr, Color::DOUBLE_BLACK);
				while (ptr != root && GetColor(ptr) == Color::DOUBLE_BLACK)
				{
					parent = ptr->parent;
					// ptr is left child
					if (ptr == parent->left)
					{
						sibling = parent->right;
						// Case when sibling is RED
						if (GetColor(sibling) == Color::RED)
						{
							SetColor(sibling, Color::BLACK);
							SetColor(parent, Color::RED);
							LeftRotation(parent);
						}
						// Cases when sibling is BLACK
						else
						{
							// Subcase when children of sibling are BLACK
							if (GetColor(sibling->left) == Color::BLACK
								&& GetColor(sibling->right) == Color::BLACK)
							{
								SetColor(sibling, Color::RED);
								if (GetColor(parent) == Color::RED)
									SetColor(parent, Color::BLACK);
								else
									SetColor(parent, Color::DOUBLE_BLACK);
								ptr = parent;
							}
							// Subcase when at least one of the children of sibling is RED
							else
							{
								if (GetColor(sibling->right) == Color::BLACK)
								{
									SetColor(sibling->left, Color::BLACK);
									SetColor(sibling, Color::RED);
									RightRotation(sibling);
									sibling = parent->right;
								}
								SetColor(sibling, parent->color);
								SetColor(parent, Color::BLACK);
								SetColor(sibling->right, Color::BLACK);
								LeftRotation(parent);
								break;

							}
						}
					}
					// ptr is right child
					else
					{
						sibling = parent->left;
						// Case when sibling is RED
						if (GetColor(sibling) == Color::RED)
						{
							SetColor(sibling, Color::BLACK);
							SetColor(parent, Color::RED);
							RightRotation(parent);
						}
						// Cases when sibling is BLACK
						else
						{
							// Subcase when children of sibling are BLACK
							if (GetColor(sibling->left) == Color::BLACK
								&& GetColor(sibling->right) == Color::BLACK)
							{
								SetColor(sibling, Color::RED);
								if (GetColor(parent) == Color::RED)
									SetColor(parent, Color::BLACK);
								else
									SetColor(parent, Color::DOUBLE_BLACK);
								ptr = parent;
							}
							// Subcase when at least one of the children of sibling is RED
							else
							{
								if (GetColor(sibling->left) == Color::BLACK)
								{
									SetColor(sibling->right, Color::BLACK);
									SetColor(sibling, Color::RED);
									LeftRotation(sibling);
									sibling = parent->left;
								}
								SetColor(sibling, parent->color);
								SetColor(parent, Color::BLACK);
								SetColor(sibling->left, Color::BLACK);
								RightRotation(parent);
								break;
								
							}
						}	
					}
				}

				if (n == n->parent->left)
					n->parent->left = nullptr;
				else
					n->parent->right = nullptr;
				delete (n);

				SetColor(root, Color::BLACK);

			}
		}

		template<typename T>
		void RBTree<T>::InOrderBST(Node<T>*& n)
		{
			if (n == nullptr)
				return;

			InOrderBST(n->left);
			std::cout << n->data << " " << n->color << " | " << std::endl;
			InOrderBST(n->right);
		}

		template<typename T>
		void RBTree<T>::PreOrderBST(Node<T>*& n)
		{
			if (n == nullptr)
				return;

			std::cout << n->data << " " << n->color << " | " << std::endl;
			PreOrderBst(n->left);
			PreOrderBst(n->right);
		}

		

	}
}
#endif