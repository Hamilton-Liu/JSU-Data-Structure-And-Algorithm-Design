#include <iostream>
using namespace std;
#include <string>
#include "MinBracketsProblem.h"//--------------包含最少括号问题类的头文件

int main(void)
{
	string str;

	cout << "Please enter a sequence of brackets including \'(\', \')\', \'[\', \']\', \'{\' and \'}'((}(}):" << endl;
	cin >> str;//输入：(}(}
	MinBracketsProblem mbp(str);//----------定义一个最少括号问题对象
	mbp.Solve();//-------------调用对象的Solve函数使用动态规划方法计算需要添加的最少的括号数目
	cout << "The minimum number of brackets to be added is: " << mbp.GetMinBrackets() << endl;//---------调用对象的GetMinBrackets函数返回需要添加的最少括号数目

	system("pause");
	return 0;
}