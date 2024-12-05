#include <iostream>
using namespace std;
#include "MatrixSP.h"//------------包含矩阵最小路径和问题类的头文件

int **AllocateMemory(int row, int col)
{
	int **space = new int *[row];
	for (int i = 0; i < row; i++)
		space[i] = new int[col];
	return space;
}

void DeleteMemory(int **space, int row)
{
	for (int i = 0; i < row; i++)
		delete[]space[i];
	delete[]space;
}

int main(void)
{
	int **m;//存放矩阵元素的二维数组
	int r, c;//矩阵的行数和列数

	cout << "Please enter the number of rows of the matrix(4):" << endl;
	cin >> r;//输入矩阵行数：4
	cout << "Please enter the number of columns of the matrix(4):" << endl;
	cin >> c;//输入矩阵列数：4
	m = AllocateMemory(r, c);
	cout << "Please enter " << r * c << " integers(1 3 5 9 8 1 3 4 5 0 6 1 8 8 4 0):" << endl;
	//输入矩阵元素：1 3 5 9 8 1 3 4 5 0 6 1 8 8 4 0
	for(int i = 0; i < r; i++)
		for(int j = 0; j < c; j++)
			cin >> m[i][j];
	MatrixSP msp(m, r, c);//--------------建立矩阵路径最小和问题对象
	msp.Solve();//-----------调用对象的Solve函数，使用动态规划法寻找矩阵路径最小和、以及对应的路径	
	cout << "The minimum sum is:" << msp.GetMinSum() << endl;//-----------调用对象的GetMinSum函数获得矩阵路径最小和并输出
	cout << "The path is:" << endl;
	msp.ShowPath();//----------------调用对象的ShowPath函数输出路径
	cout << endl;
	DeleteMemory(m, r);

	system("pause");
	return 0;
}