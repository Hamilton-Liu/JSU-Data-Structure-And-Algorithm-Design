using namespace std;
#include <iostream>
#include <cmath>


class NQueensProblem {
protected:
    int n;         // 皇后数量
    int *q;        // 存储解，q[i] 表示第 i 行皇后所在的列
    bool place(int i, int *q); // 判断是否可以放置皇后
    bool BranchAndBound(); // 分支限界法核心函数

public:
    NQueensProblem(int n);   // 构造函数
    ~NQueensProblem();       // 析构函数
    bool Solve();            // 求解函数，调用分支限界法
    int* GetSolution();      // 返回存储解的数组
};

int abs(int a) { return (a>=0) ? a : -a; }

bool NQueensProblem::place(int i, int *q){
    if(i == 1) return true;
    for(int j = 1; j < i; j++)
        if ((q[i] == q[j]) || (abs(q[i]-q[j]) == abs(i-j)))
            return false;
        return true;
}

NQueensProblem::NQueensProblem(int n){
    this->n = n;
    q = new int[n + 1];  // 动态分配存储空间，行号从1开始
    for (int i = 1; i <= n; i++) {
        q[i] = 0;  // 初始化所有行的列号为0
    }
}

NQueensProblem::~NQueensProblem() {
    delete[] q;  // 释放动态分配的内存
}

bool NQueensProblem::BranchAndBound() {
    int i = 1;  // 当前处理的行
    q[i] = 0;   // 初始化第一行的列号

    while (i > 0) {
        q[i]++;  // 尝试当前行的下一个列

        // 如果当前位置不合法，则尝试当前行的下一个列
        while (q[i] <= n && !place(i, q)) {
            q[i]++;
        }

        if (q[i] <= n) { // 找到合法位置
            if (i == n) { // 如果已经处理到最后一行
                return true; // 找到一个解
            }
            i++;  // 进入下一行
            q[i] = 0;  // 初始化下一行
        } else { // 当前行没有合法位置
            i--;  // 回溯上一行
        }
    }

    return false; // 没有解
}

bool NQueensProblem::Solve() {
    return BranchAndBound(); // 调用分支限界法求解
}

int* NQueensProblem::GetSolution() {
    int* result = new int[n + 1];  // 动态分配存储解的数组
    for (int i = 1; i <= n; i++) {
        result[i] = q[i];  // 将解复制到 result 中
    }
    return result;  // 返回解
}