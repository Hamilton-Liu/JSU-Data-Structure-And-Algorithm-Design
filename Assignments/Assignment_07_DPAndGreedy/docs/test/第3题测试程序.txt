#include <iostream>
using namespace std;
#include "RefuelProblem.h"//-----包含加油问题类的头文件

int main(void)
{
	int m, n, *d;
	cout << "Please enter the endurance mileage of the car(7):" << endl;
	cin >> m;//输入汽车加满油可以行驶的里程：7
	cout << "Please enter the number of petrol stations(4):" << endl;
	cin >> n;//输入加油站的数目：4
	cout << "Please enter the distance between petrol stations(2 7 3 6):" << endl;
	d = new int[n];
	for(int i = 0; i < n; i++)//输入加油站之间的距离，第一个数据表示汽车起点到第0号加油站的距离
		cin >> d[i];			//输入：2 7 3 6
	RefuelProblem RFP(m, n, d);	//------------定义一个加油问题对象
	if(RFP.Solve())//------------调用对象的Solve函数用贪心法求解最少加油次数，若存在方案返回true,不存在方案返回false
	{
		int *ans = RFP.GetSolution();//--------调用对象的GetSolution函数返回停靠的加油站编号，存放在ans数组中
		cout << "The minimum number of refueling is " << RFP.GetMinValue() << endl;//------调用对象的GetMinValue函数返回最少加油次数
		cout << "The serial number of petrol stations is:" << endl;
		for(int i = 0; i < RFP.GetMinValue(); i++)//输出停靠的加油站编号
			cout << ans[i] << ' ';
		cout << endl;
		delete[]ans;
	}
	else//没有解决方案
		cout << "No solutions!" << endl;
	
	system("pause");
	return 0;
}