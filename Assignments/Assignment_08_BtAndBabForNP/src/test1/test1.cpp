#include <iostream>
using namespace std;
#include <iomanip>
#include "DigitalGameProblem.h"	//-----------包含填数字游戏问题类的头文件

//在由3×3个方格构成的方阵填入1～n中的9个数字，每个方格填一个整数（不重复）
//使得所有相邻两个方格内的整数之和为素数。请设计算法求出所有满足这个要求的数字填法。

int main(void)
{
	int ub;
	cout << "Please enter the upper bound of digits to be filled in 3 * 3 grid(10):" << endl;//提示输入填入数字的上界
	cin >> ub;//输入：10，即填入的数字为1..10
	DigitalGameProblem DGP(ub);		//------------定义一个在3*3的方格内填数字游戏的对象，可以填入的数字是1~ub
	int count = DGP.Solve();		//------------调用对象的Solve函数利用回溯法求解在全部解决方案，返回解决方案数目
	if(count)
	{
		int ** ans = DGP.GetSolution();		//-----------调用对象的GetSolution函数返回所有解决方案，存储在ans指向的二维数组之中
		cout << "The number of solutions is: " << count << endl;
		cout << "All solutions are shown as follows:" << endl;
		for(int i = 0; i < count; i++)
		{
			cout << "Solution " << i + 1 << ":" << endl;
			for(int j = 0; j < 9; j++)
			{
				cout << setw(3) << ans[i][j];
				if((j + 1) % 3 == 0)
					cout << endl;
			}
		}
		for(int i = 0; i < count; i++)
			delete[]ans[i];
		delete[]ans;
	}
	else
		cout << "No solutions!" << endl;

	system("pause");
	return 0;
}