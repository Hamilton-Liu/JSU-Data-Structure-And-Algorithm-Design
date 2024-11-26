#pragma once
#include "BTNode.h"
#include <cstring>
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
	void CreateBinaryTree(BTNode<DataType> * &r, DataType pre[], int &preStart);
	//���ݶ���������ռλ��������������д���n���ڵ�Ķ�����		(1)
	int Height(BTNode<DataType> *r);  										//����rΪ���Ķ������߶�
	int CountLeaf(BTNode<DataType> *r); 									//����rΪ���Ķ�������Ҷ�ӽڵ���Ŀ									
	BTNode<DataType> *Parent(BTNode<DataType> *r, BTNode<DataType> *p);		//����rΪ���Ķ������нڵ�p��˫��
	BTNode<DataType>* LocateElem(BTNode<DataType> *r, DataType &e);			//����rΪ���Ķ�������Ѱ������Ԫ�ص���e�Ľڵ�
	int Width(BTNode<DataType> *r);											//�������������
	int getNodeCount(BTNode<DataType> *r);									//�ݹ���������ڵ���
	bool Isomorphism(BTNode<DataType> *r1,BTNode<DataType> *r2, BTNode<DataType> *f1, BTNode<DataType> *f2);
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
	void CreateBinaryTree();												//�ӿں���		(1)
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
	int Width();															//������������ȣ��ӿڣ�
	int NodeCount();														//�ݹ���ڵ���Ŀ���ӿڣ�
	bool Isomorphism(BinaryTree<char> tree);
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

//���ݶ���������ռλ��������������д���n���ڵ�Ķ�����
template <class DataType>
void BinaryTree<DataType>::CreateBinaryTree(BTNode<DataType> * &r, DataType pre[], int &preStart) {
	if(pre[preStart] == '#') {
		r = NULL;
		preStart++;
		return;
	} 
	r = new BTNode<DataType>(pre[preStart]);
	preStart++;
	CreateBinaryTree(r->lChild, pre, preStart);	//�ݹ鹹��������
	CreateBinaryTree(r->rChild, pre, preStart);	//�ݹ鹹��������
}
//�ӿں���
template <class DataType>
void BinaryTree<DataType>::CreateBinaryTree() {
    string pre;  // ���ַ�����ʾ��������
    cin >> pre;  // ������������

    int preStart = 0;  // ��ʼ���������е���ʼλ��
    char *preArray = new char[pre.length() + 1];  // ����һ���ַ�����
    strcpy(preArray, pre.c_str());  // ���ַ������ݸ��Ƶ��ַ�������

    CreateBinaryTree(root, preArray, preStart);  // ���õݹ麯������������

    delete preArray;  // ʹ����������ͷ��ڴ�
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

template <class DataType>
int BinaryTree<DataType>::Width(BTNode<DataType> *r)					//�������������
{
    if (!root) return 0;

    LinkQueue<BTNode<DataType>*> q;
    q.EnQueue(root);
    int maxWidth = 0;

    while (!q.IsEmpty()) {
        int width = q.GetLength();  // ��ǰ��Ŀ���
        maxWidth = std::max(maxWidth, width);
		BTNode<DataType> *p;
        // ������һ��Ľڵ�
        for (int i = 0; i < width; ++i) {
            q.GetHead(p);
            if (p->lChild) q.EnQueue(p->lChild);
            if (p->rChild) q.EnQueue(p->rChild);
			q.DelQueue(p);
        }
    }
	return maxWidth;
}

/*LinkQueue<BTNode<DataType> *> q;
	BTNode<DataType> *p;
	if(r)  q.EnQueue(r);										//���ڵ����
	while(!q.IsEmpty()) {										//�����в�Ϊ��
		q.DelQueue(p);    visit(p->data);						//��ͷ�ڵ���Ӳ�����
		if(p->lChild)  q.EnQueue(p->lChild);					//���Ӵ��������
		if(p->rChild)  q.EnQueue(p->rChild);					//�Һ��Ӵ��������
		*/

template <class DataType>
int BinaryTree<DataType>::Width() {
        return Width(root);
}

template <class DataType>
int BinaryTree<DataType>::getNodeCount(BTNode<DataType> *r) {
	if (!r) return 0;  // ����ڵ�Ϊ�գ����� 0
    return 1 + getNodeCount(r->lChild) + getNodeCount(r->rChild);// �ڵ������ڵ�ǰ�ڵ㣨1��+ �������ڵ��� + �������ڵ���
}

template <class DataType>
int BinaryTree<DataType>::NodeCount(){
	return getNodeCount(root);
}

//������������ö��������洢�ڵ㣬��Ƶݹ��㷨�ж����ö������Ƿ�ͬ��������̬��ͬ����
//����
template <class DataType>
bool BinaryTree<DataType>::Isomorphism(BTNode<DataType> *r1,BTNode<DataType> *r2, BTNode<DataType> *f1, BTNode<DataType> *f2){
	if (r1 == NULL && r2 == NULL) return true;
	if (r1 == NULL && r2 != NULL || r1 != NULL && r2 == NULL) return false;

	if(
		Isomorphism(r1->lChild, r2->lChild, r1, r2) && 
		Isomorphism(r1->rChild, r2->rChild, r1, r2)
	) 
		return true;
	else
		return false;

	/*if (r1->lChild == NULL && r1->rChild == NULL &&
		r2->lChild == NULL && r2->rChild == NULL)
	{
		if ((f1->lChild == r1 && f2->lChild == r2) ||
			(f1->rChild == r1 && f2->rChild == r2))
			return true;
		else return false;
	}*/
	
}

//�ӿ�
template <class DataType>
bool BinaryTree<DataType>::Isomorphism(BinaryTree<char> tree){
	return Isomorphism(root,tree.root,nullptr,nullptr);
}