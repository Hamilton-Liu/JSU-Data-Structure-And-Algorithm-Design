#include <iostream>
using namespace std;
int GetMode(int arr[], int a, int b, int &m);

//在一个整数序列中，每个元素出现的次数称为重数，重数最大的元素称为众数。现已知一个长度为n的递增有序的整数序列，请利用分治法设计算法寻找该序列的众数。
int main(void)
{
	int n;//整数数目
	int *a;//整数数组
	int mode, max;//mode：众数，max：众数的重数
	
	cout << "Please enter the number of integers(12):" << endl;
	cin >> n;//输入：12
	a = new int[n];
	cout << "Please enter " << n << " integers in ascending order(1 2 2 3 3 3 3 3 6 6 6 6):" << endl;//输入：1 2 2 3 3 3 3 3 6 6 6 6
	for (int i = 0; i < n; i++)
		cin >> a[i];
	max = 0;
	mode = GetMode(a, 0, n - 1, max);//------------------调用函数在数组a中从下标0到n-1的范围中寻找众数mode，其重数为max
	cout << "The mode of the sequence is: " << mode << endl;
	cout << "And the count is: " << max << endl;
	delete []a;

	system("pause");
	return 0;
}

int GetMode(int arr[], int a, int b, int &m) {
    if (a == b) {   //区间只有一个元素
        m = 1;      //重数为1
        return arr[a];
    }

    int mid = (a + b) / 2;
    int leftM, rightM; // 特殊情况下的众数重数
    int leftMode = GetMode(arr, a, mid, leftM);
    int rightMode = GetMode(arr, mid + 1, b, rightM);

    // 合并结果
    if (leftMode == rightMode) {//两边众数相同
        m = leftM + rightM;
        return leftMode;
    } else {
        // 如果两边众数不同，计算跨界的重数
        int leftCount = leftM;
        int rightCount = rightM;
        int midCount = 0;

        // 向左统计右众数
        for (int i = mid; i >= a; i--) {
            if(arr[i] == rightMode)
                rightCount++;
        }
        // 向右统计左众数
        for (int i = mid + 1; i <= b; i++) {
            if(arr[i] == leftMode)
                leftCount++;
        }
        // 统计中间两边的数的重数
        if (arr[mid]==arr[mid+1])
        {
            for (int i = mid; i >= a; i--) {
            if(arr[i] == arr[mid])
                midCount++;
            }

            for (int i = mid + 1; i <= b; i++) {
            if(arr[i] == arr[mid])
                midCount++;
            }
        }
        
        // 比较跨界后的重数，确定最终众数
       if (leftCount < midCount && midCount > rightCount){
            m = midCount;
            return arr[mid];
        } else if (leftCount > rightCount) {
            m = leftCount;
            return leftMode;
        } else {
            m = rightCount;
            return rightMode;
        }
    }
}