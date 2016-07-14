/*
ID: shuoxie1
PROG: wormhole
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <set>
#include <queue>
using namespace std;

#define N 15
typedef struct Point {
    int x;
    int y;
    Point(int _x = 0, int _y = 0) : x(_x), y(_y){};
}Point;

typedef struct Edge {
    int a;
    int b;
    Edge(int _a = 0, int _b = 0) : a(_a), b(_b){};
}Edge;

int n;
Point P[N];

bool flag[N];
Edge E[N];

int G[N][N];
int ret = 0;

//wrong solution
bool circuit() {
    int d[N];
    int i, j;
    for (i = 1; i <= n / 2; i++) {
        if (P[E[i].a].y == P[E[i].b].y)
            return true;
    }
    for (i = 1; i <= n / 2; i++) {
        G[E[i].a][E[i].b] = G[E[i].b][E[i].a] = 1;
    }
    for (i = 1; i <= n; i++) {
        for (j = i + 1; j <= n; j++) {
            if (P[i].y == P[j].y)
                G[i][j] = G[j][i] = 1;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1 ; j <= n; j++) {
            d[i] = G[i][j] + G[j][i];
        }
    }
    set<int> s;
    queue<int> q;
    for (int i = 1; i <= n; i++)
        s.insert(i);
    for (int i = 1; i <= n; i++) {
        if (d[i] <= 1) {
            q.push(i);
            s.erase(i);
        }
    }
    while (!q.empty()) {
        int i = q.front();
        q.pop();
        for (int j = 1; j <= n; j++) {
            if (G[i][j]) {
                d[j]--;
                if (d[j] <= 1) {
                    q.push(j);
                    s.erase(i);
                }
            }
        }
    }
    if (s.empty())
        return false;
    else return true;
}

void build_g(int c) {
    if (c > n / 2) {
        if (circuit()) ret++;
        return;
    }
    int i, j;
    for (i = c; i <= n; i++) {
        if (flag[i]) continue;
        flag[i] = true;
        for (j = i + 1; j <= n; j++) {
            if (flag[j]) continue;            
            flag[j] = true;
            E[c].a = i;
            E[c].b = j;
            build_g(c + 1);
            flag[j] = false;
        }
        flag[i] = false;
    }
    return;
}

int main(int argc, char** args) {
    ifstream fin(stdin);
    ofstream fout(stdout);
    //ifstream fin("wormhole.in");
    //ofstream fout("wormhole.out");
    fin >> n;
    for (int i = 1; i <= n; i++) {
        fin >> P[i].x >> P[i].y;
    }
    build_g(1);
    return 0;
}


//////////////////////////////////////////////////////////////
//楼上代码都没有注释- -知道自己风格糟糕至少加点注释啊……如果感觉两份代码有些相似不是错觉，各有借鉴- -
//貌似我的叙述有问题……下文的“边”不是指两点之间的边，而是矩阵里的一行的意思……
/*
ID: wtx97071
PROG: wormhole
LANG: C++
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<vector>
#include<queue>
#include<map>
#include<set>
#include<cmath>
#include<algorithm>
using namespace std;
struct SaveNode{
    int x, y;
    bool vis;
};
struct Node{
    int x, tx, ty;// tx、ty : 与(x, y)相连点的坐标 
};
struct Line{
    int y;
    vector<Node> node;
};
vector<SaveNode> s;// 按输入存点(用于配对); 
vector<Line> graph;// 按位置存点(用于判断是否有环); 
//graph[i] : 纵数第i条边 ;
//graph[i].node[j] : 这条边上的第j个点 ; 
int N, ans = 0;
bool vis[20][20];
void insnode(int x, int j){//insert_node 按序插入一个点 
    for(int i = 0; i < graph[j].node.size(); ++i)
        if(x < graph[j].node[i].x){
            graph[j].node.insert(graph[j].node.begin() + i, (Node){x, -1, -1});
            return;
        }
    graph[j].node.push_back((Node){x, -1, -1});
    return;
}
void insline(int x, int y){//insert_line 按序插入一条边（并在该边上插入一个点） 
    for(int i = 0; i < graph.size(); ++i)
        if(y < graph[i].y){
            graph.insert(graph.begin() + i, (Line){y});
            insnode(x, i);
            return;
        }
    vector<Node> temp;
    temp.push_back((Node){x, -1, -1});
    graph.push_back((Line){y,temp});
    return;
}
bool isloop(int y, int x){
    int lx = x,
        ly = y;
    while(lx < graph[ly].node.size()){
        if(vis[lx][ly]){
            memset(vis, 0, sizeof(vis));
            return true;
        }
        vis[lx][ly] = 1;
        int tx = graph[ly].node[lx].tx,
            ty = graph[ly].node[lx].ty;
        ++tx;
        lx = tx;
        ly = ty;
    }
    memset(vis, 0, sizeof(vis));
    return false;
}
bool haveloop(){
    for(int i = 0; i < graph.size(); ++i)
        for(int j = 0; j < graph[i].node.size(); ++j)
            if(isloop(i, j))return true;
    return false;
}
void makepair(int i, int j){
    int x1 = s[i].x,
        y1 = s[i].y,
        x2 = s[j].x,
        y2 = s[j].y;
    graph[y1].node[x1].tx = x2;
    graph[y1].node[x1].ty = y2;
    graph[y2].node[x2].tx = x1;
    graph[y2].node[x2].ty = y1;
}
void remake(int i, int j){//实际不需要这个函数，因为值会覆盖不用重置，不过还是写了…… 
    int x1 = s[i].x,
        y1 = s[i].y,
        x2 = s[j].x,
        y2 = s[j].y;
    graph[y1].node[x1].tx =
    graph[y1].node[x1].ty =
    graph[y2].node[x2].tx =
    graph[y2].node[x2].ty = -1;
}
void find(int num){//配对(num为剩余还未配对的次数) 
    if(num == 0){
        if(haveloop())++ans;
        return;
    }
    int t;
    for(int i = 0; i < N; ++i)
        if(!s[i].vis){
            t = i;
            s[t].vis = 1;
            break;
        }
    for(int i = t + 1; i < N; ++i)
        if(!s[i].vis){
            s[i].vis = 1;
            makepair(t, i);
            find(num - 1);
            remake(t, i);
            s[i].vis = 0;
        }
    s[t].vis = 0;
}
int main(){
    freopen("wormhole.in","r",stdin);
    freopen("wormhole.out","w",stdout);
    cin >> N;
    memset(vis, 0, sizeof(vis));
    for(int i = 0; i < N; ++i){
        int ix, iy;
        cin >> ix >> iy;
        int have = 0;
        for(int j = 0; j < graph.size(); ++j)
            if(graph[j].y == iy){
                insnode(ix, j);
                have = 1;
                break;
            }
        if(!have)insline(ix, iy);
    }
    for(int i = 0; i < graph.size(); ++i){//将相邻节点的距离压缩为1
        graph[i].y = i;
        for(int j = 0; j < graph[i].node.size(); ++j){
            graph[i].node[j].x = j;
            s.push_back((SaveNode){j, i, 0});//j是横坐标x，i是纵坐标y
        }
    }
    //以上为输入部分 
    find(N / 2);//配对并计数 
    cout << ans << endl;
    return 0;
}
