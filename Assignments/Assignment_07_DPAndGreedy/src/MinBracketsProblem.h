#include <algorithm>
#include <string.h>
using namespace std;

class MinBracketsProblem {
protected:
    int dp[50][50];
    string str;
    int sol,len;
    bool IsMatching(char left, char right);
public:
	MinBracketsProblem(string str);	//构造函数
    int GetMinBrackets();			//获取最小和
    void Solve();                   //求解
};

//括号序列有()、{}和[]组成，“(([{}]))()”是合法的，而“(}{)”、“(}(}”和“({)}”都是不合法的。
//如果一个括号序列不合法，设计一个算法，求解使该序列成为合法的括号序列至少需要添加的括号数目。
//例如，“(}(}”最少需要添加4个括号成为合法括号序列，即变为“(){}(){}” 。

bool MinBracketsProblem::IsMatching(char left, char right) {
    return (left == '(' && right == ')') ||
           (left == '[' && right == ']') ||
           (left == '{' && right == '}');
}

MinBracketsProblem::MinBracketsProblem(string str){
    this->str = str;
    this->len = str.length();
    sol = 0;
    //初始化动态规划矩阵
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            if (i == j) dp[j][j] = 1;
            else dp[i][j] = 0;
        }
    }
}

void MinBracketsProblem::Solve(){
    if (len == 0) return;

    for (int length = 2; length <= len; length++) {     // 子串长度
        for (int i = 0; i <= len - length; i++) {       // 子串起点
            int j = i + length - 1;                     // 子串终点
            if (IsMatching(str[i], str[j])) {
                dp[i][j] = dp[i+1][j-1];
            } else {
                dp[i][j] = min(dp[i+1][j], dp[i][j-1]) + 1;
            }
        }
    }
    sol = dp[0][len-1];
}

int MinBracketsProblem::GetMinBrackets(){
    return sol;
}