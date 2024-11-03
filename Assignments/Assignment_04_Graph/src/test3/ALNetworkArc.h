#pragma once
template<class WeightType>
class ALNetworkArc {
public:
	int adjvex;																	//��ͷ�������
	WeightType weight;															//����Ȩֵ
	ALNetworkArc<WeightType> *nextarc;											//��̻��ڵ��ָ��
	ALNetworkArc()																//�޲ι��캯��������һ���յĻ��ڵ�
	{
		adjvex = -1;	nextarc = NULL;
	}
	ALNetworkArc(int adj, WeightType w, ALNetworkArc<WeightType> * next = NULL) //�вι��캯��
	{
		adjvex = adj;	weight = w;	nextarc = next;
	}
};
