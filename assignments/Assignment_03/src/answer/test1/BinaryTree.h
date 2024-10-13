#pragma once
#include "BTNode.h"
template <class DataType>
class BinaryTree {
protected:
	BTNode<DataType> *root; ;   											//二叉树根节点
	void Destroy(BTNode<DataType> * &r);									//删除以r为根的二叉树
	void PreOrder(BTNode<DataType> *r, void(*visit)(const DataType &));		//先序遍历以r为根的二叉树
	void InOrder(BTNode<DataType> *r, void(*visit)(const DataType &));		//中序遍历以r为根的二叉树
	void PostOrder(BTNode<DataType> *r, void(*visit)(const DataType &));	//后序遍历以r为根的二叉树
	void LevelOrder(BTNode<DataType> *r, void(*visit)(const DataType &));	//层次遍历以r为根的二叉树
	//根据二叉树的先序遍历序列和中序遍历序列创建以r为根的二叉树
	void CreateBinaryTree(BTNode<DataType> * &r, DataType pre[], DataType in[], int preStart, int preEnd, int inStart, int inEnd);
	int Height(BTNode<DataType> *r);  										//求以r为根的二叉树高度
	int CountLeaf(BTNode<DataType> *r); 									//求以r为根的二叉树中叶子节点数目									
	BTNode<DataType> *Parent(BTNode<DataType> *r, BTNode<DataType> *p);		//求以r为根的二叉树中节点p的双亲
	BTNode<DataType>* LocateElem(BTNode<DataType> *r, DataType &e);			//在以r为根的二叉树中寻找数据元素等于e的节点
public:
	BinaryTree():root(NULL) {}												//构造函数
	virtual ~BinaryTree() { Destroy(root); }								//析构函数
	BTNode<DataType>* GetRoot() { return root; }							//返回根指针
	bool IsEmpty() { return root == NULL ? true : false; }					//判断二叉树是否为空
	void PreOrder(void(*visit)(const DataType &));							//先序遍历二叉树
	void InOrder(void(*visit)(const DataType &));							//中序遍历二叉树
	void PostOrder(void(*visit)(const DataType &));							//后序遍历二叉树
	void LevelOrder(void(*visit)(const DataType &));						//层次遍历二叉树
	void CreateBinaryTree(DataType pre[], DataType in[], int n);			//根据二叉树的先序遍历和后序遍历序列创建n个节点的二叉树
	void InsertLeftChild(BTNode<DataType>* p, DataType &e);					//插入e作为节点p的左孩子
	void InsertRightChild(BTNode<DataType>* p, DataType &e);				//插入e作为节点p的右孩子
	void DeleteLeftChild(BTNode<DataType>* p)								//删除节点p的左子树
	{	if(p)  Destroy(p->lChild);	}
	void DeleteRightChild(BTNode<DataType>* p)								//删除节点p的右子树
	{	if(p)  Destroy(p->rChild);	}
	int CountLeaf() { return CountLeaf(root); }								//求二叉树的叶子节点数目
	int Height() { return Height(root); }									//求二叉树的高度
	BTNode<DataType>* Parent(BTNode<DataType> *p) 							//在二叉树中求节点p的双亲
	{	return (root == NULL || p == root) ? NULL : Parent(root, p);	}
	BTNode<DataType>* LocateElem(DataType &e);								//在二叉树中寻找数据元素等于e的节点
};

template <class DataType>
void BinaryTree<DataType>::Destroy(BTNode<DataType> * &r) {		//删除以r为根的二叉树
	if(r) {														//以r为根的二叉树不是空树则删除
		Destroy(r->lChild);										//删除r的左子树
		Destroy(r->rChild);										//删除r的右子树
		delete r;												//删除根节点r
		r = NULL;									
	}
}

template <class DataType>
void BinaryTree<DataType>::PreOrder(BTNode<DataType> *r, void(*visit)(const DataType &)) {	//先序遍历以r为根的二叉树
	if(r != NULL) {
		visit(r->data);  										//首先访问根节点r
		PreOrder(r->lChild, visit);  							//然后先序遍历r的左子树
		PreOrder(r->rChild, visit);  							//最后先序遍历r的右子树
	}
}

template <class DataType>
void BinaryTree<DataType>::InOrder(BTNode<DataType> *r, void(*visit)(const DataType &)) {	//中序遍历以r为根的二叉树
	if(r != NULL) {
		InOrder(r->lChild, visit);  							//首先中序遍历r的左子树
		visit(r->data);  										//然后访问根节点r
		InOrder(r->rChild, visit);  							//最后中序遍历r的右子树
	}
}

template <class DataType>
void BinaryTree<DataType>::PostOrder(BTNode<DataType> *r, void(*visit)(const DataType &)) {	//后序遍历以r为根的二叉树
	if(r != NULL) {
		PostOrder(r->lChild, visit);  							//首先后序遍历r的左子树
		PostOrder(r->rChild, visit);  							//然后后序遍历r的右子树
		visit(r->data);  										//最后访问根节点r
	}
}

template <class DataType>
void BinaryTree<DataType>::LevelOrder(BTNode<DataType> *r, void(*visit)(const DataType &)) {	//层次遍历以r为根的二叉树
	LinkQueue<BTNode<DataType> *> q;
	BTNode<DataType> *p;
	if(r)  q.EnQueue(r);										//根节点入队
	while(!q.IsEmpty()) {										//当队列不为空
		q.DelQueue(p);    visit(p->data);						//队头节点入队并访问
		if(p->lChild)  q.EnQueue(p->lChild);					//左孩子存在则入队
		if(p->rChild)  q.EnQueue(p->rChild);					//右孩子存在则入队
	}
}

//根据二叉树的先序遍历序列和中序遍历序列创建以r为根的二叉树
template <class DataType>
void BinaryTree<DataType>::CreateBinaryTree(BTNode<DataType> * &r, DataType pre[], DataType in[], int preStart, int preEnd, int inStart, int inEnd) {
	if(inStart > inEnd)  r = NULL;								//无节点，表示当前以r为根的二叉树为空树
	else {														//有节点，表示当前以r为根的二叉树非空
		r = new BTNode<DataType>(pre[preStart]);				//在先序序列中找到根节点
		int mid = inStart;										//mid表示中序序列中根节点位置
		while(in[mid] != pre[preStart])  mid++;					//在中序序列中寻找根节点的位置
		//创建r的左子树，其先序序列在pre[preStart+1…preStart + mid – inStart]，中序序列在in[inStart…mid – 1]
		CreateBinaryTree(r->lChild, pre, in, preStart + 1, preStart + mid - inStart, inStart, mid - 1);
		//创建r的右子树，其先序序列在pre[preStart + mid - inStart + 1…preEnd]，中序序列在in[mid + 1…inEnd]
		CreateBinaryTree(r->rChild, pre, in, preStart + mid - inStart + 1, preEnd, mid + 1, inEnd);
	}
}

template <class DataType>
void BinaryTree<DataType>::CreateBinaryTree(BTNode<DataType> * &r, DataType pre[], DataType in[], int preStart, int preEnd, int inStart, int inEnd) {
	if(inStart > inEnd)  r = NULL;								//无节点，表示当前以r为根的二叉树为空树
	else {														//有节点，表示当前以r为根的二叉树非空
		r = new BTNode<DataType>(pre[preStart]);				//在先序序列中找到根节点
		int mid = inStart;										//mid表示中序序列中根节点位置
		while(in[mid] != pre[preStart])  mid++;					//在中序序列中寻找根节点的位置
		//创建r的左子树，其先序序列在pre[preStart+1…preStart + mid – inStart]，中序序列在in[inStart…mid – 1]
		CreateBinaryTree(r->lChild, pre, in, preStart + 1, preStart + mid - inStart, inStart, mid - 1);
		//创建r的右子树，其先序序列在pre[preStart + mid - inStart + 1…preEnd]，中序序列在in[mid + 1…inEnd]
		CreateBinaryTree(r->rChild, pre, in, preStart + mid - inStart + 1, preEnd, mid + 1, inEnd);
	}
}

template <class DataType>
int BinaryTree<DataType>::Height(BTNode<DataType> *r) {			//求以r为根的二叉树高度
	if(r == NULL)  return 0;									//空二叉树高度为0
	else {
		int lh, rh;
		lh = Height(r->lChild);									//计算左子树的高度
		rh = Height(r->rChild);									//计算右子树的高度
		return (lh > rh ? lh : rh) + 1;							//左、右子树高度的最大值加1为树的高度
	}
}

template <class DataType>
int BinaryTree<DataType>::CountLeaf(BTNode<DataType> *r) {		//求以r为根的二叉树的节点个数
	if(r == NULL)  return 0;									//空二叉树的叶子节点数目为0
	else if((r->lChild == NULL) && (r->rChild == NULL))  		//r无子树，则本身是叶子节点
		return 1;
	else 														//r有子树
		return CountLeaf(r->lChild) + CountLeaf(r->rChild);		//计算左、右子树的叶子节点数目之和
}


template <class DataType>
BTNode<DataType> * BinaryTree<DataType>::Parent(BTNode<DataType> *r, BTNode<DataType> *p) {	//求以r为根的二叉树中节点p的双亲
	if(r == NULL)	return NULL;								//以r为根的二叉树为空树，无法找到双亲
	else if(r->lChild == p || r->rChild == p)	return r;		//r是p的双亲，返回r
	else {
		BTNode<DataType> *t;
		if(t = Parent(r->lChild, p))	return t;				//在左子树中找p的双亲，成功返回双亲指针
		if(t = Parent(r->rChild, p))	return t;				//在右子树中找p的双亲，成功返回双亲指针
		return NULL;											//未找到p的双亲
	}
}

//在以r为根的二叉树中寻找数据元素等于e的节点
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
void BinaryTree<DataType>::PreOrder(void(*visit)(const DataType &))	//先序遍历二叉树
{
	PreOrder(root, visit);
}

template <class DataType>
void BinaryTree<DataType>::InOrder(void(*visit)(const DataType &))	//中序遍历二叉树
{
	InOrder(root, visit);
}

template <class DataType>
void BinaryTree<DataType>::PostOrder(void(*visit)(const DataType &))//后序遍历二叉树
{
	PostOrder(root, visit);
}

template <class DataType>
void BinaryTree<DataType>::LevelOrder(void(*visit)(const DataType &))//层次遍历二叉树
{
	LevelOrder(root, visit);
}

template <class DataType>
void BinaryTree<DataType>::CreateBinaryTree(DataType pre[], DataType in[], int n)	//根据二叉树的先序遍历和后序遍历序列创建n个节点的二叉树
{
	CreateBinaryTree(root, pre, in, 0, n - 1, 0, n - 1);
}

template <class DataType>
void BinaryTree<DataType>::InsertLeftChild(BTNode<DataType>* p, DataType &e) {	//插入e作为节点p的左孩子
	if(p) {																	//节点p存在，则插入e成为p的左孩子
		BTNode<DataType> *pNew = new BTNode<DataType>(e, p->lChild);			//新建节点
		p->lChild = pNew;														//插入成为p的左孩子
	}
}

template <class DataType>
void BinaryTree<DataType>::InsertRightChild(BTNode<DataType>* p, DataType &e)	//插入e作为节点p的右孩子
{
	if(p) {																	//节点p存在，则插入e成为p的右孩子
		BTNode<DataType> *pNew = new BTNode<DataType>(e, p->rChild);			//新建节点
		p->rChild = pNew;														//插入成为p的右孩子
	}
}

template <class DataType>
BTNode<DataType>* BinaryTree<DataType>::LocateElem(DataType &e)					//在二叉树中寻找值为e的节点
{
	return LocateElem(root, e);
}