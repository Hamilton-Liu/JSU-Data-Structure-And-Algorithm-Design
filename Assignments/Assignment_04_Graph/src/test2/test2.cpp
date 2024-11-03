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

	system("pause");
	return 0;
}