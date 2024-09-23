#pragma once
#include "Status.h"
const int DEFAULT_SIZE = 100;
template<class DataType>
class SqQueue
{
	DataType *elems;								//Ԫ�ش洢�ռ�
	int maxSize;									//���е����� 
	int front, rear;								//��ͷ���βָ��
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
	front = rear = 0;								//��ͷ����βָ���ʼ��Ϊ0
}

template <class DataType>
SqQueue<DataType>::~SqQueue()						//����һ������
{
	delete []elems;
}

template<class DataType>
int SqQueue<DataType>::GetLength() const			//����еĳ���
{
	return (rear - front + maxSize) % maxSize;		//���㲢���ض����е�Ԫ����Ŀ
}

template<class DataType>
bool SqQueue<DataType>::IsEmpty() const				//����Ϊ�շ���true�����򷵻�false
{
	return front == rear;
}

template<class DataType>
void SqQueue<DataType>::Clear()						//��ն���
{
	front = rear = 0;
}

template<class DataType>
Status SqQueue<DataType>::EnQueue(const DataType &e)
{
	if((rear + 1) % maxSize == front)					//�ж϶����Ƿ�����
		return OVER_FLOW;								//��������������������Ϣ
	else {												//����δ��
		elems[rear] = e;								//��e�����βָ��ָʾ��λ��
		rear = (rear + 1) % maxSize;					//��βָ�����1λ
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
	for (int i = front; i != rear; i = (i + 1) % maxSize)
		(*visit)(elems[i]);
}