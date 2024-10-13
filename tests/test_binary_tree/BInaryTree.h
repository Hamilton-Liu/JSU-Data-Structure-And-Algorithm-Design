#include "BTNode.h"

template<class DataType>
class BinaryTree{
protected:
    BTNode<DataType> *root;
    void Destroy(BTNode<DataType>* &r);
    void PreOrder(BTNode<DataType>* &r, void(*visit)(const DataType &));
    void InOrder(BTNode<DataType>* &r, void(*visit)(const DataType &));
    void PostOrder(BTNode<DataType>* &r, void(*visit)(const DataType &));
    void LevelOrder(BTNode<DataType>* &r, void(*visit)(const DataType &));
    void CreateBinaryTree();
    int Height();
    int CountLeaf();
    BTNode<DataType>* Parent(BTNode<DataType> *r, BTNode<DataType> *p);
public:
    BinaryTree():root(NULL){}
    void InsertLeftChild(BTNode<DataType> *p, DataType e);
    void InsertRightChild(BTNode<DataType> *p, DataType e);
};

//删除二叉树
template<class DataType>
void Destroy(BTNode<DataType>* &r){
    if(r){
        Destroy(r->lChild);
        Destroy(r->rChild);
        delete r; r = NULL;
    }
}

//找双亲
template<class DataType>
BTNode<DataType>* Parent(BTNode<DataType> *r, BTNode<DataType> *p){
    if(r == NULL || r == p) return NULL;
    else if(r->lChild == p || r->rChild == p) return r;
    BTNode<DataType> *t;

    t = Parent(r->lChild,p);
    if (t != NULL) return t;

    t = Parent(r->rChild,p);
    if (t != NULL) return t;

    return NULL;
}
//找双亲2
template<class DataType>
BTNode<DataType>* Parent(BTNode<DataType> *r, BTNode<DataType> *p){
    if(r == NULL || r == p) return NULL;
    else if(r->lChild == p || r->rChild == p) return r;
    else{
        BTNode<DataType> *t;
        if(t = Parent(r->lChild,p)) return t;
        if(t = Parent(r->rChild,p)) return t;
        return NULL;
    }
}

//插入左孩子
template<class DataType>
void InsertLeftChild(BTNode<DataType> *p, DataType e){
    if (p){
        BTNode<DataType> *leftChild = new BTNode<DataType>(e, p->lChild);
        p->lChild = leftChild;
    }   
}

//插入右孩子
template<class DataType>
void InsertRightChild(BTNode<DataType> *p, DataType e){
    
}

