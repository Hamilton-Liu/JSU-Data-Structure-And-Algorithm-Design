#pragma once
#include "Status.h"
#include "ALNetworkArc.h"
#include "ALNetworkVex.h"
const int DEFAULT_SIZE = 100;
const int DEFAULT_INFINITY = 0x3f3f3f3f;
template<class DataType, class WeightType>
class ALDirNetwork {
protected:
	int vexNum, vexMaxSize, arcNum;						//实际顶点数目，顶点数组容量和实际弧数
	WeightType infinity;								//存储表示无穷大的值
	ALNetworkVex<DataType, WeightType> *vexs;			//指向顶点数组的指针
	Status *visited;									//指向访问标志数组的指针
public:
	//构造函数，创建顶点数组容量为vexsize的空有向网
	ALDirNetwork(int vexsize = DEFAULT_SIZE, WeightType infinit = (WeightType)DEFAULT_INFINITY);
	//构造函数，创建包含vertexnum个顶点，没有弧的有向网
	ALDirNetwork(DataType data[], int vertexnum, int vexsize = DEFAULT_SIZE, WeightType infinit = (WeightType)DEFAULT_INFINITY);
	virtual ~ALDirNetwork();					 				//析构函数
	void Clear();										//清空有向网
	bool IsEmpty();										//判断有向网是否为空
	int GetOrder(const DataType &e) const;				//获取数据元素等于e的顶点序号
	Status GetElem(int v, DataType & e) const;			//获取顶点v的数据元素值
	Status SetElem(int v, const DataType &e);			//修改顶点v的数据元素值为e
	WeightType GetInfinity() const;						//获取表示无穷大的值
	int GetVexNum() const;								//获取当前顶点数目
	int GetArcNum() const;								//获取当前弧的数目
	int GetFirstAdjvex(int v) const;					//获取顶点v的第一个邻接点
	int GetNextAdjvex(int v1, int v2)const;				//获取顶点v1相对于v2的后继邻接点
	Status InsertVex(const DataType &e);				//插入数据元素值为e的顶点
	Status InsertArc(int v1, int v2, WeightType w);		//插入从顶点v1到v2，权为w的弧
	Status DeleteVex(const DataType &e);				//删除数据元素值为e的顶点
	Status DeleteArc(int v1, int v2);					//删除从顶点v1到v2的弧
	WeightType GetWeight(int v1, int v2) const; 		//获取从顶点v1到v2的弧的权值
	Status SetWeight(int v1, int v2, WeightType w);		//设置从顶点v1到v2的弧的权值为w
	Status GetVisitedTag(int v) const;					//获取顶点v的访问标志
	Status SetVisitedTag(int v, Status tag) const;		//修改顶点v的访问标志为tag
	void Display();										//显示有向网邻接表 
};

//构造函数，创建顶点数组容量为vexsize的空有向网
template<class DataType, class WeightType>
ALDirNetwork<DataType, WeightType>::ALDirNetwork(int vexsize, WeightType infinit)
{
	vexNum = 0;  vexMaxSize = vexsize;  arcNum = 0;  infinity = infinit;
	vexs = new ALNetworkVex<DataType, WeightType>[vexMaxSize]; 		//分配顶点数组
	visited = new Status[vexMaxSize]; 								//分配访问标志数组
	for(int v = 0; v < vexNum; v++) {								//初始化顶点数组、访问标志数组
		vexs[v].firstarc = NULL;
		visited[v] = UNVISITED;
	}
}

//构造函数，创建包含vertexnum个顶点，没有弧的有向网
template<class DataType, class WeightType>
ALDirNetwork<DataType, WeightType>::ALDirNetwork(DataType data[], int vertexnum, int vexsize, WeightType infinit) {
	if(vexsize < vertexnum)
	{
		cout << "顶点数目不能大于允许的顶点最大数目! ";  exit(0);
	}
	vexNum = vertexnum;  vexMaxSize = vexsize;  arcNum = 0;  infinity = infinit;
	vexs = new ALNetworkVex<DataType, WeightType>[vexMaxSize]; 		//分配顶点数组
	visited = new Status[vexMaxSize]; 								//分配访问标志数组
	for(int v = 0; v < vexNum; v++) {								//初始化顶点数组、访问标志数组
		vexs[v].data = data[v];  vexs[v].firstarc = NULL;
		visited[v] = UNVISITED;
	}
}

template<class DataType, class WeightType>
ALDirNetwork<DataType, WeightType>::~ALDirNetwork() {	//析构函数
	Clear();
	delete []vexs;
	delete []visited;
}

template<class DataType, class WeightType>
void ALDirNetwork<DataType, WeightType>::Clear() {		//清空有向网
	ALNetworkArc<WeightType> *p;
	for(int v = 0; v < vexNum; v++) {					//释放邻接点链表，重置访问标志数组
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
bool ALDirNetwork<DataType, WeightType>::IsEmpty() {	//判断有向网是否为空
	return vexNum ? false : true;
}

template<class DataType, class WeightType>
int ALDirNetwork<DataType, WeightType>::GetOrder(const DataType &e) const {	//获取数据元素等于e的顶点序号
	for(int v = 0; v < vexNum; v++)					//遍历顶点数组
		if(vexs[v].data == e)						//判断顶点的数据元素是否等于e
			return v;								//相等则返回顶点下标
	return -1;										//未找到，返回-1
}

template<class DataType, class WeightType>
Status ALDirNetwork<DataType, WeightType>::GetElem(int v, DataType & e) const {	//获取顶点v的数据元素值
	if(v < 0 || v >= vexNum)						//判断v是否越界
	{
		cout << "v取值不合法!" << endl;  return FAILED;
	}
	e = vexs[v].data;
	return SUCCESS;
}

template<class DataType, class WeightType>
Status ALDirNetwork<DataType, WeightType>::SetElem(int v, const DataType &e) {	//修改顶点v的数据元素值为e
	if(v < 0 || v >= vexNum)						//判断v是否越界
	{
		cout << "v取值不合法!" << endl;  return FAILED;
	}
	vexs[v].data = e;
	return SUCCESS;
}

template<class DataType, class WeightType>
WeightType ALDirNetwork<DataType, WeightType>::GetInfinity() const {	//获取表示无穷大的值
	return infinity;
}

template<class DataType, class WeightType>
int ALDirNetwork<DataType, WeightType>::GetVexNum() const {	//获取当前顶点数目
	return vexNum;
}

template<class DataType, class WeightType>
int ALDirNetwork<DataType, WeightType>::GetArcNum() const {	//获取当前弧的数目
	return arcNum;
}

template<class DataType, class WeightType>
int ALDirNetwork<DataType, WeightType>::GetFirstAdjvex(int v) const {	//获取顶点v的第一个邻接点
	if(v < 0 || v >= vexNum)						//判断v是否越界
	{
		cout << "v取值不合法!" << endl;  return -1;
	}
	if(vexs[v].firstarc == NULL)  return -1;		//不存在邻接点
	else  return vexs[v].firstarc->adjvex;			//返回第一个弧节点记录的弧头顶点序号
}

template<class DataType, class WeightType>
int ALDirNetwork<DataType, WeightType>::GetNextAdjvex(int v1, int v2) const {	//获取顶点v1相对于v2的后继邻接点
	ALNetworkArc<WeightType> *p;
	if(v1 < 0 || v1 >= vexNum) 						//判断v1是否越界
	{
		cout << "v1取值不合法!" << endl;  return -1;
	}
	if(v2 < 0 || v2 >= vexNum)						//判断v2是否越界
	{
		cout << "v2取值不合法!" << endl;  return -1;
	}
	if(v1 == v2) 									//判断v1和v2是否相等
	{
		cout << "v1与v2不能相等!" << endl;  return -1;
	}
	p = vexs[v1].firstarc;							//p指向弧链表的第一个弧节点
	while(p != NULL && p->adjvex != v2)				//寻找v2所在的弧节点
		p = p->nextarc;
	if(p == NULL || p->nextarc == NULL)  return -1;	//不存在后继邻接点
	else  return p->nextarc->adjvex;				//返回后继弧节点记录的弧头顶点序号
}

template<class DataType, class WeightType>
Status ALDirNetwork<DataType, WeightType>::InsertVex(const DataType &e) {	//插入数据元素值为e的顶点
	if(vexNum == vexMaxSize)  return OVER_FLOW;		//顶点数组已满
	vexs[vexNum].data = e;							//将顶点数据存储到顶点数组尾部
	vexs[vexNum].firstarc = NULL;	
	visited[vexNum] = UNVISITED;  vexNum++;
	return SUCCESS;
}

template<class DataType, class WeightType>
Status ALDirNetwork<DataType, WeightType>::InsertArc(int v1, int v2, WeightType w) {	//插入从顶点v1到v2，权为w的弧
	if(v1 < 0 || v1 >= vexNum) 						//判断v1是否越界
	{
		cout << "v1取值不合法!" << endl;  return FAILED;
	}
	if(v2 < 0 || v2 >= vexNum)						//判断v2是否越界
	{
		cout << "v2取值不合法!" << endl;  return FAILED;
	}
	if(v1 == v2) 									//判断v1和v2是否相等
	{
		cout << "v1与v2不能相等!" << endl;  return FAILED;
	}
	if(w == infinity)								//判断w取值是否为无穷
	{
		cout << "权值w不能为无穷大!" << endl;  return FAILED;
	}
	vexs[v1].firstarc = new ALNetworkArc<WeightType>(v2, w, vexs[v1].firstarc);
	arcNum++;
	return SUCCESS;
}

template<class DataType, class WeightType>
Status ALDirNetwork<DataType, WeightType>::DeleteArc(int v1, int v2) {	//删除从顶点v1到v2的弧
	if(v1 < 0 || v1 >= vexNum) 						//判断v1是否越界
	{
		cout << "v1取值不合法!" << endl;  return FAILED;
	}
	if(v2 < 0 || v2 >= vexNum)						//判断v2是否越界
	{
		cout << "v2取值不合法!" << endl;  return FAILED;
	}
	if(v1 == v2) 									//判断v1和v2是否相等
	{
		cout << "v1与v2不能相等!" << endl;  return FAILED;
	}
	ALNetworkArc<WeightType> *pre = NULL, *p;		//pre指向待删节点前驱，p指向待删节点
	p = vexs[v1].firstarc;							//p指向第一个弧节点
	while(p && p->adjvex != v2)						//寻找待删弧节点
	{
		pre = p;  p = p->nextarc;
	}
	if(!p)  return FAILED;							//未找到待删的弧节点，删除失败
	if(p == vexs[v1].firstarc)						//待删弧节点是弧链表的第一个节点
		vexs[v1].firstarc = p->nextarc;				//修改弧链表的头指针
	else											//待删弧节点不是弧链表的第一个节点
		pre->nextarc = p->nextarc;					//修改前驱节点的后继指针
	delete p;										//释放待删弧节点
	arcNum--;										//弧的数目减1
	return SUCCESS;
}

template<class DataType, class WeightType>
Status ALDirNetwork<DataType, WeightType>::DeleteVex(const DataType &e) {	//删除数据元素值为e的顶点
	int v = GetOrder(e);							//获取待删顶点的序号
	ALNetworkArc<WeightType> *p;
	if(v == -1)										//未找到该顶点
	{
		cout << "待删除的顶点不存在!" << endl;  return FAILED;
	}
	for(int w = 0; w < vexNum; w++)					//删除以v作为弧头顶点的弧
		if (w != v)  DeleteArc(w, v);
	p = vexs[v].firstarc;							//删除以v作为弧尾顶点的弧
	while(p) {										//依次释放弧链表中的弧节点
		vexs[v].firstarc = p->nextarc;
		delete p;  p = vexs[v].firstarc;
		arcNum--;
	}
	if(v != vexNum - 1) {							//若待删顶点不是最后一个顶点，需要移动
		vexs[v].data = vexs[vexNum - 1].data;		//复制顶点数据
		vexs[v].firstarc = vexs[vexNum - 1].firstarc;	//复制顶点的弧链表头指针
		vexs[vexNum - 1].firstarc = NULL;			//原弧链表头指针置为空指针
		visited[v] = visited[vexNum - 1];			//复制顶点访问状态信息
		//寻找弧头顶点为最后一个顶点的弧节点，修改其中的弧头顶点序号为v													
		for(int w = 0; w < vexNum - 1; w++)
			if(w != v) {
				for(p = vexs[w].firstarc; p; p = p->nextarc)
					if(p->adjvex == vexNum - 1)
						p->adjvex = v;
			}
	}
	vexNum--;										//顶点数目减1
	return SUCCESS;
}

template<class DataType, class WeightType>
WeightType ALDirNetwork<DataType, WeightType>::GetWeight(int v1, int v2) const {	//获取从顶点v1到v2的弧的权值
	if(v1 < 0 || v1 >= vexNum) 						//判断v1是否越界
	{
		cout << "v1取值不合法!" << endl;  return infinity;
	}
	if(v2 < 0 || v2 >= vexNum)						//判断v2是否越界
	{
		cout << "v2取值不合法!" << endl;  return infinity;
	}
	if(v1 == v2) 									//判断v1和v2是否相等
		return infinity;
	ALNetworkArc<WeightType> *p;
	p = vexs[v1].firstarc;							//p指向第一个弧节点
	while(p && p->adjvex != v2)						//寻找邻接点v2
		p = p->nextarc;
	if(!p)  return infinity;						//v2不是v1的邻接点，返回无穷
	return p->weight;								//返回从顶点v1到v2的弧的权值
}

template<class DataType, class WeightType>
Status ALDirNetwork<DataType, WeightType>::SetWeight(int v1, int v2, WeightType w) {	//设置从顶点v1到v2的弧的权值为w
	if(v1 < 0 || v1 >= vexNum) 						//判断v1是否越界
	{
		cout << "v1取值不合法!" << endl;  return FAILED;
	}
	if(v2 < 0 || v2 >= vexNum)						//判断v2是否越界
	{
		cout << "v2取值不合法!" << endl;  return FAILED;
	}
	if(v1 == v2) 									//判断v1和v2是否相等
	{
		cout << "v1与v2不能相等!" << endl;  return FAILED;
	}
	ALNetworkArc<WeightType> *p;
	p = vexs[v1].firstarc;							//p指向第一个弧节点
	while(p && p->adjvex != v2)						//寻找邻接点v2
		p = p->nextarc;
	if(!p)  return FAILED;							//v2不是v1的邻接点，返回失败信息
	p->weight = w;									//修改从顶点v1到v2的弧的权值
	return SUCCESS;								
}

template<class DataType, class WeightType>
Status ALDirNetwork<DataType, WeightType>::GetVisitedTag(int v) const {	//获取顶点v的访问标志
	if(v < 0 || v >= vexNum)						//判断v是否越界
	{
		cout << "v取值不合法!" << endl;  return FAILED;
	}
	return visited[v];
}

template<class DataType, class WeightType>
Status ALDirNetwork<DataType, WeightType>::SetVisitedTag(int v, Status tag) const {	//修改顶点v的访问标志为tag
	if(v < 0 || v >= vexNum)						//判断v是否越界
	{
		cout << "v取值不合法!" << endl;  return FAILED;
	}
	visited[v] = tag;
	return SUCCESS;
}

template<class DataType, class WeightType>
void ALDirNetwork<DataType, WeightType>::Display()	//显示有向网邻接表
{
	ALNetworkArc<WeightType> *p;
	cout << "有向网共有" << vexNum << "个顶点，" << arcNum << "条边。" << endl;
	for(int v = 0; v < vexNum; v++) {				//显示第v个邻接链表
		cout << v << ":\t" << vexs[v].data;		// 显示顶点号
		p = vexs[v].firstarc;
		while(p != NULL) {
			cout << "-->(" << p->adjvex << "," << p->weight << ")";
			p = p->nextarc;
		}
		cout << endl;
	}
}

//读取数据并创建有向图graph
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

//深度优先遍历
//辅助函数
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
//接口函数
template <class DataType, class WeightType>
void DFSTraverse(const ALDirNetwork<DataType,WeightType> &graph,void(*visit)(const DataType &))
{
    for (int v = 0; v < graph.GetVexNum(); v++) {
        if (graph.GetVisitedTag(v) == UNVISITED) {
            DFS(graph, v, visit);
        }
    }
}


//广度优先遍历
//辅助函数
template <class DataType, class WeightType>
void BFS(const ALDirNetwork<DataType,WeightType> &g, int v,void(*visit)(const DataType &))
{
}
//接口函数
template <class DataType, class WeightType>
void BFSTraverse(const ALDirNetwork<DataType,WeightType> &graph,void(*visit)(const DataType &))
{
} 