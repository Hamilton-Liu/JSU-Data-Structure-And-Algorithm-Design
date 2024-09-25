#pragma once
#include "Status.h"
const int DEFAULT_SIZE = 100;
template<class DataType>
class SqQueue
{
	DataType *elems;								//Ԫ�ش洢�ռ�
	int maxSize;									//���е����� 
	int front;										//��ͷ���βָ��
	int length;
public:
	SqQueue(int size = DEFAULT_SIZE);				//���캯��
	virtual ~SqQueue();								//��������
	int GetLength() const;							//����еĳ���
	bool IsEmpty() const;							//�ж϶����Ƿ�Ϊ��
	void Clear();									//��ն���
	Status EnQueue(const DataType &e);				//���
	Status DelQueue(DataType &e);					//����
	Status GetHead(DataType &e) const;				//ȡ��ͷԪ��
	void Traverse(void(*visit)(const DataType &)) const;	//��������Ԫ��
};

template<class DataType>
SqQueue<DataType>::SqQueue(int size)				//����һ������Ϊsize�Ŀն���
{
	elems = new DataType[size];						
	maxSize = size;
	front = length = 0;								//��ͷ����βָ���ʼ��Ϊ0
}

template <class DataType>
SqQueue<DataType>::~SqQueue()						//����һ������
{
	delete []elems;
}

template<class DataType>
int SqQueue<DataType>::GetLength() const			//����еĳ���
{
	return length;	//���㲢���ض����е�Ԫ����Ŀ
}

template<class DataType>
bool SqQueue<DataType>::IsEmpty() const				//����Ϊ�շ���true�����򷵻�false
{
	return length == 0;
}

template<class DataType>
void SqQueue<DataType>::Clear()						//��ն���
{
	front = length = 0;
}

template<class DataType>
Status SqQueue<DataType>::EnQueue(const DataType &e)
{
	if(length == maxSize)								//�ж϶����Ƿ�����
		return OVER_FLOW;								//��������������������Ϣ
	else {												//����δ��
		elems[(front%maxSize+length)%maxSize] = e;				//��e�����βλ��	
		length++;										//���ȣ�1
		return SUCCESS;									//������ӳɹ���Ϣ
	}
}

template<class DataType>
Status SqQueue<DataType>::DelQueue(DataType &e)
{
	if(IsEmpty())										//�ж϶����Ƿ�Ϊ��
		return UNDER_FLOW;								//����Ϊ�գ�����������Ϣ
	else {												//���в�Ϊ��
		e = elems[front];								//��ȡ��ͷԪ�ص�ֵ
		front = (front + 1) % maxSize;					//��ͷָ�����1λ��ɾ����ͷԪ��
		length--;										//����-1
		return SUCCESS;									//���س��ӳɹ���Ϣ
	}	
}

template<class DataType>
Status SqQueue<DataType>::GetHead(DataType &e) const
{
	if(IsEmpty())										//�ж϶����Ƿ�Ϊ��
		return UNDER_FLOW;								//����Ϊ�գ�����������Ϣ
	else {												//���в�Ϊ��
		e = elems[front];								//��ȡ��ͷԪ�ص�ֵ
		return SUCCESS;									//���سɹ���Ϣ
	}
}

template<class DataType>
void SqQueue<DataType>::Traverse(void (*visit)(const DataType &)) const	//��������Ԫ��
{
	for (int i = front; i != front+length; i++)
		(*visit)(elems[i]);
}