using namespace std;

//在由3×3个方格构成的方阵填入1～n中的9个数字，每个方格填一个整数（不重复）
//使得所有相邻两个方格内的整数之和为素数。请设计算法求出所有满足这个要求的数字填法。

class DigitalGameProblem{
protected:
    int ub = 0;
    int ans[50][9];
    int count = 0;
    int tag[100];
    void Backtrack(int a[9], int q);
public:
    DigitalGameProblem(int u){ this->ub = u; };
    int **GetSolution();
    int Solve();
};

int Isprime(int i) //素数判断函数
{
    if (i == 1) return 0;
    if (i == 2) return 1;
    for (int j = 2; j * j <= i; j++)
        if (i % j == 0)
            return 0;
    return 1;
}

int DigitalGameProblem::Solve() {
    count = 0; // 重置解的数量
    int a[9] = {0}; // 初始化格子
    for (int i = 0; i < 100; ++i) {
        tag[i] = 0; // 初始化标记数组
    }
    Backtrack(a, 9); // 开始回溯搜索
    return count; // 返回解的数量
}

void DigitalGameProblem::Backtrack(int a[9], int q) {
    if (q == 0) { // 如果所有方格已经填满，存储解
        for (int i = 0; i < 9; i++) {
            ans[count][i] = a[i];
        }
        count++;
        return;
    }
    for (int i = 1; i <= ub; i++) {
        if (!tag[i]) { // 如果数字 i 未被使用
            if (q < 9) {
                int index = 9 - q;
                // 检查左侧和上侧是否满足素数条件
                if ((index % 3 > 0 && !Isprime(a[index - 1] + i)) ||
                    (index >= 3 && !Isprime(a[index - 3] + i))) {
                    continue;
                }
            }
            tag[i] = 1;
            a[9 - q] = i;
            Backtrack(a, q - 1);
            tag[i] = 0;
        }
    }
}

int** DigitalGameProblem::GetSolution() {
    if (count == 0) return nullptr;

    // 动态分配二维数组存储所有解
    int** result = new int*[count];
    for (int i = 0; i < count; i++) {
        result[i] = new int[9];
        for (int j = 0; j < 9; j++) {
            result[i][j] = ans[i][j];
        }
    }
    return result;
}