#pragma once
#include "BTNode.h"
template <class DataType>
class BinaryTree {
protected:
	BTNode<DataType> *root; ;   											//���������ڵ�
	void Destroy(BTNode<DataType> * &r);									//ɾ����rΪ���Ķ�����
	void PreOrder(BTNode<DataType> *r, void(*visit)(const DataType &));		//���������rΪ���Ķ�����
	void InOrder(BTNode<DataType> *r, void(*visit)(const DataType &));		//���������rΪ���Ķ�����
	void PostOrder(BTNode<DataType> *r, void(*visit)(const DataType &));	//���������rΪ���Ķ�����
	void LevelOrder(BTNode<DataType> *r, void(*visit)(const DataType &));	//��α�����rΪ���Ķ�����
	//���ݶ�����������������к�����������д�����rΪ���Ķ�����
	void CreateBinaryTree(BTNode<DataType> * &r, DataType pre[], DataType in[], int preStart, int preEnd, int inStart, int inEnd);
	int Height(BTNode<DataType> *r);  										//����rΪ���Ķ������߶�
	int CountLeaf(BTNode<DataType> *r); 									//����rΪ���Ķ�������Ҷ�ӽڵ���Ŀ									
	BTNode<DataType> *Parent(BTNode<DataType> *r, BTNode<DataType> *p);		//����rΪ���Ķ������нڵ�p��˫��
	BTNode<DataType>* LocateElem(BTNode<DataType> *r, DataType &e);			//����rΪ���Ķ�������Ѱ������Ԫ�ص���e�Ľڵ�
public:
	BinaryTree():root(NULL) {}												//���캯��
	virtual ~BinaryTree() { Destroy(root); }								//��������
	BTNode<DataType>* GetRoot() { return root; }							//���ظ�ָ��
	bool IsEmpty() { return root == NULL ? true : false; }					//�ж϶������Ƿ�Ϊ��
	void PreOrder(void(*visit)(const DataType &));							//�������������
	void InOrder(void(*visit)(const DataType &));							//�������������
	void PostOrder(void(*visit)(const DataType &));							//�������������
	void LevelOrder(void(*visit)(const DataType &));						//��α���������
	void CreateBinaryTree(DataType pre[], DataType in[], int n);			//���ݶ���������������ͺ���������д���n���ڵ�Ķ�����
	void InsertLeftChild(BTNode<DataType>* p, DataType &e);					//����e��Ϊ�ڵ�p������
	void InsertRightChild(BTNode<DataType>* p, DataType &e);				//����e��Ϊ�ڵ�p���Һ���
	void DeleteLeftChild(BTNode<DataType>* p)								//ɾ���ڵ�p��������
	{	if(p)  Destroy(p->lChild);	}
	void DeleteRightChild(BTNode<DataType>* p)								//ɾ���ڵ�p��������
	{	if(p)  Destroy(p->rChild);	}
	int CountLeaf() { return CountLeaf(root); }								//���������Ҷ�ӽڵ���Ŀ
	int Height() { return Height(root); }									//��������ĸ߶�
	BTNode<DataType>* Parent(BTNode<DataType> *p) 							//�ڶ���������ڵ�p��˫��
	{	return (root == NULL || p == root) ? NULL : Parent(root, p);	}
	BTNode<DataType>* LocateElem(DataType &e);								//�ڶ�������Ѱ������Ԫ�ص���e�Ľڵ�
};

template <class DataType>
void BinaryTree<DataType>::Destroy(BTNode<DataType> * &r) {		//ɾ����rΪ���Ķ�����
	if(r) {														//��rΪ���Ķ��������ǿ�����ɾ��
		Destroy(r->lChild);										//ɾ��r��������
		Destroy(r->rChild);										//ɾ��r��������
		delete r;												//ɾ�����ڵ�r
		r = NULL;									
	}
}

template <class DataType>
void BinaryTree<DataType>::PreOrder(BTNode<DataType> *r, void(*visit)(const DataType &)) {	//���������rΪ���Ķ�����
	if(r != NULL) {
		visit(r->data);  										//���ȷ��ʸ��ڵ�r
		PreOrder(r->lChild, visit);  							//Ȼ���������r��������
		PreOrder(r->rChild, visit);  							//����������r��������
	}
}

template <class DataType>
void BinaryTree<DataType>::InOrder(BTNode<DataType> *r, void(*visit)(const DataType &)) {	//���������rΪ���Ķ�����
	if(r != NULL) {
		InOrder(r->lChild, visit);  							//�����������r��������
		visit(r->data);  										//Ȼ����ʸ��ڵ�r
		InOrder(r->rChild, visit);  							//����������r��������
	}
}

template <class DataType>
void BinaryTree<DataType>::PostOrder(BTNode<DataType> *r, void(*visit)(const DataType &)) {	//���������rΪ���Ķ�����
	if(r != NULL) {
		PostOrder(r->lChild, visit);  							//���Ⱥ������r��������
		PostOrder(r->rChild, visit);  							//Ȼ��������r��������
		visit(r->data);  										//�����ʸ��ڵ�r
	}
}

template <class DataType>
void BinaryTree<DataType>::LevelOrder(BTNode<DataType> *r, void(*visit)(const DataType &)) {	//��α�����rΪ���Ķ�����
	LinkQueue<BTNode<DataType> *> q;
	BTNode<DataType> *p;
	if(r)  q.EnQueue(r);										//���ڵ����
	while(!q.IsEmpty()) {										//�����в�Ϊ��
		q.DelQueue(p);    visit(p->data);						//��ͷ�ڵ���Ӳ�����
		if(p->lChild)  q.EnQueue(p->lChild);					//���Ӵ��������
		if(p->rChild)  q.EnQueue(p->rChild);					//�Һ��Ӵ��������
	}
}

//���ݶ�����������������к�����������д�����rΪ���Ķ�����
template <class DataType>
void BinaryTree<DataType>::CreateBinaryTree(BTNode<DataType> * &r, DataType pre[], DataType in[], int preStart, int preEnd, int inStart, int inEnd) {
	if(inStart > inEnd)  r = NULL;								//�޽ڵ㣬��ʾ��ǰ��rΪ���Ķ�����Ϊ����
	else {														//�нڵ㣬��ʾ��ǰ��rΪ���Ķ������ǿ�
		r = new BTNode<DataType>(pre[preStart]);				//�������������ҵ����ڵ�
		int mid = inStart;										//mid��ʾ���������и��ڵ�λ��
		while(in[mid] != pre[preStart])  mid++;					//������������Ѱ�Ҹ��ڵ��λ��
		//����r����������������������pre[preStart+1��preStart + mid �C inStart]������������in[inStart��mid �C 1]
		CreateBinaryTree(r->lChild, pre, in, preStart + 1, preStart + mid - inStart, inStart, mid - 1);
		//����r����������������������pre[preStart + mid - inStart + 1��preEnd]������������in[mid + 1��inEnd]
		CreateBinaryTree(r->rChild, pre, in, preStart + mid - inStart + 1, preEnd, mid + 1, inEnd);
	}
}

template <class DataType>
void BinaryTree<DataType>::CreateBinaryTree(BTNode<DataType> * &r, DataType pre[], DataType in[], int preStart, int preEnd, int inStart, int inEnd) {
	if(inStart > inEnd)  r = NULL;								//�޽ڵ㣬��ʾ��ǰ��rΪ���Ķ�����Ϊ����
	else {														//�нڵ㣬��ʾ��ǰ��rΪ���Ķ������ǿ�
		r = new BTNode<DataType>(pre[preStart]);				//�������������ҵ����ڵ�
		int mid = inStart;										//mid��ʾ���������и��ڵ�λ��
		while(in[mid] != pre[preStart])  mid++;					//������������Ѱ�Ҹ��ڵ��λ��
		//����r����������������������pre[preStart+1��preStart + mid �C inStart]������������in[inStart��mid �C 1]
		CreateBinaryTree(r->lChild, pre, in, preStart + 1, preStart + mid - inStart, inStart, mid - 1);
		//����r����������������������pre[preStart + mid - inStart + 1��preEnd]������������in[mid + 1��inEnd]
		CreateBinaryTree(r->rChild, pre, in, preStart + mid - inStart + 1, preEnd, mid + 1, inEnd);
	}
}

template <class DataType>
int BinaryTree<DataType>::Height(BTNode<DataType> *r) {			//����rΪ���Ķ������߶�
	if(r == NULL)  return 0;									//�ն������߶�Ϊ0
	else {
		int lh, rh;
		lh = Height(r->lChild);									//�����������ĸ߶�
		rh = Height(r->rChild);									//�����������ĸ߶�
		return (lh > rh ? lh : rh) + 1;							//���������߶ȵ����ֵ��1Ϊ���ĸ߶�
	}
}

template <class DataType>
int BinaryTree<DataType>::CountLeaf(BTNode<DataType> *r) {		//����rΪ���Ķ������Ľڵ����
	if(r == NULL)  return 0;									//�ն�������Ҷ�ӽڵ���ĿΪ0
	else if((r->lChild == NULL) && (r->rChild == NULL))  		//r��������������Ҷ�ӽڵ�
		return 1;
	else 														//r������
		return CountLeaf(r->lChild) + CountLeaf(r->rChild);		//��������������Ҷ�ӽڵ���Ŀ֮��
}


template <class DataType>
BTNode<DataType> * BinaryTree<DataType>::Parent(BTNode<DataType> *r, BTNode<DataType> *p) {	//����rΪ���Ķ������нڵ�p��˫��
	if(r == NULL)	return NULL;								//��rΪ���Ķ�����Ϊ�������޷��ҵ�˫��
	else if(r->lChild == p || r->rChild == p)	return r;		//r��p��˫�ף�����r
	else {
		BTNode<DataType> *t;
		if(t = Parent(r->lChild, p))	return t;				//������������p��˫�ף��ɹ�����˫��ָ��
		if(t = Parent(r->rChild, p))	return t;				//������������p��˫�ף��ɹ�����˫��ָ��
		return NULL;											//δ�ҵ�p��˫��
	}
}

//����rΪ���Ķ�������Ѱ������Ԫ�ص���e�Ľڵ�
template <class DataType>
BTNode<DataType> * BinaryTree<DataType>::LocateElem(BTNode<DataType> *r, DataType &e) {	
	BTNode<DataType> * p = NULL;
	if(r)
	{
		if(r->data == e)	p = r;
		else
		{
			p = LocateElem(r->lChild, e);
			if(!p)	p = LocateElem(r->rChild, e);
		}
	}
	return p;
}

template <class DataType>
void BinaryTree<DataType>::PreOrder(void(*visit)(const DataType &))	//�������������
{
	PreOrder(root, visit);
}

template <class DataType>
void BinaryTree<DataType>::InOrder(void(*visit)(const DataType &))	//�������������
{
	InOrder(root, visit);
}

template <class DataType>
void BinaryTree<DataType>::PostOrder(void(*visit)(const DataType &))//�������������
{
	PostOrder(root, visit);
}

template <class DataType>
void BinaryTree<DataType>::LevelOrder(void(*visit)(const DataType &))//��α���������
{
	LevelOrder(root, visit);
}

template <class DataType>
void BinaryTree<DataType>::CreateBinaryTree(DataType pre[], DataType in[], int n)	//���ݶ���������������ͺ���������д���n���ڵ�Ķ�����
{
	CreateBinaryTree(root, pre, in, 0, n - 1, 0, n - 1);
}

template <class DataType>
void BinaryTree<DataType>::InsertLeftChild(BTNode<DataType>* p, DataType &e) {	//����e��Ϊ�ڵ�p������
	if(p) {																	//�ڵ�p���ڣ������e��Ϊp������
		BTNode<DataType> *pNew = new BTNode<DataType>(e, p->lChild);			//�½��ڵ�
		p->lChild = pNew;														//�����Ϊp������
	}
}

template <class DataType>
void BinaryTree<DataType>::InsertRightChild(BTNode<DataType>* p, DataType &e)	//����e��Ϊ�ڵ�p���Һ���
{
	if(p) {																	//�ڵ�p���ڣ������e��Ϊp���Һ���
		BTNode<DataType> *pNew = new BTNode<DataType>(e, p->rChild);			//�½��ڵ�
		p->rChild = pNew;														//�����Ϊp���Һ���
	}
}

template <class DataType>
BTNode<DataType>* BinaryTree<DataType>::LocateElem(DataType &e)					//�ڶ�������Ѱ��ֵΪe�Ľڵ�
{
	return LocateElem(root, e);
}