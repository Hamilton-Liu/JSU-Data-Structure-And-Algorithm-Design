#pragma once
#include "Status.h"
const int DEFAULT_SIZE = 100;
template<class DataType>
class SqList {
protected:
	DataType *elems;										//ָ��̬���������
	int maxSize;											//˳�������� 
	int length;												//˳���ĳ���
public:
	SqList(int size = DEFAULT_SIZE);						//���캯��
	virtual ~SqList();										//��������
	int GetLength() const;									//��˳���ĳ���
	int GetMaxSize() const;									//��˳��������
	bool IsEmpty() const;									//�ж�˳����Ƿ�ձ�
	void Clear();											//���˳���
	int LocateElem(DataType &e);							//����Ԫ��
	Status GetElem(int i, DataType &e);						//ȡԪ��
	Status SetElem(int i, DataType &e);						//�޸�Ԫ��
	Status InsertElem(int i, DataType &e);					//����Ԫ��
	Status DeleteElem(int i, DataType &e);					//ɾ��Ԫ��
	void Traverse(void(*visit)(const DataType &)) const;	//����˳���
	SqList(const SqList<DataType> &sa);						//�������캯��
	SqList<DataType> &operator =(const SqList<DataType> &sa);//��ֵ���������
	//ʵ��-1.1
	Status DelMinElem(DataType &e);							//ɾ����СԪ��
};

template<class DataType>
SqList<DataType>::SqList(int size) {   //����һ������Ϊsize��˳���
	elems = new DataType[size];
	maxSize = size;
	length = 0;
}

template<class DataType>
SqList<DataType>::~SqList() 	   //����˳���
{
	delete[]elems;
}

template<class DataType>
int SqList<DataType>::GetLength() const
{
	return length;
}

template<class DataType>
int SqList<DataType>::GetMaxSize() const	//��˳��������
{
	return maxSize;
}

template<class DataType>
bool SqList<DataType>::IsEmpty() const
{
	return length ? false : true;
}

template<class DataType>
void SqList<DataType>::Clear()
{
	length = 0;
}

template<class DataType>
int SqList<DataType>::LocateElem(DataType &e) {
	int i = 0;
	while (i < length) {
		if (elems[i] == e) return i + 1;		//Ԫ��ֵ��ȣ��򷵻�λ�򣬼���ǰ�±�+1
		else i++;								//������ȣ���������Ѱ��
	}
	return 0;									//˳���û����e��ȵ�����Ԫ�أ�����0
}

template<class DataType>
Status SqList<DataType>::GetElem(int i, DataType &e) {
	if (i <1 || i > length) return INVALID;					//���λ�򳬳���Χ��������Ч��Ϣ
	e = elems[i - 1];										//��Ҫ����Ԫ�ر�����e��
	return SUCCESS;
}

template<class DataType>
Status SqList<DataType>::SetElem(int i, DataType &e) {
	if (i <1 || i > length) return INVALID;					//���λ�򳬳���Χ��������Ч��Ϣ
	elems[i - 1] = e;										//�޸�����Ԫ�ص�ֵ���ڸ���ֵe
	return SUCCESS;
}

template<class DataType>
Status SqList<DataType>::InsertElem(int i, DataType &e) {
	if (length == maxSize)  return OVER_FLOW;					//��������������������Ϣ
	if (i <1 || i > length + 1)  return INVALID;				//���λ�򳬳���Χ��������Ч��Ϣ
	for (int j = length - 1; j >= i - 1; j--)					//�ƶ�Ԫ��
		elems[j + 1] = elems[j];
	elems[i - 1] = e;											//��e���뵱ǰλ��
	length++;													//����1
	return SUCCESS;												//���ز���ɹ���Ϣ
}

template<class DataType>
Status SqList<DataType>::DeleteElem(int i, DataType &e) {
	if (length == 0) return UNDER_FLOW;							//����ǿձ�����������Ϣ
	if (i <1 || i > length) return INVALID;						//���λ�򳬳���Χ��������Ч��Ϣ
	e = elems[i - 1];											//��Ҫɾ��������Ԫ�ر�����e��
	for (int j = i; j <= length - 1; j++)						//�ƶ�Ԫ��
		elems[j - 1] = elems[j];
	length--;													//����1
	return SUCCESS;
}

template<class DataType>
void SqList<DataType>::Traverse(void(*visit)(const DataType &)) const {  //����˳����е�ÿ��Ԫ��
	for (int i = 1; i <= length; i++)
		(*visit)(elems[i - 1]);									//����visitָ��ĺ��������η�������Ԫ��
}

template <class DataType>
SqList<DataType>::SqList(const SqList<DataType> & sa) {
	elems = new DataType[sa.maxSize];
	maxSize = sa.maxSize;
	length = sa.length;
	for (int i = 0; i < length; i++)
		elems[i] = sa.elems[i];
}

template <class DataType>
SqList<DataType>&  SqList<DataType>::operator=(const SqList<DataType> & sa) {
	if(this == &sa)	return *this;
	if(elems)	delete[]elems;
	elems = new DataType[sa.maxSize];
	maxSize = sa.maxSize;    length = sa.length;
	for (int i = 0; i < length; i++)    elems[i] = sa.elems[i];
	return *this;
}

//ʵ��-1.1
template <class DataType>
Status SqList<DataType>::DelMinElem(DataType &e) {
	if (length == 0) return UNDER_FLOW;							//����ǿձ�����������Ϣ
	e = elems[0];												//����Ҫɾ����������Ϣ�����e��
	int flag = 0;												//�����Ǳ����������Сֵ���±�
	for (int i = 1 ; i <= length; i++){
		if (elems[i] < elems[i-1]){
			e = elems[i];
			flag = i;
		}
	}
	elems[flag] = elems[length];
	length--;
}