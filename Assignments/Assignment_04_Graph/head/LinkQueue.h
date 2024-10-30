#pragma once
#include "Status.h"
#include "Node.h"			//����������ڵ����ͷ�ļ�
template<class DataType>
class LinkQueue
{
	Node<DataType> *front, *rear;					//��ͷ���βָ��
public:
	LinkQueue();									//���캯��
	virtual ~LinkQueue();							//��������
	int GetLength() const;							//����еĳ���
	bool IsEmpty() const;							//�ж϶����Ƿ�Ϊ��
	void Clear();									//��ն���
	Status EnQueue(const DataType &e);				//���
	Status DelQueue(DataType &e);					//����
	Status GetHead(DataType &e) const;				//ȡ��ͷԪ��
	void Traverse(void(*visit)(const DataType &)) const;	//��������Ԫ��
};

template<class DataType>
LinkQueue<DataType>::LinkQueue()					//����һ���յ�������
{
	rear = front = new Node<DataType>;
}

template <class DataType>
LinkQueue<DataType>::~LinkQueue()					//����һ��������
{
	Clear();										//�ͷ�����Ԫ�ؽڵ�
	delete front;									//�ͷ�ͷ�ڵ�
}

template<class DataType>
int LinkQueue<DataType>::GetLength() const			//�������еĳ���
{
	int count = 0;									//����������¼Ԫ�ؽڵ����Ŀ
	Node<DataType> *p = front->next;				//���帨��ָ��ָ���ͷ�ڵ�
	while (p)										//��������ͳ�ƽڵ���Ŀ
	{
		count++;	p = p->next;
	}
	return count;									//���ؽڵ���Ŀ��Ԫ�ظ�����
}

template<class DataType>
bool LinkQueue<DataType>::IsEmpty() const			//������Ϊ�շ���true�����򷵻�false
{
	return front == rear;
}

template<class DataType>
void LinkQueue<DataType>::Clear()					//���������
{
	Node<DataType> *p = front->next;				//���帨��ָ��ָ���һ��Ԫ�ؽڵ�
	while (p) {										//������ͷ����ʼ����ɾ���ڵ�
		front->next = p->next;						//�޸�ͷ�ڵ�ĺ��ָ��ָ���һ��Ԫ�ؽڵ�ĺ�̽ڵ�
		delete p;									//ɾ����һ��Ԫ�ؽڵ�
		p = front->next;							//����ָ��ָ��ǰ�ĵ�һ��Ԫ�ؽڵ�
	}
	rear = front;									//�޸Ķ�βָ��ָ��ͷ�ڵ�
}

template<class DataType>
Status LinkQueue<DataType>::EnQueue(const DataType &e)
{
	//�������һ���½ڵ�洢Ԫ��e 
	Node<DataType> *pNew = new Node<DataType>(e);
	if (!pNew)										//�жϽڵ��Ƿ����ʧ��
		return OVER_FLOW;							//�ڵ����ʧ�ܣ�����������Ϣ
	else {											//�ڵ����ɹ�
		rear->next = pNew;							//���ڵ�����βָ����ָ�ڵ�֮��
		rear = rear->next;							//�ƶ���βָ��ָ���½ڵ�
		return SUCCESS; 							//���سɹ���Ϣ
	}
}

template<class DataType>
Status LinkQueue<DataType>::DelQueue(DataType &e)	//�����ӳɹ�����e���ض�ͷԪ�ص�ֵ
{
	if (IsEmpty())									//�ж϶����Ƿ�Ϊ��
		return UNDER_FLOW;							//����Ϊ�գ�����������Ϣ
	else {											//���в�Ϊ��
		Node<DataType> *p = front->next;			//���帨��ָ��ָ��ǰ��ͷ�ڵ�
		e = p->data;								//��ȡ��ǰ��ͷԪ�ص�ֵ
		front->next = p->next;						//�޸�ͷ�ڵ��еĺ��ָ��
		if (rear == p)								//�ж϶����Ƿ�ֻ��һ��Ԫ��
			rear = front;							//ֻ��һ��Ԫ�أ��޸Ķ�βָ��ָ��ͷ�ڵ�
		delete p;									//ɾ��ԭ��ͷ�ڵ�
		return SUCCESS; 							//���سɹ���Ϣ
	}
}

template<class DataType>
Status LinkQueue<DataType>::GetHead(DataType &e) const	//��ȡ��ͷԪ�سɹ�����e���ض�ͷԪ�ص�ֵ
{
	if (IsEmpty())									//�ж϶����Ƿ�Ϊ��
		return UNDER_FLOW;							//����Ϊ�գ�����������Ϣ
	else {											//���в�Ϊ��
		e = front->next->data;						//��ȡ��һ��Ԫ�ؽڵ�������Ԫ�ص�ֵ
		return SUCCESS; 							//���سɹ���Ϣ
	}
}

template<class DataType>
void LinkQueue<DataType>::Traverse(void(*visit)(const DataType &)) const	//����������Ԫ��
{
	for (Node<DataType> *p = front->next; p; p = p->next)
		(*visit)(p->data);
}
