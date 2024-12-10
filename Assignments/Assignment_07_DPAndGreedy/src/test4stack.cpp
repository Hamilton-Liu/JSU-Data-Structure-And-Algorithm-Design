#include <iostream>
#include <vector>
using namespace std;

// 给定一个n位的正整数d，删除其中任意的k（k≤n）个数字之后，剩下的数字按照原次序排列构成一个新的正整数。
// 对于给定的n位正整数d和正整数k，设计一个算法，使得删除之后剩下的数字构成的整数最小。

int DelDigit(int v, int k);

int main(void) {
    long value;
    int k;

    cout << "Please enter an integer(3001527):" << endl;
    cin >> value; // 输入待删除的整数：3001527
    cout << "Please enter the number of digits to be deleted(3):" << endl;
    cin >> k; // 输入删除的位数：3
    value = DelDigit(value, k); // 调用DelDigit函数从value删除k位得到最小数
    cout << "After deletion, The smallest integer is: " << value << endl; // 输出删除后得到的最小数

    system("pause");
    return 0;
}

int DelDigit(int v, int k) {
    vector<int> digits;
    int temp = v;
    
    // 把value转换为数组
    while (temp > 0) {
        digits.push_back(temp % 10);
        temp /= 10;
    }
    // 手动反转数组
    int n = digits.size();
    for (int i = 0; i < n / 2; ++i) {
        swap(digits[i], digits[n - i - 1]);
    }

    // 贪心策略
    vector<int> result;
    int to_delete = k;
    for (int i = 0; i < n; ++i) {
        while (!result.empty() && result.back() > digits[i] && to_delete > 0) {
            result.pop_back();
            to_delete--;
        }
        result.push_back(digits[i]);
    }

    // 如果还需要删除更多的数字，则从末尾删除
    while (to_delete > 0) {
        result.pop_back();
        to_delete--;
    }

    // 构建结果
    int res = 0;
    bool leadingZero = true;
    for (int digit : result) {
        if (digit == 0 && leadingZero) {
            continue; // 跳过前导零
        }
        leadingZero = false;
        res = res * 10 + digit;
    }

    // 如果结果为空，返回0
    if (res == 0 && result.empty()) {
        return 0;
    }

    return res;
}