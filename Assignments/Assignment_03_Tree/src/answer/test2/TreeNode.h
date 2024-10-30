#pragma once
template <class DataType>
class TreeNode {
public:
	DataType data;									//������
	TreeNode<DataType> *Child;						//����ָ����
	TreeNode<DataType> *Brother; 						//�Һ���ָ����
	TreeNode() { Child = Brother = NULL; }			//�޲ι��캯��������սڵ�
	//�вι��캯������������Ԫ�ؽڵ�
	TreeNode(DataType &e, TreeNode<DataType> *child = NULL, TreeNode<DataType> *brother = NULL)
	{
		data = e;  Child = child;  Brother = brother;
	}
};