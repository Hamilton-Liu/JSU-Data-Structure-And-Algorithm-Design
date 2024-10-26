#include <iostream>
using namespace std;
#include "Status.h"
#include "Node.h"
#include "LinkQueue.h"
#include "TreeNode.h"
#include "Tree.h"

template <class DataType>
void Display(const DataType & e)
{    cout << e << " ";    }

int main(void)
{
	Tree<char> tree;
	cout << "Please enter the preorder sequence of a tree, # is null pointer(ABE#FK#L###CG##DH#IM#N##J####):" << endl;
	tree.CreateTree();//输入：ABE#FK#L###CG##DH#IM#N##J####
	cout << "The preorder sequence of the tree is:" << endl;
	tree.PreOrder(Display);
	cout << endl;
	cout << "The postorder sequence of the tree is:" << endl;
	tree.PostOrder(Display);
	cout << endl;
	cout << "The level order sequence of the tree is:" << endl;
	tree.LevelOrder(Display);
	cout << endl;
	//---------------------以下测试第1小题函数--------------------------------------------
	cout << "The height of the tree is: " << tree.Height() << endl;//--------调用第1小题函数
	//---------------------以下测试第2题函数----------------------------------------------------------------
	cout << "The degree of the tree is: " << tree.Degree() << endl;//----------调用第2小题函数

	system("pause");
	return 0;
}