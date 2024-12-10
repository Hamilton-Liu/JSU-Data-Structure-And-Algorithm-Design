#include <algorithm>
using namespace std;

class MatrixSP {
protected:
    int dp[50][50];
    pair<int, int> tag[50][50];
	int **m;
    int r,c;
    void ShowPath(int i, int j);          //展示路径辅助函数
public:
	MatrixSP(int **m, int r, int c);	//构造函数
    int GetMinSum();			//获取最小和
    void ShowPath();          //展示路径
    void Solve();             //求解
};

//	给定一个m行n列的矩阵，从左上角开始每次只能向右或向下移动，最后到达右下角的位置，移动路径上的数字之和作为这条路径的路径和。
//	设计一个算法求所有路径和中的最小路径和。

MatrixSP::MatrixSP(int **m, int r, int c){
    this->m = m;
    this->r = r;
    this->c = c;
    //初始化动态规划矩阵和标记矩阵
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            dp[i][j] = 0;}}

}

void MatrixSP::Solve(){
    //动态规划求解
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            if(i == 0 && j == 0){
                dp[i][j] = m[i][j];
                tag[i][j].first = 0;
                tag[i][j].second = 0;
            }
            else
            if(i == 0 && j != 0){
                dp[i][j] = dp[i][j-1] + m[i][j];
                tag[i][j].first = i;
                tag[i][j].second = j-1;
            }
            else
            if(i != 0 && j == 0){
                dp[i][j] = dp[i-1][j] + m[i][j];
                tag[i][j].first = i-1;
                tag[i][j].second = j;
            }
            else
            {
                dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + m[i][j];
                if (dp[i-1][j] < dp[i][j-1])
                {
                    tag[i][j].first = i-1;
                    tag[i][j].second = j;
                }
                else
                {
                    tag[i][j].first = i;
                    tag[i][j].second = j-1;
                }
            }
        }
    }
}

int MatrixSP::GetMinSum(){
    return dp[r-1][c-1];
}

void MatrixSP::ShowPath(int i, int j) {
    if (i == 0 && j == 0) {
        cout << m[i][j] << " ";
        return;
    }
    ShowPath(tag[i][j].first, tag[i][j].second);
    if(i == r-1 && j == c-1) 
        cout << m[i][j];
    else
        cout << m[i][j] << " ";
}
void MatrixSP::ShowPath(){
    ShowPath(r-1,c-1);
}