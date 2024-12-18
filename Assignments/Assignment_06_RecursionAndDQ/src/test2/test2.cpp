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

//假设二叉树采用二叉链表存储节点，设计递归算法判断两棵二叉树是否同构（即形态相同）。
int main(void)
{
	BinaryTree<char> tree1, tree2, tree3;
	cout << "Please enter the preorder sequence of the first binary tree, # is null pointer(ABCD#E##FG###HIJ##K###L#MN##O##):" << endl;
	tree1.CreateBinaryTree();//输入：ABCD#E##FG###HIJ##K###L#MN##O##
	cout << "Please enter the preorder sequence of the second binary tree, # is null pointer(BCDE#F##GH###IJK##L###M#NO##P##):" << endl;
	tree2.CreateBinaryTree();//输入：BCDE#F##GH###IJK##L###M#NO##P##
	cout << "Please enter the preorder sequence of the third binary tree, # is null pointer(ABDG#L##HM###EIN##O###C#F#K##):" << endl;
	tree3.CreateBinaryTree();//输入：ABDG#L##HM###EIN##O###C#F#K##
	if(tree1.Isomorphism(tree2))//---------------------------------调用判断二叉树是否同构的函数
		cout << "The first and the second binary trees are isomorphic." << endl;
	else
		cout << "The first and the second binary trees are not isomorphic." << endl;
	if(tree1.Isomorphism(tree3))//---------------------------------调用判断二叉树是否同构的函数
		cout << "The first and the third binary trees are isomorphic." << endl;
	else
		cout << "The first and the third binary trees are not isomorphic." << endl;
	
	system("pause");
	return 0;
}