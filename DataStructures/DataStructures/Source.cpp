#include <iostream>
#include "AVLTree.h"
#include "RBTree.h"

template<typename T>
using MyAVLTree = myDataStructures::AVLTree::AVLTree<T>;

template<typename T>
using MyRBTree = myDataStructures::RBTree::RBTree<T>;


int main()
{

	//### Test AVL Tree - BEGIN ###
	//MyAVLTree<int> t;
	//t.Insert(20);
	//t.Insert(25);
	//t.Insert(15);
	//t.Insert(10);
	//t.Insert(30);
	//t.Insert(5);
	//t.Insert(35);
	//t.Insert(67);
	//t.Insert(43);
	//t.Insert(21);
	//t.Insert(10);
	//t.Insert(89);
	//t.Insert(38);
	//t.Insert(69);
	//t.Display();

	//t.Remove(35);
	//t.Remove(38);
	//t.Display();
	//### Test AVL Tree - END ###

	//### Test Red Black Tree - BEGIN ###
	//MyRBTree<int> rb;
	//rb.InsertValue(7);
	//rb.InsertValue(3);
	//rb.InsertValue(18);
	//rb.InsertValue(10);
	//rb.InsertValue(22);
	//rb.InsertValue(8);
	//rb.InsertValue(11);
	//rb.InsertValue(26);
	//rb.InsertValue(2);
	//rb.InsertValue(6);
	//rb.InsertValue(13);
	//rb.InOrder();
	//rb.LevelOrder();

	//std::cout << std::endl << "Deleting 18, 11, 3, 10, 22" << std::endl;

	//rb.DeleteValue(18);
	//rb.DeleteValue(11);
	//rb.DeleteValue(3);
	//rb.DeleteValue(10);
	//rb.DeleteValue(22);
	//rb.InOrder();
	//rb.LevelOrder();
	//### Test Red Black Tree - END ###

	std::cin.ignore();
	std::cin.get();
	return 0;
}
