#include <iostream>
using namespace std;
#include "Status.h"
#include "Node.h"
#include "LinkQueue.h"
#include "BTNode.h"
#include "BinaryTree.h"

template <class DataType>
void Display(const DataType & e)
{    cout << e << " ";    }

//（1）根据二叉树的先序遍历序列建立二叉树。
//例如：根据先序遍历序列ABDG#L##HM###EIN##O###C#FJ##K##建立二叉树，其中，#表示空树。
int main(void)
{
	BinaryTree<char> tree;
	//---------------------以下测试第1小题函数--------------------------------------------
	cout << "Please enter the preorder sequence of a binary tree, # is null pointer(ABDG#L##HM###EIN##O###C#FJ##K##):" << endl;
	tree.CreateBinaryTree();////--------调用第1小题函数,输入：ABDG#L##HM###EIN##O###C#FJ##K##
	cout << "The preorder sequence of the binary tree is:" << endl;
	tree.PreOrder(Display);
	cout << endl;
	cout << "The inorder sequence of the binary tree is:" << endl;
	tree.InOrder(Display);
	cout << endl;
	cout << "The postorder sequence of the binary tree is:" << endl;
	tree.PostOrder(Display);
	cout << endl;
	cout << "The level order sequence of the binary tree is:" << endl;
	tree.LevelOrder(Display);
	cout << endl;

	system("pause");
	return 0;
}