#pragma once
template <class DataType>
class BTNode {
public:
	DataType data;									//数据域
	BTNode<DataType> *lChild;						//左孩子指针域
	BTNode<DataType> *rChild; 						//右孩子指针域
	BTNode() { lChild = rChild = NULL; }			//无参构造函数，构造空节点
	//有参构造函数，构造数据元素节点
	BTNode(DataType &e, BTNode<DataType> *leftChild = NULL, BTNode<DataType> *rightChild = NULL)
	{
		data = e;  lChild = leftChild;  rChild = rightChild;
	}
};
