#pragma once
#include "Status.h"
#include  "Node.h"			//����������ڵ����ͷ�ļ�
template<class DataType>
class LinkStack
{
	Node<DataType> *top;							//ջ��ָ��
public:
	LinkStack();									//���캯��
	virtual ~LinkStack();							//��������
	int GetLength() const;							//��ջ�ĳ���
	bool IsEmpty() const;							//�ж�ջ�Ƿ�Ϊ��
	void Clear();									//���ջ
	Status Push(const DataType &e);					//��ջ
	Status Pop(DataType &e);						//��ջ
	Status Top(DataType &e) const;					//ȡջ��Ԫ��
	void Traverse(void(*visit)(const DataType &)) const;	//����ջ��Ԫ��
};

template<class DataType>
LinkStack<DataType>::LinkStack()		//����һ����ջ
{
	top = NULL;
}

template<class DataType>
LinkStack<DataType>::~LinkStack()		//����ջ
{
	Clear();							//ͨ���������ջ�����ﵽɾ�������Ŀ��
}					

template <class DataType>
int LinkStack<DataType>::GetLength() const	//����ջ��Ԫ�ظ���
{
	int count = 0��						//����������¼Ԫ�ؽڵ����Ŀ
		Node<DataType> *p = top;		//���帨��ָ��ָ��ջ���ڵ�
	while (p)							//��������ͳ�ƽڵ���Ŀ
	{
		count++;	p = p->next;
	}
	return count;						//���ؽڵ���Ŀ��Ԫ�ظ�����
}

template<class DataType>
bool LinkStack<DataType>::IsEmpty() const	//ջΪ�շ���true�����򷵻�false
{
	return top == NULL;
}

template<class DataType>
void LinkStack<DataType>::Clear()		//��ջ��Ϊ��ջ
{
	Node<DataType> *p = top;			//���帨��ָ������ɾ�������еĽڵ�
	while (p) {							//������ͷ����ʼ����ɾ���ڵ�
		top = top->next;				//ջ��ָ��ָ������ڵ㣬ʹ�����ڵ��Ϊ��ջ��
		delete p;						//ɾ��ԭջ���ڵ�
		p = top;						//����ָ��ָ����ջ���ڵ�
	}
}

template<class DataType>
Status LinkStack<DataType>::Push(const DataType &e)
{
	//�������һ���½ڵ�洢Ԫ��e������������ͷ��
	Node<DataType> *pNew = new Node<DataType>(e, top);
	if (!pNew)								//�жϽڵ��Ƿ����ʧ��
		return OVER_FLOW;					//�ڵ����ʧ�ܣ�����������Ϣ
	else {									//�ڵ����ɹ�
		top = pNew;							//ջ��ָ��ָ���½ڵ� 
		return SUCCESS; 					//���سɹ���Ϣ
	}
}

template<class DataType>
Status LinkStack<DataType>::Pop(DataType &e)	//����ջ�ɹ�����e����ջ��Ԫ�ص�ֵ
{
	if (IsEmpty())						//�ж�ջ�Ƿ�Ϊ��
		return UNDER_FLOW;				//ջ�գ�����������Ϣ
	else {								//ջ��Ϊ��
		Node<DataType> *p = top;		//���帨��ָ��ָ��ǰջ���ڵ�
		e = top->data;					//��ȡ��ǰջ��Ԫ�ص�ֵ
		top = top->next;	delete p;	//topָ����ջ���ڵ㣬ɾ����ջ���ڵ�
		return SUCCESS; 				//���سɹ���Ϣ
	}
}

template<class DataType>
Status LinkStack<DataType>::Top(DataType &e) const	//��ȡջ��Ԫ�سɹ�����e����ջ��Ԫ�ص�ֵ
{
	if (IsEmpty())							//�ж�ջ�Ƿ�Ϊ��
		return UNDER_FLOW;					//ջ�գ�����������Ϣ
	else {									//ջ��Ϊ��
		e = top->data;						//��ȡ��ǰջ��Ԫ�ص�ֵ
		return SUCCESS; 					//���سɹ���Ϣ
	}
}

template <class DataType>
void LinkStack<DataType>::Traverse(void(*visit)(const DataType &)) const		//����ջ�е�ÿ��Ԫ��
{
	Node<DataType> *p = top;				//���帨��ָ��ָ��ջ���ڵ�
	while (p) {								//��ջ���ڵ㿪ʼ���η��ʽڵ�
		(*visit)(p->data);					//���ʽڵ�Ԫ��
		p = p->next;						//ָ������ڵ�
	}
}