template <class DataType>
class BTNode{
public:
    DataType data;                  //数据域
    BTNode<DataType> *lChild;       //左孩子指针域
    BTNode<DataType> *rChild;       //右孩子指针域
    BTNode(){                       //无参构造函数
        lChild = rChild = NULL;     //初始化左右孩子指针为空
    }
    BTNode(DataType &e, BTNode<DataType> *leftChild = NULL, BTNode<DataType> *rightChild = NULL){
        data = e; lChild = leftChild; rChild = rightChild;
    }                               //有参构造函数
};