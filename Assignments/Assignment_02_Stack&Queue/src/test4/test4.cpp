#include <iostream>
using namespace std;
#include "Status.h"
#include "LinkQueue.h"

//二项式(a+b)^n展开后，其系数构成杨辉三角形，写出利用队列实现输出杨辉三角形前n行的算法。杨辉三角输出格式如下例所示。
//n=5时，共计输出5行。
//对于第i（i=1, 2, 3, 4, 5）行，首先输出n-i个空格；然后输出该行数据，数据之间用1个空格间隔；最后一个数据的后面有1个空格。

Status YangHui(int n){
	LinkQueue<int> queue;			//创建链队列
	queue.EnQueue(1);
	queue.EnQueue(1);				//初始化队列
	int t1 = 0, t2 = 0;				//创建暂存变量t1和t2
	for(int i = 1; i <= n; i++)
	{									//对从1到n的每一行进行操作
		t2 = 0;							//每行手动重置t2的值（t2为上一个出队的值）
		cout << string(n - i, ' ');		//首先输出n-i个空格
		for(int j = 0;j < i+1; j++)
		{								//第i行进行i+1次出队，并完成和元素的入队
			queue.DelQueue(t1);			//出队，储存到t1中
			cout << t1 << ' ';			//输出t1（首元素）
			queue.EnQueue(t1+t2);		//t1+t2入队（上一次出队的值加刚出队的值）
			t2 = t1;					//把t1（刚出队）的值存放到t2中
		}
		queue.EnQueue(1);				//加法部分结束，入队1
		cout << endl;					//换行
	}
	return SUCCESS;
}

int main(void)
{
	int n;

	cout << "Please enter the order of binomial(5):" << endl;
	do{
		cin >> n;//输入5
		if(n <= 0)
			cout << "The order of binomial must be greater than 0, please re-enter(5):" << endl;
	}while(n <= 0);
	cout << "The Yang Hui triangle with order " << n << " is as follows:" << endl;
	YangHui(n);//------------------------------调用生成与打印杨辉三角的函数
	cout << endl;

	cout << "Please enter the order of binomial(8):" << endl;
	do{
		cin >> n;//输入8
		if(n <= 0)
			cout << "The order of binomial must be greater than 0, please re-enter(8):" << endl;
	}while(n <= 0);
	cout << "The Yang Hui triangle with order " << n << " is as follows:" << endl;
	YangHui(n);//------------------------------调用生成与打印杨辉三角的函数

	system("pause");
	return 0;
}