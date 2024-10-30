#pragma once
#include "Status.h"
#include "ALNetworkArc.h"
#include "ALNetworkVex.h"
const int DEFAULT_SIZE = 100;
const int DEFAULT_INFINITY = 0x3f3f3f3f;
template<class DataType, class WeightType>
class ALDirNetwork {
protected:
	int vexNum, vexMaxSize, arcNum;						//ʵ�ʶ�����Ŀ����������������ʵ�ʻ���
	WeightType infinity;								//�洢��ʾ������ֵ
	ALNetworkVex<DataType, WeightType> *vexs;			//ָ�򶥵������ָ��
	Status *visited;									//ָ����ʱ�־�����ָ��
public:
	//���캯��������������������Ϊvexsize�Ŀ�������
	ALDirNetwork(int vexsize = DEFAULT_SIZE, WeightType infinit = (WeightType)DEFAULT_INFINITY);
	//���캯������������vertexnum�����㣬û�л���������
	ALDirNetwork(DataType data[], int vertexnum, int vexsize = DEFAULT_SIZE, WeightType infinit = (WeightType)DEFAULT_INFINITY);
	virtual ~ALDirNetwork();					 				//��������
	void Clear();										//���������
	bool IsEmpty();										//�ж��������Ƿ�Ϊ��
	int GetOrder(const DataType &e) const;				//��ȡ����Ԫ�ص���e�Ķ������
	Status GetElem(int v, DataType & e) const;			//��ȡ����v������Ԫ��ֵ
	Status SetElem(int v, const DataType &e);			//�޸Ķ���v������Ԫ��ֵΪe
	WeightType GetInfinity() const;						//��ȡ��ʾ������ֵ
	int GetVexNum() const;								//��ȡ��ǰ������Ŀ
	int GetArcNum() const;								//��ȡ��ǰ������Ŀ
	int GetFirstAdjvex(int v) const;					//��ȡ����v�ĵ�һ���ڽӵ�
	int GetNextAdjvex(int v1, int v2)const;				//��ȡ����v1�����v2�ĺ���ڽӵ�
	Status InsertVex(const DataType &e);				//��������Ԫ��ֵΪe�Ķ���
	Status InsertArc(int v1, int v2, WeightType w);		//����Ӷ���v1��v2��ȨΪw�Ļ�
	Status DeleteVex(const DataType &e);				//ɾ������Ԫ��ֵΪe�Ķ���
	Status DeleteArc(int v1, int v2);					//ɾ���Ӷ���v1��v2�Ļ�
	WeightType GetWeight(int v1, int v2) const; 		//��ȡ�Ӷ���v1��v2�Ļ���Ȩֵ
	Status SetWeight(int v1, int v2, WeightType w);		//���ôӶ���v1��v2�Ļ���ȨֵΪw
	Status GetVisitedTag(int v) const;					//��ȡ����v�ķ��ʱ�־
	Status SetVisitedTag(int v, Status tag) const;		//�޸Ķ���v�ķ��ʱ�־Ϊtag
	void Display();										//��ʾ�������ڽӱ� 
};

//���캯��������������������Ϊvexsize�Ŀ�������
template<class DataType, class WeightType>
ALDirNetwork<DataType, WeightType>::ALDirNetwork(int vexsize, WeightType infinit)
{
	vexNum = 0;  vexMaxSize = vexsize;  arcNum = 0;  infinity = infinit;
	vexs = new ALNetworkVex<DataType, WeightType>[vexMaxSize]; 		//���䶥������
	visited = new Status[vexMaxSize]; 								//������ʱ�־����
	for(int v = 0; v < vexNum; v++) {								//��ʼ���������顢���ʱ�־����
		vexs[v].firstarc = NULL;
		visited[v] = UNVISITED;
	}
}

//���캯������������vertexnum�����㣬û�л���������
template<class DataType, class WeightType>
ALDirNetwork<DataType, WeightType>::ALDirNetwork(DataType data[], int vertexnum, int vexsize, WeightType infinit) {
	if(vexsize < vertexnum)
	{
		cout << "������Ŀ���ܴ�������Ķ��������Ŀ! ";  exit(0);
	}
	vexNum = vertexnum;  vexMaxSize = vexsize;  arcNum = 0;  infinity = infinit;
	vexs = new ALNetworkVex<DataType, WeightType>[vexMaxSize]; 		//���䶥������
	visited = new Status[vexMaxSize]; 								//������ʱ�־����
	for(int v = 0; v < vexNum; v++) {								//��ʼ���������顢���ʱ�־����
		vexs[v].data = data[v];  vexs[v].firstarc = NULL;
		visited[v] = UNVISITED;
	}
}

template<class DataType, class WeightType>
ALDirNetwork<DataType, WeightType>::~ALDirNetwork() {	//��������
	Clear();
	delete []vexs;
	delete []visited;
}

template<class DataType, class WeightType>
void ALDirNetwork<DataType, WeightType>::Clear() {		//���������
	ALNetworkArc<WeightType> *p;
	for(int v = 0; v < vexNum; v++) {					//�ͷ��ڽӵ��������÷��ʱ�־����
		p = vexs[v].firstarc;
		while(p) {
			vexs[v].firstarc = p->nextarc;
			delete p;
			p = vexs[v].firstarc;
		}
		visited[v] = UNVISITED;
	}
	vexNum = 0;  arcNum = 0;
}

template<class DataType, class WeightType>
bool ALDirNetwork<DataType, WeightType>::IsEmpty() {	//�ж��������Ƿ�Ϊ��
	return vexNum ? false : true;
}

template<class DataType, class WeightType>
int ALDirNetwork<DataType, WeightType>::GetOrder(const DataType &e) const {	//��ȡ����Ԫ�ص���e�Ķ������
	for(int v = 0; v < vexNum; v++)					//������������
		if(vexs[v].data == e)						//�ж϶��������Ԫ���Ƿ����e
			return v;								//����򷵻ض����±�
	return -1;										//δ�ҵ�������-1
}

template<class DataType, class WeightType>
Status ALDirNetwork<DataType, WeightType>::GetElem(int v, DataType & e) const {	//��ȡ����v������Ԫ��ֵ
	if(v < 0 || v >= vexNum)						//�ж�v�Ƿ�Խ��
	{
		cout << "vȡֵ���Ϸ�!" << endl;  return FAILED;
	}
	e = vexs[v].data;
	return SUCCESS;
}

template<class DataType, class WeightType>
Status ALDirNetwork<DataType, WeightType>::SetElem(int v, const DataType &e) {	//�޸Ķ���v������Ԫ��ֵΪe
	if(v < 0 || v >= vexNum)						//�ж�v�Ƿ�Խ��
	{
		cout << "vȡֵ���Ϸ�!" << endl;  return FAILED;
	}
	vexs[v].data = e;
	return SUCCESS;
}

template<class DataType, class WeightType>
WeightType ALDirNetwork<DataType, WeightType>::GetInfinity() const {	//��ȡ��ʾ������ֵ
	return infinity;
}

template<class DataType, class WeightType>
int ALDirNetwork<DataType, WeightType>::GetVexNum() const {	//��ȡ��ǰ������Ŀ
	return vexNum;
}

template<class DataType, class WeightType>
int ALDirNetwork<DataType, WeightType>::GetArcNum() const {	//��ȡ��ǰ������Ŀ
	return arcNum;
}

template<class DataType, class WeightType>
int ALDirNetwork<DataType, WeightType>::GetFirstAdjvex(int v) const {	//��ȡ����v�ĵ�һ���ڽӵ�
	if(v < 0 || v >= vexNum)						//�ж�v�Ƿ�Խ��
	{
		cout << "vȡֵ���Ϸ�!" << endl;  return -1;
	}
	if(vexs[v].firstarc == NULL)  return -1;		//�������ڽӵ�
	else  return vexs[v].firstarc->adjvex;			//���ص�һ�����ڵ��¼�Ļ�ͷ�������
}

template<class DataType, class WeightType>
int ALDirNetwork<DataType, WeightType>::GetNextAdjvex(int v1, int v2) const {	//��ȡ����v1�����v2�ĺ���ڽӵ�
	ALNetworkArc<WeightType> *p;
	if(v1 < 0 || v1 >= vexNum) 						//�ж�v1�Ƿ�Խ��
	{
		cout << "v1ȡֵ���Ϸ�!" << endl;  return -1;
	}
	if(v2 < 0 || v2 >= vexNum)						//�ж�v2�Ƿ�Խ��
	{
		cout << "v2ȡֵ���Ϸ�!" << endl;  return -1;
	}
	if(v1 == v2) 									//�ж�v1��v2�Ƿ����
	{
		cout << "v1��v2�������!" << endl;  return -1;
	}
	p = vexs[v1].firstarc;							//pָ������ĵ�һ�����ڵ�
	while(p != NULL && p->adjvex != v2)				//Ѱ��v2���ڵĻ��ڵ�
		p = p->nextarc;
	if(p == NULL || p->nextarc == NULL)  return -1;	//�����ں���ڽӵ�
	else  return p->nextarc->adjvex;				//���غ�̻��ڵ��¼�Ļ�ͷ�������
}

template<class DataType, class WeightType>
Status ALDirNetwork<DataType, WeightType>::InsertVex(const DataType &e) {	//��������Ԫ��ֵΪe�Ķ���
	if(vexNum == vexMaxSize)  return OVER_FLOW;		//������������
	vexs[vexNum].data = e;							//���������ݴ洢����������β��
	vexs[vexNum].firstarc = NULL;	
	visited[vexNum] = UNVISITED;  vexNum++;
	return SUCCESS;
}

template<class DataType, class WeightType>
Status ALDirNetwork<DataType, WeightType>::InsertArc(int v1, int v2, WeightType w) {	//����Ӷ���v1��v2��ȨΪw�Ļ�
	if(v1 < 0 || v1 >= vexNum) 						//�ж�v1�Ƿ�Խ��
	{
		cout << "v1ȡֵ���Ϸ�!" << endl;  return FAILED;
	}
	if(v2 < 0 || v2 >= vexNum)						//�ж�v2�Ƿ�Խ��
	{
		cout << "v2ȡֵ���Ϸ�!" << endl;  return FAILED;
	}
	if(v1 == v2) 									//�ж�v1��v2�Ƿ����
	{
		cout << "v1��v2�������!" << endl;  return FAILED;
	}
	if(w == infinity)								//�ж�wȡֵ�Ƿ�Ϊ����
	{
		cout << "Ȩֵw����Ϊ�����!" << endl;  return FAILED;
	}
	vexs[v1].firstarc = new ALNetworkArc<WeightType>(v2, w, vexs[v1].firstarc);
	arcNum++;
	return SUCCESS;
}

template<class DataType, class WeightType>
Status ALDirNetwork<DataType, WeightType>::DeleteArc(int v1, int v2) {	//ɾ���Ӷ���v1��v2�Ļ�
	if(v1 < 0 || v1 >= vexNum) 						//�ж�v1�Ƿ�Խ��
	{
		cout << "v1ȡֵ���Ϸ�!" << endl;  return FAILED;
	}
	if(v2 < 0 || v2 >= vexNum)						//�ж�v2�Ƿ�Խ��
	{
		cout << "v2ȡֵ���Ϸ�!" << endl;  return FAILED;
	}
	if(v1 == v2) 									//�ж�v1��v2�Ƿ����
	{
		cout << "v1��v2�������!" << endl;  return FAILED;
	}
	ALNetworkArc<WeightType> *pre = NULL, *p;		//preָ���ɾ�ڵ�ǰ����pָ���ɾ�ڵ�
	p = vexs[v1].firstarc;							//pָ���һ�����ڵ�
	while(p && p->adjvex != v2)						//Ѱ�Ҵ�ɾ���ڵ�
	{
		pre = p;  p = p->nextarc;
	}
	if(!p)  return FAILED;							//δ�ҵ���ɾ�Ļ��ڵ㣬ɾ��ʧ��
	if(p == vexs[v1].firstarc)						//��ɾ���ڵ��ǻ�����ĵ�һ���ڵ�
		vexs[v1].firstarc = p->nextarc;				//�޸Ļ������ͷָ��
	else											//��ɾ���ڵ㲻�ǻ�����ĵ�һ���ڵ�
		pre->nextarc = p->nextarc;					//�޸�ǰ���ڵ�ĺ��ָ��
	delete p;										//�ͷŴ�ɾ���ڵ�
	arcNum--;										//������Ŀ��1
	return SUCCESS;
}

template<class DataType, class WeightType>
Status ALDirNetwork<DataType, WeightType>::DeleteVex(const DataType &e) {	//ɾ������Ԫ��ֵΪe�Ķ���
	int v = GetOrder(e);							//��ȡ��ɾ��������
	ALNetworkArc<WeightType> *p;
	if(v == -1)										//δ�ҵ��ö���
	{
		cout << "��ɾ���Ķ��㲻����!" << endl;  return FAILED;
	}
	for(int w = 0; w < vexNum; w++)					//ɾ����v��Ϊ��ͷ����Ļ�
		if (w != v)  DeleteArc(w, v);
	p = vexs[v].firstarc;							//ɾ����v��Ϊ��β����Ļ�
	while(p) {										//�����ͷŻ������еĻ��ڵ�
		vexs[v].firstarc = p->nextarc;
		delete p;  p = vexs[v].firstarc;
		arcNum--;
	}
	if(v != vexNum - 1) {							//����ɾ���㲻�����һ�����㣬��Ҫ�ƶ�
		vexs[v].data = vexs[vexNum - 1].data;		//���ƶ�������
		vexs[v].firstarc = vexs[vexNum - 1].firstarc;	//���ƶ���Ļ�����ͷָ��
		vexs[vexNum - 1].firstarc = NULL;			//ԭ������ͷָ����Ϊ��ָ��
		visited[v] = visited[vexNum - 1];			//���ƶ������״̬��Ϣ
		//Ѱ�һ�ͷ����Ϊ���һ������Ļ��ڵ㣬�޸����еĻ�ͷ�������Ϊv													
		for(int w = 0; w < vexNum - 1; w++)
			if(w != v) {
				for(p = vexs[w].firstarc; p; p = p->nextarc)
					if(p->adjvex == vexNum - 1)
						p->adjvex = v;
			}
	}
	vexNum--;										//������Ŀ��1
	return SUCCESS;
}

template<class DataType, class WeightType>
WeightType ALDirNetwork<DataType, WeightType>::GetWeight(int v1, int v2) const {	//��ȡ�Ӷ���v1��v2�Ļ���Ȩֵ
	if(v1 < 0 || v1 >= vexNum) 						//�ж�v1�Ƿ�Խ��
	{
		cout << "v1ȡֵ���Ϸ�!" << endl;  return infinity;
	}
	if(v2 < 0 || v2 >= vexNum)						//�ж�v2�Ƿ�Խ��
	{
		cout << "v2ȡֵ���Ϸ�!" << endl;  return infinity;
	}
	if(v1 == v2) 									//�ж�v1��v2�Ƿ����
		return infinity;
	ALNetworkArc<WeightType> *p;
	p = vexs[v1].firstarc;							//pָ���һ�����ڵ�
	while(p && p->adjvex != v2)						//Ѱ���ڽӵ�v2
		p = p->nextarc;
	if(!p)  return infinity;						//v2����v1���ڽӵ㣬��������
	return p->weight;								//���شӶ���v1��v2�Ļ���Ȩֵ
}

template<class DataType, class WeightType>
Status ALDirNetwork<DataType, WeightType>::SetWeight(int v1, int v2, WeightType w) {	//���ôӶ���v1��v2�Ļ���ȨֵΪw
	if(v1 < 0 || v1 >= vexNum) 						//�ж�v1�Ƿ�Խ��
	{
		cout << "v1ȡֵ���Ϸ�!" << endl;  return FAILED;
	}
	if(v2 < 0 || v2 >= vexNum)						//�ж�v2�Ƿ�Խ��
	{
		cout << "v2ȡֵ���Ϸ�!" << endl;  return FAILED;
	}
	if(v1 == v2) 									//�ж�v1��v2�Ƿ����
	{
		cout << "v1��v2�������!" << endl;  return FAILED;
	}
	ALNetworkArc<WeightType> *p;
	p = vexs[v1].firstarc;							//pָ���һ�����ڵ�
	while(p && p->adjvex != v2)						//Ѱ���ڽӵ�v2
		p = p->nextarc;
	if(!p)  return FAILED;							//v2����v1���ڽӵ㣬����ʧ����Ϣ
	p->weight = w;									//�޸ĴӶ���v1��v2�Ļ���Ȩֵ
	return SUCCESS;								
}

template<class DataType, class WeightType>
Status ALDirNetwork<DataType, WeightType>::GetVisitedTag(int v) const {	//��ȡ����v�ķ��ʱ�־
	if(v < 0 || v >= vexNum)						//�ж�v�Ƿ�Խ��
	{
		cout << "vȡֵ���Ϸ�!" << endl;  return FAILED;
	}
	return visited[v];
}

template<class DataType, class WeightType>
Status ALDirNetwork<DataType, WeightType>::SetVisitedTag(int v, Status tag) const {	//�޸Ķ���v�ķ��ʱ�־Ϊtag
	if(v < 0 || v >= vexNum)						//�ж�v�Ƿ�Խ��
	{
		cout << "vȡֵ���Ϸ�!" << endl;  return FAILED;
	}
	visited[v] = tag;
	return SUCCESS;
}

template<class DataType, class WeightType>
void ALDirNetwork<DataType, WeightType>::Display()	//��ʾ�������ڽӱ�
{
	ALNetworkArc<WeightType> *p;
	cout << "����������" << vexNum << "�����㣬" << arcNum << "���ߡ�" << endl;
	for(int v = 0; v < vexNum; v++) {				//��ʾ��v���ڽ�����
		cout << v << ":\t" << vexs[v].data;		// ��ʾ�����
		p = vexs[v].firstarc;
		while(p != NULL) {
			cout << "-->(" << p->adjvex << "," << p->weight << ")";
			p = p->nextarc;
		}
		cout << endl;
	}
}

//��ȡ���ݲ���������ͼgraph
template <class DataType, class WeightType>
int LoadData(ALDirNetwork<DataType,WeightType> net)
{
    ifstream file("E:/Library/JSU-Data-Structure-And-Algorithm-Design/Assignments/Assignment_04_Graph/docs/data/GraphData.txt");
    if(!file.is_open()){
        cout << "Cannot open the file!" << endl;
        return 0;
    }
    
    int VexNum, ArcNum;
    file >> VexNum; file >> ArcNum;
    //net = ALDirNetwork<char,int>(VexNum, ArcNum);

    for (int i = 0; i < VexNum; i++)
    {
        char Vex;
        file >> Vex;
        net.InsertVex(Vex);
    }
    
    for (int i = 0; i < ArcNum; i++)
    {
        char from, to;
        int weight;
        file >> from >> to >> weight;
        net.InsertArc(from, to, weight);
    }
    return 1;
}

//������ȱ���
//��������
template <class DataType, class WeightType>
void DFS(const ALDirNetwork<DataType,WeightType> &g, int v,void(*visit)(const DataType &))
{
    DataType e;
    g.SetVisitedTag(v,VISITED);
    g.GetElem(v, e); visit(e);
    for(int w = g.GetFirstAdjvex(v); w != -1; w = g.GetNextAdjvex(v,w))
        if(g.GetVisitedTag(w) == UNVISITED)
            DFS(g, w, visit);
}
//�ӿں���
template <class DataType, class WeightType>
void DFSTraverse(const ALDirNetwork<DataType,WeightType> &graph,void(*visit)(const DataType &))
{
    for (int v = 0; v < graph.GetVexNum(); v++) {
        if (graph.GetVisitedTag(v) == UNVISITED) {
            DFS(graph, v, visit);
        }
    }
}


//������ȱ���
//��������
template <class DataType, class WeightType>
void BFS(const ALDirNetwork<DataType,WeightType> &g, int v,void(*visit)(const DataType &))
{
}
//�ӿں���
template <class DataType, class WeightType>
void BFSTraverse(const ALDirNetwork<DataType,WeightType> &graph,void(*visit)(const DataType &))
{
} 