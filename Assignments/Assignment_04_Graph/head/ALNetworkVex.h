#pragma once
template<class DataType, class WeightType>
class ALNetworkVex {
public:
	DataType data;													//��������Ԫ��ֵ
	ALNetworkArc<WeightType> *firstarc;								//ָ�������ͷָ��
	ALNetworkVex()	     		       								//�޲ι��캯��������һ���յĶ���ڵ�
	{
		firstarc = NULL;
	}
	ALNetworkVex(DataType &e, ALNetworkArc<WeightType> *arc = NULL) //�вι��캯��
	{
		data = e;	firstarc = arc;
	}
};
