#include <iostream>
using namespace std;
int Solve(int w[], int a, int b);

// 有n（n>3）个硬币（编号为1~n），其中一枚是假币，由于假币的重量较轻，可以采用天平称重的方式找到这枚假币。请利用分治法设计算法找到这枚假币，输出假币的编号。
int main(void)
{
	int n, truePos, result;//硬币数目，假币真实编号，查找结果
	int * weight;//硬币重量数组

	cout << "Please enter the number of coins(11):" << endl;
	cin >> n;//输入:11
	weight = new int[n + 1];
	for (int i = 1; i <= n; i++)
		weight[i] = 2;
	cout << "Please enter the serial number of counterfeit coin(6): " << endl;
	cin >> truePos;//输入:6
    weight[truePos] = 1;
	result = Solve(weight, 1, n);//------------------------------调用函数在编号为1..n的范围内寻找假币的编号
	if (result == truePos)
		cout << "You have found the serial number of counterfeit coin correctly that is " << result << endl;
	else
	{
		cout << "You have not found the serial number of counterfeit coin correctly." << endl;
		cout << "The correct serial number is " << truePos << " , but your result is " << result << endl;
	}
	delete []weight;

	system("pause");
	return 0;
}

int Solve(int w[], int a, int b){
    if (a == b) // 如果只有一个硬币，直接返回它的编号
        return a;

    int mid1 = 0;
    int mid2 = 0;
    if ((b-a)>3){
        mid1 = a + (b - a) / 3;  // 第一组的右端
        mid2 = b - (b - a) / 3;  // 第二组的左端
    }
    else{
        mid1 = a;
        mid2 = a + 1;
    }

    //计算sum1，sum2
    int sum1 = 0, sum2 = 0;
    for (int i = a; i <= mid1; i++) 
        sum1 += w[i]; // 计算第一组的总重量
    for (int i = mid1 + 1; i <= mid2; i++) 
        sum2 += w[i]; // 计算第二组的总重量

    //conquer
    if (sum1 == sum2) 
    {
        // 如果第一组和第二组相等，假币在第三组
        return Solve(w, mid2 + 1, b); // 递归查找第三组
    }
    else if (sum1 < sum2) 
    {
        // 如果第一组较轻，假币在第一组
        return Solve(w, a, mid1); // 递归查找第一组
    }
    else 
    {
        // 如果第二组较轻，假币在第二组
        return Solve(w, mid1 + 1, mid2); // 递归查找第二组
	}
}