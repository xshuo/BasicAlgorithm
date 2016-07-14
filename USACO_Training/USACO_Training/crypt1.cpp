#ifdef __CRYPT1__
/*
ID: shuoxie1
PROG: crypt1
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <string.h>
using namespace std;

int N;
int digits[10];
bool flag[10];

int ret = 0;
int num[5];

bool isCryptarithm(const int num[]) {
    int a = num[0] * 100 + num[1] * 10 + num[2];
    int b = num[3] * 10 + num[4];
    int c = num[4] * a;
    int d = num[3] * a;
    //cout << "----------------------";
    //cout << a << " " << b << " " << c << " " << d << " " << a * b << endl;
    if (c >= 1000 || d >= 1000)
        return false;
    int e = c % 10, f = c / 10 % 10 , g = c / 100;
    if (!flag[e] || !flag[f] || !flag[g])
        return false;
    e = d % 10; f = d / 10 % 10; g = d / 100;
    if (!flag[e] || !flag[f] || !flag[g])
        return false;
    c = a * b;
    d = c % 10; e = c / 10 % 10; f = c / 100 % 10; g = c / 1000;
    if (!flag[d] || !flag[e] || !flag[f] || !flag[g])
        return false;
    return true;
}

void dfs_num(int idx) {
    if (idx == 5) {
        if(isCryptarithm(num))
            ret++;
        return;
    }
    for (int i = 0; i < N; i++) {
        num[idx] = digits[i];
        dfs_num(idx + 1);
    }
}

int main(int argc, char** args) {
    //ifstream fin(stdin);
    //ofstream fout(stdout);
    ifstream fin("crypt1.in");
    ofstream fout("crypt1.out");
    memset(digits, 0, sizeof(digits));
    memset(flag, 0, sizeof(flag));
    fin >> N;
    for (int i = 0; i < N; i++) {
        fin >> digits[i];
        flag[digits[i]] = true;
    }
    dfs_num(0);
    fout << ret << endl;
    return 0;
}
#endif