#pragma once
#include "Status.h"
const int DEFAULT_SIZE = 100;
template<class DataType>
class SqStack
{
	DataType *elems;								//Ԫ�ش洢�ռ�
	int maxSize;									//ջ������ 
	int top1, top2;									//ջ��ָ��
public:
	SqStack(int size = DEFAULT_SIZE);				//���캯��
	virtual ~SqStack();								//��������
	int GetLength(int id) const;							//��ջ�ĳ���
	bool IsEmpty(int id) const;						//�ж�ջ�Ƿ�Ϊ��
	void Clear();									//���ջ
	Status Push(int id, const DataType &e);			//��ջ
	Status Pop(int id, DataType &e);						//��ջ
	Status Top(int id, DataType &e) const;					//ȡջ��Ԫ��
	void Traverse(int id, void(*visit)(const DataType &)) const;	//����ջ��Ԫ��
};

template<class DataType>
SqStack<DataType>::SqStack(int size)		//����һ������Ϊsize�Ĺ���ջ
{	
	elems = new DataType[size];
	maxSize = size;
	top1 = -1;					//����ջ1
	top2 = size;				//����ջ2
}

template<class DataType>
SqStack<DataType>::~SqStack()			//����ջ
{
	delete[]elems;
}

template <class DataType>
int SqStack<DataType>::GetLength(int id) const		//����ջ��Ԫ�ظ���
{	
	if(id == 1) return (top1 + 1);
	return (maxSize - top2);
}

template<class DataType>
bool SqStack<DataType>::IsEmpty(int id) const		//ջΪ�շ���true�����򷵻�false
{
	if(id == 1){
		return top1 == -1;
	}
	return top2 == maxSize;
}

template<class DataType>
void SqStack<DataType>::Clear()				//��ջ��Ϊ��ջ
{
	top1 = -1;
	top2 = maxSize;
}

template<class DataType>
Status SqStack<DataType>::Push(int id, const DataType &e)
{
	if(id == 1){
		if (top1 + (maxSize - top2 + 1) == maxSize - 1)			//�ж�ջ1�Ƿ�����
			return OVER_FLOW;				//ջ����������������Ϣ
		else {								//ջδ��
			elems[++top1] = e;				//top+1��Ϊ�µ�ջ��λ�ã���Ԫ��e�����λ��
			return SUCCESS; 				//���سɹ���Ϣ
		}
	}
	else{
		if (top1 + (maxSize - top2 + 1) == maxSize - 1)				//�ж�ջ2�Ƿ�����
			return OVER_FLOW;				//ջ����������������Ϣ
		else {								//ջδ��
			elems[--top2] = e;				//top+1��Ϊ�µ�ջ��λ�ã���Ԫ��e�����λ��
			return SUCCESS; 				//���سɹ���Ϣ
		}
	}
}

template<class DataType>
Status SqStack<DataType>::Pop(int id, DataType &e)	//����ջ�ɹ�����e����ջ��Ԫ�ص�ֵ
{	
	if (id == 1){
			if (IsEmpty(id))					//�ж�ջ�Ƿ�Ϊ��
			return UNDER_FLOW;				//ջ�գ�����������Ϣ
		else {								//ջ��Ϊ��
			e = elems[top1--];				//��ȡ��ǰջ��Ԫ�ص�ֵ����ɾ����Ԫ��
			return SUCCESS; 				//���سɹ���Ϣ
		}
	}
	else{
		if (IsEmpty(id))					//�ж�ջ�Ƿ�Ϊ��
			return UNDER_FLOW;				//ջ�գ�����������Ϣ
		else {								//ջ��Ϊ��
			e = elems[top2++];				//��ȡ��ǰջ��Ԫ�ص�ֵ����ɾ����Ԫ��
			return SUCCESS; 				//���سɹ���Ϣ
		}
	}
}

template<class DataType>
Status SqStack<DataType>::Top(int id, DataType &e) const	//��ȡջ��Ԫ�سɹ�����e����ջ��Ԫ�ص�ֵ
{
	if (IsEmpty(id))						//�ж�ջ�Ƿ�Ϊ��
		return UNDER_FLOW;					//ջ�գ�����������Ϣ
	else {
		if(id == 1) e = elems[top1];			//ջ��Ϊ��
		else e = elems[top2];					//��ȡ��ǰջ��Ԫ�ص�ֵ
		return SUCCESS; 					//���سɹ���Ϣ
	}
}

template <class DataType>
void SqStack<DataType>::Traverse(int id, void(*visit)(const DataType &)) const		//����ջ�е�ÿ��Ԫ��
{	
	if(id ==1)
	{
		for (int i = top1; i >= 0; i--)
		(*visit)(elems[i]);
	}
	else
	{
		for (int i = top2; i <= maxSize-1; i++)
		(*visit)(elems[i]);
	}
}