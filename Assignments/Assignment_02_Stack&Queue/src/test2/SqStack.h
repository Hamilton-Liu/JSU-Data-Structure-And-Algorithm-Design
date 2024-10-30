#pragma once
#include "Status.h"
const int DEFAULT_SIZE = 100;
template<class DataType>
class SqStack
{
	DataType *elems;								//Ԫ�ش洢�ռ�
public:
	int maxSize;									//ջ������ 
	int top;										//ջ��ָ��
	SqStack(int size = DEFAULT_SIZE);				//���캯��
	virtual ~SqStack();								//��������
	int GetLength() const;							//��ջ�ĳ���
	bool IsEmpty() const;							//�ж�ջ�Ƿ�Ϊ��
	void Clear();									//���ջ
	Status Push(const DataType &e);					//��ջ
	Status Pop(DataType &e);						//��ջ
	Status Top(DataType &e) const;					//ȡջ��Ԫ��
	void Traverse(void(*visit)(const DataType &)) const;	//����ջ��Ԫ��
};

template<class DataType>
SqStack<DataType>::SqStack(int size)		//����һ������Ϊsize�Ŀ�ջ
{
	elems = new DataType[size];
	maxSize = size;
	top = -1;
}

template<class DataType>
SqStack<DataType>::~SqStack()			//����ջ
{
	delete[]elems;
}

template <class DataType>
int SqStack<DataType>::GetLength() const		//����ջ��Ԫ�ظ���
{
	return top + 1;
}

template<class DataType>
bool SqStack<DataType>::IsEmpty() const		//ջΪ�շ���true�����򷵻�false
{
	return top == -1;
}

template<class DataType>
void SqStack<DataType>::Clear()				//��ջ��Ϊ��ջ
{
	top = -1;
}

template<class DataType>
Status SqStack<DataType>::Push(const DataType &e)
{
	if (top == maxSize - 1)				//�ж�ջ�Ƿ�����
		return OVER_FLOW;				//ջ����������������Ϣ
	else {								//ջδ��
		elems[++top] = e;				//top+1��Ϊ�µ�ջ��λ�ã���Ԫ��e�����λ��
		return SUCCESS; 				//���سɹ���Ϣ
	}
}

template<class DataType>
Status SqStack<DataType>::Pop(DataType &e)	//����ջ�ɹ�����e����ջ��Ԫ�ص�ֵ
{
	if (IsEmpty())						//�ж�ջ�Ƿ�Ϊ��
		return UNDER_FLOW;				//ջ�գ�����������Ϣ
	else {								//ջ��Ϊ��
		e = elems[top--];				//��ȡ��ǰջ��Ԫ�ص�ֵ����ɾ����Ԫ��
		return SUCCESS; 				//���سɹ���Ϣ
	}
}

template<class DataType>
Status SqStack<DataType>::Top(DataType &e) const	//��ȡջ��Ԫ�سɹ�����e����ջ��Ԫ�ص�ֵ
{
	if (IsEmpty())							//�ж�ջ�Ƿ�Ϊ��
		return UNDER_FLOW;				//ջ�գ�����������Ϣ
	else {									//ջ��Ϊ��
		e = elems[top];						//��ȡ��ǰջ��Ԫ�ص�ֵ
		return SUCCESS; 					//���سɹ���Ϣ
	}
}

template <class DataType>
void SqStack<DataType>::Traverse(void(*visit)(const DataType &)) const		//����ջ�е�ÿ��Ԫ��
{
	for (int i = top; i >= 0; i--)
		(*visit)(elems[i]);
}

