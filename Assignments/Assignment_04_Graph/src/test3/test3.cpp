#include <iostream>
using namespace std;
#include <fstream>
#include "Status.h"
#include "ALNetworkArc.h"
#include "ALNetworkVex.h"
#include "ALDirNetwork.h"
#include "Node.h"
#include "LinkQueue.h"

void Display(const char &e)
{    cout << e << " ";    }


//（3）利用Dijkstra算法求指定源点到其余各顶点的最短路径,要求输出最短路径及其长度。
int main(void)
{
	ALDirNetwork<char,int> graph(20,9999);
	char start,end;

	//从文件GraphData.txt中读取有向图数据，建立图graph
	if(!LoadData(graph))//--------------------调用LoadData函数从文件GraphData.txt读取有向图数据建立图graph，请自己实现
	{
		cout << "Failed to create graph!" << endl;
		exit(1);
	}
	cout << "The depth first traversal sequence of the graph is:" << endl;
	DFSTraverse(graph,Display);
	cout << endl;
	cout << "The breadth first traversal sequence of the graph is:" << endl;
	BFSTraverse(graph,Display);
	cout << endl;
	//-----------------------------以下测试第1小题------------------------------------------------
	start = 'A';	end = 'G';
	if(ExistPathDFS(graph,start,end))//------------------调用第1小题函数--------------------------
		cout << "According to the depth first search strategy, there is a path between "<< start << " and " << end << endl;
	else
		cout << "According to the depth first search strategy, there is no path between "<< start << " and " << end << endl;
	start = 'B';	end = 'I';
	if (ExistPathDFS(graph, start, end))//------------------调用第1小题函数--------------------------
		cout << "According to the depth first search strategy, there is a path between " << start << " and " << end << endl;
	else
		cout << "According to the depth first search strategy, there is no path between " << start << " and " << end << endl;
	//-----------------------------以下测试第2小题------------------------------------------------
	start = 'A';	end = 'H';
	if(ExistPathBFS(graph,start,end))//------------------调用第2小题函数--------------------------
		cout << "According to the breadth first search strategy, there is a path between " << start << " and " << end << endl;
	else
		cout << "According to the breadth first search strategy, there is no path between "<< start << " and " << end << endl;
	start = 'C';	end = 'G';
	if(ExistPathBFS(graph, start, end))//------------------调用第2小题函数--------------------------
		cout << "According to the breadth first search strategy, there is a path between " << start << " and " << end << endl;
	else
		cout << "According to the breadth first search strategy, there is no path between " << start << " and " << end << endl;
	//-----------------------------以下测试第3小题------------------------------------------------
	//cout << "Please enter the start point for calculating the shortest path(A):" << endl;
	//cin >> start;//输入：A
	int *path = new int[graph.GetVexNum()],*dist = new int[graph.GetVexNum()];
	start = 'A';
	Dijkstra(graph,graph.GetOrder(start), dist, path);//------------------调用第3小题函数--------------------------
	//输出起点到所有顶点的最短路径和最短路径长度
	OutputShortestPath(graph,graph.GetOrder(start), dist, path);//-------------------调用OutputShortestPath函数输出结果，请自己实现
	start = 'C';
	Dijkstra(graph, graph.GetOrder(start), dist, path);//------------------调用第3小题函数--------------------------
	 //输出起点到所有顶点的最短路径和最短路径长度
	OutputShortestPath(graph, graph.GetOrder(start), dist, path);//-------------------调用OutputShortestPath函数输出结果，请自己实现
	delete []path;
	delete []dist;

	system("pause");
	return 0;
}