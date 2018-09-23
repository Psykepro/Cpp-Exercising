#ifndef AVL_TREE_H
#define AVL_TREE_H


namespace myDataStructures
{
	namespace AVLTree
	{
		template<typename T>
		struct Node
		{
			Node(T key) : key(key)
			{

			}
			T key;
			Node<T>* left;
			Node<T>* right;
			unsigned char height; // It is pretty legal to use 1 byte. Because of the fact that to overflow the limit of byte the height must be over than 255. 
								  // Which means to have more keys than - 57896044618658097711785492504343953926634992332820282019728792003956564819968.
		};

		template<typename T>
		class AVLTree
		{
		private:
			Node<T>* root;

		protected:

			unsigned char Height(Node<T>* n);
			int BalanceFactor(Node<T>* n);
			void FixHeight(Node<T>* n);
			Node<T>* Balance(Node<T>* n);
			Node<T>* RightRotation(Node<T>* &n);
			Node<T>* LeftRotation(Node<T>* &n);
			Node<T>* Insert(T v, Node<T>* n);
			Node<T>* Remove(T v, Node<T>* n);
			Node<T>* FindMin(Node<T>* n);
			Node<T>* FindMax(Node<T>* n);
			void* PopMax(Node<T>* n);
			void Clear(Node<T>* n);
			void InOrder(Node<T>* n);

		public:

			AVLTree();
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
		unsigned char AVLTree<T>::Height(Node<T>* n)
		{
			return n ? n->height : 0;
		}

		template<typename T>
		int AVLTree<T>::BalanceFactor(Node<T>* n)
		{
			if (n == nullptr)
				return 0;

			return Height(n->left) - Height(n->right);
		}

		template<typename T>
		void AVLTree<T>::FixHeight(Node<T>* n)
		{
			n->height = (Height(n->left) > Height(n->right) ? Height(n->left) : Height(n->right)) + 1;
		}

		template<typename T>
		Node<T>* AVLTree<T>::Balance(Node<T>* n)
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
		Node<T>* AVLTree<T>::RightRotation(Node<T>* &n)
		{
			Node<T>* l = n->left;
			n->left = l->right;
			l->right = n;
			FixHeight(n);
			FixHeight(l);
			return l;
		}

		template<typename T>
		Node<T>* AVLTree<T>::LeftRotation(Node<T>* &n)
		{
			Node<T>* r = n->right;
			n->right = r->left;
			r->left = n;
			FixHeight(n);
			FixHeight(r);
			return r;
		}

		template<typename T>
		Node<T>* AVLTree<T>::Insert(T v, Node<T>* n)
		{
			if (n == nullptr)
			{
				return new Node<T>(v);
			}

			if (v < n->key)
				n->left = Insert(v, n->left);
			else if (v > n->key)
				n->right = Insert(v, n->right);

			return Balance(n);
		}

		template<typename T>
		Node<T>* AVLTree<T>::FindMin(Node<T>* n)
		{
			return n->left ? FindMin(n->left) : n;
		}

		template<typename T>
		Node<T>* AVLTree<T>::FindMax(Node<T>* n)
		{
			return n->Right ? FindMax(n->right) : n;
		}

		template<typename T>
		void* AVLTree<T>::PopMax(Node<T>* n)
		{
			Node<T>* max = FindMax(n);
			void* key = max->key;
			Remove(n, key);
			return key;
		}

		template<typename T>
		Node<T>* AVLTree<T>::Remove(T v, Node<T>* n)
		{
			Node<T>* temp;

			// Element not found
			if (n == nullptr)
				return nullptr;

			// Searching for element
			if (v < n->key)
				n->left = Remove(v, n->left);
			else if (v > n->key)
				n->right = Remove(v, n->right);

			// Element found
			// With 2 children
			else if (n->left && n->right)
			{
				temp = FindMin(n->right);
				n->key = temp->key;
				n->right = Remove(n->key, n->right);
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
		void AVLTree<T>::Clear(Node<T>* n)
		{
			if (n == nullptr)
				return;

			Clear(n->left);
			Clear(n->right);
			delete n;
		}

		template<typename T>
		void AVLTree<T>::InOrder(Node<T>* n)
		{
			if (!n)
				return;

			InOrder(n->left);
			std::cout << n->key << " ";
			InOrder(n->right);

		}

		////////////////////////
		// Public Definitions //
		////////////////////////

		template<typename T>
		AVLTree<T>::AVLTree()
		{
			root = nullptr;
		}

		template<typename T>
		AVLTree<T>::~AVLTree()
		{
			Clear(root);
		}

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
	}
}

#endif