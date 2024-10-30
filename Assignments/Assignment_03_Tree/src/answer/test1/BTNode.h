#pragma once
template <class DataType>
class BTNode {
public:
	DataType data;									//������
	BTNode<DataType> *lChild;						//����ָ����
	BTNode<DataType> *rChild; 						//�Һ���ָ����
	BTNode() { lChild = rChild = NULL; }			//�޲ι��캯��������սڵ�
	//�вι��캯������������Ԫ�ؽڵ�
	BTNode(DataType &e, BTNode<DataType> *leftChild = NULL, BTNode<DataType> *rightChild = NULL)
	{
		data = e;  lChild = leftChild;  rChild = rightChild;
	}
};
