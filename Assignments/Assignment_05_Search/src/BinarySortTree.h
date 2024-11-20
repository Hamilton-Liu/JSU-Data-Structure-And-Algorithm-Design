#pragma once
#include "BinaryTree.h"

template <class DataType>
class BinarySortTree: public BinaryTree<DataType>{
protected:
    BTNode<DataType>* Search(DataType &key, BTNode<DataType>* &f) const;
    void Delete(BTNode<DataType>* &p);
public:
    BinarySortTree();
    virtual ~BinarySortTree();
    BTNode<DataType> *Search(DataType &key) const;
    bool Insert(DataType &e);
    bool Delete(DataType &key);
    bool IsEmpty() { return this->root == NULL ? true : false; };
};

template<class DataType>
BinarySortTree<DataType>::BinarySortTree() {
    // 构造函数的实现
    this->root = NULL;  // 初始化树的根节点
}

template<class DataType>
BinarySortTree<DataType>::~BinarySortTree() {
    // 析构函数的实现
    // 清理树中的动态分配的内存
    Delete(this->root);
}

template<class DataType>
BTNode<DataType>* BinarySortTree<DataType>::Search(DataType &key, BTNode<DataType>* &f) const
{
    BTNode<DataType> *p = this -> root;
    f = NULL;
    while(p && p->data != key){
        f = p;
        if(key < p->data) p = p->lChild;
        else p = p->rChild;
    }
    return p;
}

template<class DataType>
BTNode<DataType>* BinarySortTree<DataType>::Search(DataType &key) const
{
    BTNode<DataType> *f;
    return Search(key, f);
}

template<class DataType>
bool BinarySortTree<DataType>::Insert(DataType &e)
{
    BTNode<DataType> *f;
    if(Search(e,f)) return false;
    BTNode<DataType> *p = new BTNode<DataType>(e);
    if(IsEmpty())
        this -> root = p;
    else if (e < f->data)
        f->lChild = p;
    else
        f->rChild = p;
    return true;
}

template<class DataType>
bool BinarySortTree<DataType>::Delete(DataType &key)
{
    BTNode<DataType> *p, *f;
    if ((p = Search(key,f)) == NULL) return false;
    if (f == NULL) {
        Delete(this->root);
    }
    else if (p == f->lChild){
        Delete(f->lChild);
    }
    else{
        Delete(f->rChild);
    }
    return true;
}

template<class DataType>
void BinarySortTree<DataType>::Delete(BTNode<DataType>* &p)
{
    BTNode<DataType>* tmpP,* tmpF;

    //叶子节点
    if(p->lChild == NULL && p->rChild == NULL)
    {
        delete p;
        p = NULL;
    }

    //仅有左子树
    else if(p->rChild == NULL)
    {
        tmpP = p;
        p = tmpP->lChild;
        delete tmpP;
    }

    //仅有右子树
    else if(p->lChild == NULL)
    {
        tmpP = p;
        p = tmpP->rChild;
        delete tmpP;
    }

    //有左、右子树
    else
    {
        tmpF = p;
        tmpP = p -> lChild;
        while(tmpP -> rChild){
            tmpF = tmpP;
            tmpP = tmpP -> rChild;
        }
        p -> data = tmpP -> data;
        if (tmpF -> rChild == tmpP)
            Delete(tmpF -> rChild);
        else
            Delete(tmpF -> lChild);
    }
}
