#include <iostream>
using namespace std;
#include <string>
#include "MinBracketsProblem.h"//--------------包含最少括号问题类的头文件

//括号序列有()、{}和[]组成，“(([{}]))()”是合法的，而“(}{)”、“(}(}”和“({)}”都是不合法的。
//如果一个括号序列不合法，设计一个算法，求解使该序列成为合法的括号序列至少需要添加的括号数目。
//例如，“(}(}”最少需要添加4个括号成为合法括号序列，即变为“(){}(){}” 。

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