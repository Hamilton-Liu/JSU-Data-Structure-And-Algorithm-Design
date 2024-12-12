#include <algorithm>
#include <string.h>
using namespace std;

class RefuelProblem {
protected:
    int m, n, cnt;
    int* d;
    int ans[100];
public:
	RefuelProblem(int m, int n, int* d);	//构造函数
    int *GetSolution();			            //获取加油站解集
    int GetMinValue();                      //获取最少加油次数
    bool Solve();                           //求解
};

//已知一辆汽车加满油之后可以行驶d公里，而旅途中有n个加油站。
//设计一个算法求出应在哪些加油站停靠加油，可以使得加油次数最少。
//假设用数组a存放各加油站之间的距离，例如a[]={2，7，3，6}，表示共有n=4个加油站（编号为0～n-1），从起点到0号加油站的距离为2公里，依次类推。

RefuelProblem::RefuelProblem(int m, int n, int* d){
    this->m = m;    //满油可以行驶的里程
    this->n = n;    //加油站的数目
    this->d = new int[n];
    memcpy(this->d, d, n * sizeof(int));
    //初始化答案数组
    for(int i = 0; i < 100; i++){
        ans[i] = -1;
    }
}

bool RefuelProblem::Solve(){
    //贪心法求解
    cnt = 0;
    int s = d[1];
    for(int i = 0; i < n; i++){
        if(m < d[i]) return false;  //贪心小车偶遇超长公路，加油站偏僻远如怪物，耗尽全力未能抵达

        if(s + d[i+1] <= m){
            s += d[i];       //消耗里程累加
        }
        else{
            s = 0 + d[i+1];   //加油，重新计算里程
            ans[cnt] = i;     //加油站信息计入
            cnt ++;         //加油计数+1
        }
    }
    return true;
}

int *RefuelProblem::GetSolution(){
    return ans;
}

int RefuelProblem::GetMinValue(){
    return cnt;
}