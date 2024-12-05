#include <iostream>
#include <cmath>
using namespace std;

//给定一个n位的正整数d，删除其中任意的k（k≤n）个数字之后，剩下的数字按照原次序排列构成一个新的正整数。
//对于给定的n位正整数d和正整数k，设计一个算法，使得删除之后剩下的数字构成的整数最小。

int DelDigit(int v, int k);

int main(void)
{
	long value;
	int k;

	cout << "Please enter an integer(3001527):" << endl;
	cin >> value;//输入待删除的整数：3001527
	cout << "Please enter the number of digits to be deleted(3):" << endl;
	cin >> k;//输入删除的位数：3
	value = DelDigit(value, k);//----------------调用DelDigit函数从value删除k位得到最小数
	cout << "After deletion, The smallest integer is: " << value << endl;//输出删除后得到的最小数

	system("pause");
	return 0;
}

int DelDigit(int v, int k){
	int res = 0;

	//把value转换为数组
	int t = v;
	int n = 0;
	while(t != 0){
		t /= 10;
		n ++;
	}
	int* a = new int[n];
	for(int i = n, j = 0; i > 0; i--, j++){
		a[j] = (v/(static_cast<int>(pow(10,i-1))))%10;
	}

	//贪心法
	int* b = new int[n];
	int count = 0;
	for(int i = 0; i < n && count!=k; i--){
		if(a[i] > a[i+1] || (a[i]!=0 && a[i+1] == 0)){
			a[i] = -1;
			count++;
		} 
	}

	//输出结果
	for(int i = 0; i < n; i++){
		res = res + a[i];
		res *= 10;
	}
	
	return res;
}