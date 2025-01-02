#include <iostream>
using namespace std;
#include "NQueensProblem.h"	//---------------------包含定义了n皇后问题类的头文件

//设计一个算法，采用队列式分支限界法求解4皇后问题的一个解。

int main()
{
	int n;

	cout << "Please enter the number of queens(4):" << endl;
	cin >> n;//输入皇后数目：4
	NQueensProblem nqp(n);		//------------定义一个n皇后问题的对象
	if(nqp.Solve())				//------------调用对象的Solve函数使用分支限界法求问题的1个解，有解返回true，否则返回false
	{
		int * ans = nqp.GetSolution();//----------调用对象的GetSolution函数返回问题的解
		cout << "The solution is:" << endl;
		for(int i = 1; i <= n; i++)
			cout << "row " << i << ": " << ans[i] << endl;
		delete []ans;
	}
	else
		cout << "No solutions!";
	
	system("pause");
	return 0;
}