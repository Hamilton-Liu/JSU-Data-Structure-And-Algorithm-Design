#pragma once
#include "Status.h"
#include "Node.h"
template<class DataType>
class LinkList {
protected:
	Node<DataType> *head;								//������ͷָ��
	int length;											//������
public:
	LinkList();											//���캯�������������
	LinkList(DataType a[], int n);						//���캯����������Ԫ�ص�����
	virtual ~LinkList();								//��������
	void Clear();										//��յ�����
	int GetLength() const;								//������ĳ���
	bool IsEmpty() const;								//�жϵ������Ƿ�Ϊ�ձ�
	int LocateElem(const DataType &e);					//����Ԫ��
	Status GetElem(int i, DataType &e);					//ȡԪ��
	Status SetElem(int i, DataType &e);					//�޸�Ԫ��
	Status InsertElem(int i, DataType &e);				//����Ԫ��
	Status DeleteElem(int i, DataType &e);				//ɾ��Ԫ��
	void Traverse(void(*visit)(const DataType &)) const;	//����������
};

template<class DataType>
LinkList<DataType>::LinkList() {  						//����һ��ֻ����ͷ�ڵ�Ŀ�����
	head = new Node<DataType>;							//����ͷ�ڵ�
	length = 0;											//��Ϊ0
}

template<class DataType>
LinkList<DataType>::LinkList(DataType a[], int n) {  	//���캯��������һ���ǿ�����
	Node<DataType> *p;									//ָ�������β�ڵ��ָ�����
	p = head = new Node<DataType>;    					//����ͷ�ڵ�
	for(int i = 0; i < n; i++) {
		p->next = new Node<DataType>(a[i]); 			//����Ԫ�ؽڵ㣬������Ϊa[i]��ָ����ΪNULL
		p = p->next; 									//p����ָ��ǰ��β�ڵ�
	}
	length = n;
}

template <class DataType>
LinkList<DataType>::~LinkList() {
	Clear();											//ɾ������Ԫ�ؽڵ�
	delete head;										//ɾ��ͷ�ڵ�
	head = NULL;
}

template<class DataType>
void LinkList<DataType>::Clear() {						//�������
	Node<DataType> *p = head->next;   					//pָ���һ��Ԫ�ؽڵ�
	while(p) {  										//ѭ���ͷ�ÿ���ڵ�
		head->next = p->next;    						//�޸�ͷ�ڵ�ĺ��ָ��ָ���ɾ�ڵ�ĺ��
		delete p;										//�ͷŵ�һ��Ԫ�ؽڵ�
		p = head->next;									//p����ָ������ǰ�ĵ�һ��Ԫ�ؽڵ�
	}
	length = 0;
}

template<class DataType>
int LinkList<DataType>::GetLength() const 				//������ĳ���
{
	return length;
}

template<class DataType>
bool LinkList<DataType>::IsEmpty() const
{
	return length ? false : true;
}

template <class DataType>
int LinkList<DataType>::LocateElem(const DataType &e) {
	Node<DataType> *p = head->next;  					//pָ���һ��Ԫ�ؽڵ�
	int count = 1;
	while(p != NULL && p->data != e) {					//�ӵ�һ��Ԫ�ؽڵ㿪ʼ���ν��бȽ�Ԫ�ص�ֵ
		p = p->next;									//�ƶ�ָ��pʹָ֮���̽ڵ�
		count++;										//�������ۼ�
	}
	return p ? count : 0;								//�ҵ�Ԫ��ֵ����e������count��ֵ�����򷵻�0
}

template<class DataType>
Status LinkList<DataType>::GetElem(int i, DataType &e) {	//ȡԪ��
	if(i < 1 || i > length) return INVALID;				//���λ��ȡֵ��Ч��������Ч��Ϣ
	Node<DataType> *p = head->next;   					//pָ���һ��Ԫ�ؽڵ�
	int count;											//����������¼pָ��ڼ���Ԫ�ؽڵ�
	for(count = 1; count < i; count++)   				//����pʹָ֮���i��Ԫ�ؽڵ�
		p = p->next;
	e = p->data;										//���������ֵ������e��
	return SUCCESS;
}

template <class DataType>
Status LinkList<DataType>::SetElem(int i, DataType &e) {
	if(i < 1 || i > length)	 return INVALID;			//���λ��ȡֵ��Ч��������Ч��Ϣ
	Node<DataType> *p = head->next;   					//pָ���һ��Ԫ�ؽڵ�
	int count;											//����������¼pָ��ڼ���Ԫ�ؽڵ�
	for(count = 1; count < i; count++)   				//����pʹָ֮���i��Ԫ�ؽڵ�
		p = p->next;
	p->data = e;										//�޸�������Ϊe
	return SUCCESS;
}

template <class DataType>
Status LinkList<DataType>::InsertElem(int i, DataType &e) {	//����Ԫ��
	if(i < 1 || i > length + 1)   return INVALID;
	Node<DataType> *p = head, *q;						//p��ʼָ��ͷ�ڵ㣬����1��Ԫ�ؽڵ��ǰ��
	int count;											//����������¼pָ��ڼ���Ԫ�ؽڵ��ǰ��
	for(count = 1; count < i; count++)					//�ƶ�ָ��p��ʹ��pָ�����λ�õ�ǰ��
		p = p->next;
	q = new Node<DataType>(e, p->next);					//����һ���½ڵ㣬nextָ��ԭ���ĵ�i��Ԫ�ؽڵ�
	if (!q)   return ALLOCATE_ERROR;					//�ڵ㴴��ʧ�ܣ����ط��䲻�ɹ���Ϣ��
	p->next = q;										//�޸�ǰ���ڵ�ĺ��ָ��ָ���½ڵ�
	length++;
	return SUCCESS;
}

template <class DataType>
Status LinkList<DataType>::DeleteElem(int i, DataType &e) {	//ɾ����i��Ԫ�أ�ͨ��e��������������
	if(i < 1 || i > length)   return INVALID;
	Node<DataType> *p = head, *q;						//p��ʼָ��ͷ�ڵ㣬����1��Ԫ�ؽڵ��ǰ��
	int count;											//����������¼pָ��ڼ���Ԫ�ؽڵ��ǰ��
	for(count = 1; count < i; count++)	 				//�ƶ�ָ��p��ʹ��ָ���ɾ�ڵ��ǰ��
		p = p->next;
	q = p->next;	     								//��ȡ��ɾ���ڵ�
	p->next = q->next; 	 								//�޸�ǰ���ڵ�ĺ��ָ�룬ָ���ɾ�ڵ�ĺ��
	e = q->data;										//���汻ɾ�ڵ������ֵ
	delete q;											//�ͷŽڵ���ռ�Ĵ洢��Ԫ
	length--;
	return SUCCESS;
}

template <class DataType>
void LinkList<DataType>::Traverse(void(*visit)(const DataType &)) const {
	Node<DataType> *p = head->next;   					//pָ���һ��Ԫ�ؽڵ�
	while(p != NULL) {     								//ѭ������ÿһ��Ԫ�ؽڵ㣬ֱ��pΪ��ָ��
		(*visit)(p->data);  							//ͨ��visit���ú�����������Ԫ��
		p = p->next;									//����ָ��ָ����Ԫ�ؽڵ�
	}
}