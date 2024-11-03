#pragma once
template<class DataType, class WeightType>
class ALNetworkVex {
public:
	DataType data;													//顶点数据元素值
	ALNetworkArc<WeightType> *firstarc;								//指向弧链表的头指针
	ALNetworkVex()	     		       								//无参构造函数，创建一个空的顶点节点
	{
		firstarc = NULL;
	}
	ALNetworkVex(DataType &e, ALNetworkArc<WeightType> *arc = NULL) //有参构造函数
	{
		data = e;	firstarc = arc;
	}
};
