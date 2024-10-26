#pragma once
#include "TreeNode.h"
#include <cstring>
template <class DataType>
class Tree {
protected:
	TreeNode<DataType> *root; ;   											//二叉树根节点
	void Destroy(TreeNode<DataType> * &r);									//删除以r为根的二叉树
	void PreOrder(TreeNode<DataType> *r, void(*visit)(const DataType &));		//先序遍历以r为根的二叉树
	void InOrder(TreeNode<DataType> *r, void(*visit)(const DataType &));		//中序遍历以r为根的二叉树
	void PostOrder(TreeNode<DataType> *r, void(*visit)(const DataType &));	//后序遍历以r为根的二叉树
	void LevelOrder(TreeNode<DataType> *r, void(*visit)(const DataType &));	//层次遍历以r为根的二叉树
	//根据二叉树的先序遍历序列和中序遍历序列创建以r为根的二叉树
	void CreateTree(TreeNode<DataType> * &r, DataType pre[], DataType in[], int preStart, int preEnd, int inStart, int inEnd);
	void CreateTree(TreeNode<DataType> * &r, DataType pre[], int &preStart);
	//根据二叉树的有占位符的先序遍历序列创建n个节点的二叉树	
	int Height(TreeNode<DataType> *r);  										//求以r为根的二叉树高度
	int CountLeaf(TreeNode<DataType> *r); 									//求以r为根的二叉树中叶子节点数目									
	TreeNode<DataType> *Parent(TreeNode<DataType> *r, TreeNode<DataType> *p);		//求以r为根的二叉树中节点p的双亲
	TreeNode<DataType>* LocateElem(TreeNode<DataType> *r, DataType &e);			//在以r为根的二叉树中寻找数据元素等于e的节点
	int Width(TreeNode<DataType> *r);											//求二叉树最大宽度
	int getNodeCount(TreeNode<DataType> *r);									//递归求二叉树节点数
	int Degree(TreeNode<DataType>* r);											//求树的度
public:
	Tree():root(NULL) {}												//构造函数
	virtual ~Tree() { Destroy(root); }								//析构函数
	TreeNode<DataType>* GetRoot() { return root; }							//返回根指针
	bool IsEmpty() { return root == NULL ? true : false; }					//判断二叉树是否为空
	void PreOrder(void(*visit)(const DataType &));							//先序遍历二叉树
	void InOrder(void(*visit)(const DataType &));							//中序遍历二叉树
	void PostOrder(void(*visit)(const DataType &));							//后序遍历二叉树
	void LevelOrder(void(*visit)(const DataType &));						//层次遍历二叉树
	void CreateTree(DataType pre[], DataType in[], int n);			//根据二叉树的先序遍历和后序遍历序列创建n个节点的二叉树
	void CreateTree();												//接口函数		(1)
	void InsertLeftChild(TreeNode<DataType>* p, DataType &e);					//插入e作为节点p的左孩子
	void InsertRightChild(TreeNode<DataType>* p, DataType &e);				//插入e作为节点p的右孩子
	void DeleteLeftChild(TreeNode<DataType>* p)								//删除节点p的左子树
	{	if(p)  Destroy(p->Child);	}
	void DeleteRightChild(TreeNode<DataType>* p)								//删除节点p的右子树
	{	if(p)  Destroy(p->Brother);	}
	int CountLeaf() { return CountLeaf(root); }								//求二叉树的叶子节点数目
	int Height() ;															//求二叉树的高度
	TreeNode<DataType>* Parent(TreeNode<DataType> *p) 							//在二叉树中求节点p的双亲
	{	return (root == NULL || p == root) ? NULL : Parent(root, p);	}
	TreeNode<DataType>* LocateElem(DataType &e);								//在二叉树中寻找数据元素等于e的节点
	int Width();															//求二叉树最大宽度（接口）
	int NodeCount();														//递归求节点数目（接口）
	int Degree();															//求度数（接口）
};

template <class DataType>
void Tree<DataType>::Destroy(TreeNode<DataType> * &r) {  // 删除以r为根的二叉树
    if (r) {                                             // 如果当前节点不为空
        Destroy(r->Child);                               // 递归删除左孩子（即子节点）
        Destroy(r->Brother);                             // 递归删除兄弟节点
        delete r;                                        // 删除当前节点
        r = NULL;                                        // 置空指针，防止悬挂指针
    }
}

template <class DataType>
void Tree<DataType>::PreOrder(TreeNode<DataType> *r, void(*visit)(const DataType &)) {
	if (r != NULL) {
		visit(r->data);         			// 首先访问根节点
		PreOrder(r->Child, visit);   		// 然后先序遍历子节点（左孩子）
		PreOrder(r->Brother, visit); 		// 最后先序遍历兄弟节点
	}
}

template <class DataType>
void Tree<DataType>::PostOrder(TreeNode<DataType> *r, void(*visit)(const DataType &)) {
    if (r != NULL) {
        // 首先递归遍历所有的子节点
        TreeNode<DataType> *p = r->Child;
        while (p != NULL) {
            PostOrder(p, visit);         // 后序遍历子节点
            p = p->Brother;              // 访问下一个兄弟节点
        }
        // 最后访问根节点
        visit(r->data);
    }
}

template <class DataType>
void Tree<DataType>::LevelOrder(TreeNode<DataType> *r, void(*visit)(const DataType &)) {
	LinkQueue<TreeNode<DataType> *> q;    // 使用队列存储节点
	TreeNode<DataType> *p;
	if (r) q.EnQueue(r);                  // 根节点入队
	while (!q.IsEmpty()) {                // 当队列不为空时
		q.DelQueue(p);                    // 队头节点出队并访问
		visit(p->data);                   // 访问当前节点
		// 子节点（左孩子）入队
		if (p->Child) {
			q.EnQueue(p->Child);          // 将当前节点的第一个子节点入队
			// 将子节点的所有兄弟节点依次入队
			TreeNode<DataType>* sibling = p->Child->Brother;
			while (sibling != NULL) {
				q.EnQueue(sibling);       // 兄弟节点依次入队
				sibling = sibling->Brother;
			}
		}
	}
}

//根据二叉树的先序遍历序列和中序遍历序列创建以r为根的二叉树
template <class DataType>
void Tree<DataType>::CreateTree(TreeNode<DataType> * &r, DataType pre[], DataType in[], int preStart, int preEnd, int inStart, int inEnd) {
	if(inStart > inEnd)  r = NULL;								//无节点，表示当前以r为根的二叉树为空树
	else {														//有节点，表示当前以r为根的二叉树非空
		r = new TreeNode<DataType>(pre[preStart]);				//在先序序列中找到根节点
		int mid = inStart;										//mid表示中序序列中根节点位置
		while(in[mid] != pre[preStart])  mid++;					//在中序序列中寻找根节点的位置
		//创建r的左子树，其先序序列在pre[preStart+1…preStart + mid – inStart]，中序序列在in[inStart…mid – 1]
		CreateTree(r->Child, pre, in, preStart + 1, preStart + mid - inStart, inStart, mid - 1);
		//创建r的右子树，其先序序列在pre[preStart + mid - inStart + 1…preEnd]，中序序列在in[mid + 1…inEnd]
		CreateTree(r->Brother, pre, in, preStart + mid - inStart + 1, preEnd, mid + 1, inEnd);
	}
}

//根据二叉树的有占位符的先序遍历序列创建n个节点的二叉树
template <class DataType>
void Tree<DataType>::CreateTree(TreeNode<DataType> * &r, DataType pre[], int &preStart) {
	if(pre[preStart] == '#') {
		r = NULL;
		preStart++;
		return;
	} 
	r = new TreeNode<DataType>(pre[preStart]);
	preStart++;
	CreateTree(r->Child, pre, preStart);	//递归构建左子树
	CreateTree(r->Brother, pre, preStart);	//递归构建右子树
}
//接口函数
template <class DataType>
void Tree<DataType>::CreateTree() {
    string pre;  // 用字符串表示先序序列
    cin >> pre;  // 输入先序序列

    int preStart = 0;  // 初始化先序序列的起始位置
    char *preArray = new char[pre.length() + 1];  // 创建一个字符数组
    strcpy(preArray, pre.c_str());  // 将字符串内容复制到字符数组中

    CreateTree(root, preArray, preStart);  // 调用递归函数构建二叉树

    delete[] preArray;  // 使用完数组后，释放内存
}

template <class DataType>
int Tree<DataType>::Height(TreeNode<DataType> *r) {         //求以r为根的二叉树高度
    
    if (r == NULL) return 0;		//空二叉树高度为0
    int Height = 0;  				//初始化高度为0
    TreeNode<DataType>* p = r->Child;  //把孩子节点的地址存到p里
    while (p!= NULL) {				//如果孩子节点存在
        int pHeight = this->Height(p);   //递归计算孩子高度
        p = p->Brother;            //将指针移动到兄弟指针，以遍历每一个节点
		if (pHeight > Height) {
			Height = pHeight; 	//如果孩子的高度大于Height，更新Height为pHeight
		}     
    }
    return Height + 1;
}

template <class DataType>
int Tree<DataType>::Height() {         //接口
    return Height(root);
}

template <class DataType>
int Tree<DataType>::CountLeaf(TreeNode<DataType> *r) {		//求以r为根的二叉树的节点个数
	if(r == NULL)  return 0;									//空二叉树的叶子节点数目为0
	else if((r->Child == NULL) && (r->Brother == NULL))  		//r无子树，则本身是叶子节点
		return 1;
	else 														//r有子树
		return CountLeaf(r->Child) + CountLeaf(r->Brother);		//计算左、右子树的叶子节点数目之和
}


template <class DataType>
TreeNode<DataType> * Tree<DataType>::Parent(TreeNode<DataType> *r, TreeNode<DataType> *p) {	//求以r为根的二叉树中节点p的双亲
	if(r == NULL)	return NULL;								//以r为根的二叉树为空树，无法找到双亲
	else if(r->Child == p || r->Brother == p)	return r;		//r是p的双亲，返回r
	else {
		TreeNode<DataType> *t;
		if(t = Parent(r->Child, p))	return t;				//在左子树中找p的双亲，成功返回双亲指针
		if(t = Parent(r->Brother, p))	return t;				//在右子树中找p的双亲，成功返回双亲指针
		return NULL;											//未找到p的双亲
	}
}

//在以r为根的二叉树中寻找数据元素等于e的节点
template <class DataType>
TreeNode<DataType> * Tree<DataType>::LocateElem(TreeNode<DataType> *r, DataType &e) {	
	TreeNode<DataType> * p = NULL;
	if(r)
	{
		if(r->data == e)	p = r;
		else
		{
			p = LocateElem(r->Child, e);
			if(!p)	p = LocateElem(r->Brother, e);
		}
	}
	return p;
}

template <class DataType>
void Tree<DataType>::PreOrder(void(*visit)(const DataType &))	//先序遍历二叉树
{
	PreOrder(root, visit);
}

template <class DataType>
void Tree<DataType>::InOrder(void(*visit)(const DataType &))	//中序遍历二叉树
{
	InOrder(root, visit);
}

template <class DataType>
void Tree<DataType>::PostOrder(void(*visit)(const DataType &))//后序遍历二叉树
{
	PostOrder(root, visit);
}

template <class DataType>
void Tree<DataType>::LevelOrder(void(*visit)(const DataType &))//层次遍历二叉树
{
	LevelOrder(root, visit);
}

template <class DataType>
void Tree<DataType>::CreateTree(DataType pre[], DataType in[], int n)	//根据二叉树的先序遍历和后序遍历序列创建n个节点的二叉树
{
	CreateTree(root, pre, in, 0, n - 1, 0, n - 1);
}


template <class DataType>
void Tree<DataType>::InsertLeftChild(TreeNode<DataType>* p, DataType &e) {	//插入e作为节点p的左孩子
	if(p) {																	//节点p存在，则插入e成为p的左孩子
		TreeNode<DataType> *pNew = new TreeNode<DataType>(e, p->Child);			//新建节点
		p->Child = pNew;														//插入成为p的左孩子
	}
}

template <class DataType>
void Tree<DataType>::InsertRightChild(TreeNode<DataType>* p, DataType &e)	//插入e作为节点p的右孩子
{
	if(p) {																	//节点p存在，则插入e成为p的右孩子
		TreeNode<DataType> *pNew = new TreeNode<DataType>(e, p->Brother);			//新建节点
		p->Brother = pNew;														//插入成为p的右孩子
	}
}

template <class DataType>
TreeNode<DataType>* Tree<DataType>::LocateElem(DataType &e)					//在二叉树中寻找值为e的节点
{
	return LocateElem(root, e);
}

template <class DataType>
int Tree<DataType>::Width(TreeNode<DataType> *r)					//求二叉树最大宽度
{
    if (!root) return 0;

    LinkQueue<TreeNode<DataType>*> q;
    q.EnQueue(root);
    int maxWidth = 0;

    while (!q.IsEmpty()) {
        int width = q.GetLength();  // 当前层的宽度
        maxWidth = std::max(maxWidth, width);
		TreeNode<DataType> *p;
        // 处理下一层的节点
        for (int i = 0; i < width; ++i) {
            q.GetHead(p);
            if (p->Child) q.EnQueue(p->Child);
            if (p->Brother) q.EnQueue(p->Brother);
			q.DelQueue(p);
        }
    }
	return maxWidth;
}

/*LinkQueue<TreeNode<DataType> *> q;
	TreeNode<DataType> *p;
	if(r)  q.EnQueue(r);										//根节点入队
	while(!q.IsEmpty()) {										//当队列不为空
		q.DelQueue(p);    visit(p->data);						//队头节点入队并访问
		if(p->Child)  q.EnQueue(p->Child);					//左孩子存在则入队
		if(p->Brother)  q.EnQueue(p->Brother);					//右孩子存在则入队
		*/

template <class DataType>
int Tree<DataType>::Width() {
        return Width(root);
}

template <class DataType>
int Tree<DataType>::getNodeCount(TreeNode<DataType> *r) {
        if (!r) return 0;  // 如果节点为空，返回 0
        return 1 + getNodeCount(r->Child) + getNodeCount(r->Brother);// 节点数等于当前节点（1）+ 左子树节点数 + 右子树节点数
}

template <class DataType>
int Tree<DataType>::NodeCount(){
	return getNodeCount(root);
}

template <class DataType>
int Tree<DataType>::Degree(TreeNode<DataType>* r) {
    if (r == NULL) return 0;				// 空树度为0

    int Degree = 0;							// 当前节点的度数
    int maxDegree = 0;						// 树的最大度数
    TreeNode<DataType>* p = r->Child;		// 获取根节点的第一个孩子节点

    // 递归计算当前节点的度（即孩子节点的数量）
    while (p != NULL) {
        Degree++;							 // 孩子节点存在，度数+1
        int childDegree = this->Degree(p); 		 // 递归计算子节点的度
        if (childDegree > maxDegree)
    	 maxDegree = childDegree;         		// 更新最大度
        p = p->Brother;						 // 访问下一个兄弟节点
    }

    // 返回当前节点度和子节点度中的最大值
    if (Degree > maxDegree)           //比较节点度数和记录的最大度，如果更大，则替换
        maxDegree = Degree;
	return maxDegree;
}

template <class DataType>
int Tree<DataType>::Degree() {
	return Degree(root);
}