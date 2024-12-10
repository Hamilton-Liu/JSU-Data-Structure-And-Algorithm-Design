#include <iostream>
#include <cmath>
using namespace std;

//给定一个n位的正整数d，删除其中任意的k（k≤n）个数字之后，剩下的数字按照原次序排列构成一个新的正整数。
//对于给定的n位正整数d和正整数k，设计一个算法，使得删除之后剩下的数字构成的整数最小。

int DelDigit(int v, int k);

int findMax(int a[], int size) {
    int max = 0;
	int i = 0;
	for (i = 0; i < size; i++) {
        if (a[i] > a[max]) {
            max = i;
        }
    }
    return max;
}

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
	int i,j = 0;

	//把value转换为数组
	int t = v;
	int n = 0;
	while(t != 0){
		t /= 10;
		n ++;
	}
	int a[10010] = {0};
	for(i = n, j = 0; i > 0; i--, j++){
		a[j] = (v/(static_cast<int>(pow(10,i-1))))%10;
	}

	//贪心
	bool iszero = false;
	int zcnt=0,dcnt=0;

	for(i = 0; i < n; i++){
		if(a[i] == 0){
			iszero = true;
			break;
		}
	}
	if(iszero){
		i = 0;
		while(a[i] != 0){
			zcnt++;
			i++;
		}
		if (zcnt <= k){
			for(i = 0; i < zcnt; i++){
				a[i] = -1;
				dcnt++;
			}
		}
	}
	for(; dcnt<k; dcnt++){
		a[findMax(a,n)] = -1;
	}

	//后处理，防止0在开头输出
	i = 0;
	while(a[i] == 0 || a[i] == -1){
		if(a[i] == 0) a[i] = -1;
		i++;
	}

	//输出结果
	for(i = 0; i < n; i++){
		if(a[i] != -1){
			res = res * 10 + a[i];
		}
	}
	
	return res;
}