#ifdef __BARN1__
/*
ID: shuoxie1
PROG: barn1
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <string.h>
using namespace std;
#define N 210

int M, S, C;
int stall[N];

int main(int argc, char** args) {
    //ifstream fin(stdin);
    //ofstream fout(stdout);
    ifstream fin("barn1.in");
    ofstream fout("barn1.out");
    int i, j, sum = 0;
    int count[N];
    fin >> M >> S >> C;
    memset(stall, 0, sizeof(stall));
    memset(count, 0, sizeof(count));
    int color = 1;
    int min = 1 << 20, max = -1;
    for (i = 0; i < C; i++) {
        fin >> j;
        stall[j] = color;
        if (j > max)
            max = j;
        if (j < min)
            min = j;
    }
    color++;
    for (i = min; i <= max; i++) {
        if (stall[i] == 1)
            continue;
        int cnt = 0;
        while (i <= S && stall[i] == 0) {
            stall[i] = color;
            i++;
            cnt++;
        }
        count[color] = cnt;
        color++;
    }
    sort(count, count + N, greater<int>());
    for (i = 0; i < M - 1; i++) {
        sum += count[i];
    }
    int ret = max - min + 1 - sum;
    fout << ret << endl;
    return 0;
}
#endif