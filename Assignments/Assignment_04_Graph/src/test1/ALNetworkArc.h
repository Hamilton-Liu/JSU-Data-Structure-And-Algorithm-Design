#pragma once
template<class WeightType>
class ALNetworkArc {
public:
	int adjvex;																	//弧头顶点序号
	WeightType weight;															//弧的权值
	ALNetworkArc<WeightType> *nextarc;											//后继弧节点的指针
	ALNetworkArc()																//无参构造函数，创建一个空的弧节点
	{
		adjvex = -1;	nextarc = NULL;
	}
	ALNetworkArc(int adj, WeightType w, ALNetworkArc<WeightType> * next = NULL) //有参构造函数
	{
		adjvex = adj;	weight = w;	nextarc = next;
	}
};
