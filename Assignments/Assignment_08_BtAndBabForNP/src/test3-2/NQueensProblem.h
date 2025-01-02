using namespace std;
#include <iostream>
#include <cmath>
#include <queue>

struct Node {
    int level;      // 当前处理到的行
    int* position;  // 皇后放置情况，position[i] 表示第 i 行皇后所在的列
    int priority;   // 优先级
};

class NQueensProblem {
protected:
    int n;           // 皇后数量
    Node* solution;  // 解的存储
    bool place(int level, int* position); // 判断是否可以放置皇后
    bool BranchAndBound();                // 优先队列法分支限界核心函数

public:
    NQueensProblem(int n); // 构造函数
    ~NQueensProblem();     // 析构函数
    bool Solve();          // 求解函数
    int* GetSolution();    // 返回存储解的数组
};

int abs(int a) { return (a>=0) ? a : -a; }

bool NQueensProblem::place(int i, int *q){
    if(i == 1) return true;
    for(int j = 1; j < i; j++)
        if ((q[i] == q[j]) || (abs(q[i]-q[j]) == abs(i-j)))
            return false;
        return true;
}

// 构造函数
NQueensProblem::NQueensProblem(int n){
    this->n = n;
    solution = nullptr;
}

// 析构函数
NQueensProblem::~NQueensProblem() {
    if (solution != nullptr) {
        delete[] solution->position;
        delete solution;
    }
}

// 优先队列法分支限界核心函数
bool NQueensProblem::BranchAndBound() {
    auto compare = [](Node* a, Node* b) { return a->priority > b->priority; };
    priority_queue<Node*, vector<Node*>, decltype(compare)> pq(compare);

    // 初始化根节点
    Node* root = new Node;
    root->level = 0;
    root->position = new int[n + 1]{0}; // 动态分配并初始化为 0
    root->priority = 0;
    pq.push(root);

    while (!pq.empty()) {
        Node* current = pq.top();
        pq.pop();

        if (current->level == n) { // 找到解
            solution = current;
            return true;
        }

        int nextLevel = current->level + 1;
        for (int col = 1; col <= n; col++) {
            Node* child = new Node;
            child->level = nextLevel;
            child->position = new int[n + 1];
            for (int i = 1; i <= n; i++) {
                child->position[i] = current->position[i];
            }
            child->position[nextLevel] = col;

            if (place(nextLevel, child->position)) {
                // 优先级计算（此处简单设为当前层次）
                child->priority = nextLevel;
                pq.push(child);
            } else {
                delete[] child->position;
                delete child; // 非合法结点，释放内存
            }
        }

        delete[] current->position;
        delete current; // 当前结点已扩展完毕，释放内存
    }

    return false; // 无解
}

// 调用优先队列法求解
bool NQueensProblem::Solve() {
    return BranchAndBound();
}

// 返回存储解的数组
int* NQueensProblem::GetSolution() {
    if (solution == nullptr) {
        return nullptr;
    }
    int* result = new int[n + 1];
    for (int i = 1; i <= n; i++) {
        result[i] = solution->position[i];
    }
    return result;
}