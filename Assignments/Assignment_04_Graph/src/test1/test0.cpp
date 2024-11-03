#include <iostream>
using namespace std;
#include <fstream>
#include <string>
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

	//���ļ�GraphData.txt�ж�ȡ����ͼ���ݣ�����ͼgraph
	if(!LoadData(graph))//--------------------����LoadData�������ļ�GraphData.txt��ȡ����ͼ���ݽ���ͼgraph�����Լ�ʵ��
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
	
	system("pause");
	return 0;
}