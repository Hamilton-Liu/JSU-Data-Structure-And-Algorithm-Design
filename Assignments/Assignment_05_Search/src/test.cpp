#include <iostream>
using namespace std;
#include "Status.h"
#include "Node.h"
#include "LinkQueue.h"
#include "BTNode.h"
#include "BinaryTree.h"
#include "BinarySortTree.h"

template <class DataType>
void PrintNLT(BinarySortTree<DataType>& tree, BTNode<DataType>* node, const DataType& x);

template <class DataType>
void Display(const DataType e)
{    cout << e << " ";    }

int main(void)
{
	BinarySortTree<int> tree;
	int data;
	//建立二叉排序树
	cout << "Please enter 10 integers, ending with -1(39 11 68 46 75 23 71 8 86 34 -1):" << endl;//输入：39 11 68 46 75 23 71 8 86 34 -1
	cin >> data;
	while(data != -1)
	{
		tree.Insert(data);//-----------二叉排序树插入
		cin >> data;
	}
	//中序遍历二叉排序树
	cout << "The inorder sequence of the binary sorting tree is:" << endl;
	tree.InOrder(Display);//-----------二叉排序树中序遍历
	cout << endl;
	//查找
	cout << "Please enter the data to be searched(39):" << endl;
	cin >> data;//输入：39
	if(tree.Search(data))//-----------二叉排序树查找
		cout << "Search Successfully!" << endl;
	else
		cout << "Not Found!" << endl;	
	//插入
	cout << "Please enter the data to be inserted(55):" << endl;
	cin >> data;//输入：55
	if(tree.Insert(data))//-----------二叉排序树插入	
		cout << "Insert successfully!" << endl;
	else 
		cout << "Insert unsuccessfully!" << endl;
	cout << "The inorder sequence of the binary sorting tree is:" << endl;
	tree.InOrder(Display);
	cout << endl;
	//删除
	cout << "Please enter the data to be deleted(71):" << endl;
	cin >> data;//输入：71
	if (tree.Delete(data))//-----------二叉排序树删除
		cout << "Delete successfully!" << endl;
	else
		cout << "Delete unsuccessfully!" << endl;
	cout << "The inorder sequence of the binary sorting tree is:" << endl;
	tree.InOrder(Display);
	cout << endl;
	//从大到小输出关键字不小于x的数据元素
	cout << "Please enter a data as a boundary(34):" << endl;
	cin >> data;//输入：34
	cout << "Data greater than the boundary " << data << " include:" << endl;
	PrintNLT(tree, tree.GetRoot(), data);//-----------降序输出不小于data的所有元素
	cout << endl;

	system("pause");
	return 0;
}

template <class DataType>
void PrintNLT(BinarySortTree<DataType>& tree, BTNode<DataType>* node, const DataType& x) {
    // 如果当前节点为空，直接返回
    if (node == nullptr) return;

    // 先遍历右子树，因为我们需要从大到小
    PrintNLT(tree, node->rChild, x);

    // 如果当前节点的关键字不小于x，输出该节点的值
    if (node->data >= x) {
        cout << node->data << " ";
    }

    // 然后遍历左子树
    PrintNLT(tree, node->lChild, x);
}