#ifdef __1426__
#include <iostream>
#include <queue>
#include <limits>
#include <string>

using std::queue;

#define MAX_N 110

int baseN;
bool flag;

#define __1426_BFS1_

#ifdef __1426_DFS1_
void dfs_num(unsigned __int64 n) {
    if (flag) return;
    if (n * 10 < n)
        return;
    if (n % baseN == 0) {
        printf("%I64u\n", n);
        flag = true;
        return;
    }
    dfs_num(n * 10);
    dfs_num(n * 10 + 1);
}

int main(int argc, char** args) {
    while (scanf("%d", &baseN)) {
        if (baseN == 0) break;
        flag = false;
        dfs_num(1);
    }
}

#elif defined __1426_DFS2_
///////////////////////////////////
//Time Limit Exceeded
int num[MAX_N];
bool find_multiple(int n) {
    int sum = 1;
    for (int i = 1; i < n; i++) {
        sum = (sum * 10 + num[i]) % baseN;
    }
    if (sum == 0) return true;
    else return false;
}

void print(int n) {
    for (int i = 0; i < n; i++) 
        printf("%d", num[i]);
    printf("\n");
}

void dfs_num(int n) {
    if (flag || n >= 20)
        return;
    if (find_multiple(n)) {
        flag = true;
        print(n);
        return;
    }
    for (int i = 0; i <= 1; i++) {
        num[n] = i;
        dfs_num(n + 1);
    }
}

int main(int argc, char** args) {
    while (scanf("%d", &baseN)) {
        if (baseN == 0) break;
        flag = false;
        num[0] = 1;
        dfs_num(1);
    }
}

#elif defined __1426_BFS1_
#define MAX_Q 500
using std::string;
string q[MAX_Q];
int head, tail, q_size;

bool find_multiple(string s) {
    int sum = 0;
    for (int i = 0; i < s.size(); i++) {
        sum = (sum * 10 + (s[i] - '0')) % baseN;
    }
    if (sum == 0) return true;
    return false;
}

void bfs_num(string start) {
    head = tail = q_size = 0;
    q[tail++] = start;
    q_size++;
    while (q_size) {
        string s = q[(head++) % MAX_Q];
        q_size--;
        if (find_multiple(s)) {
            std::cout << s << std::endl;
            break;
        }
        q[(tail++) % MAX_Q] = s + '0';
        q_size++;
        q[(tail++) % MAX_Q] = s + '1';
        q_size++;
    }
}

int main(int argc, char** args) {
    while (scanf("%d", &baseN)) {
        if (baseN == 0) break;
        bfs_num("1");
    }
    return 0;
}
#endif
#endif
