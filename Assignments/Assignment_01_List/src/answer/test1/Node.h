#pragma once
template <class DataType>
class Node {
public:
	DataType data;									//������
	Node< DataType> *next;							//ָ����
	Node() { next = NULL; }							//�޲ι��캯���������ڹ���ͷ�ڵ�
	Node(DataType e, Node< DataType> *link = NULL) 	//�вι��캯������������Ԫ�ؽڵ�
	{
		data = e;	next = link;
	}
};