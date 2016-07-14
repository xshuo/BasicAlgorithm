#ifdef __COMBO__
/*
ID: shuoxie1
PROG: combo
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <set>

#include <string.h>
using namespace std;

#define MAX_N 101

bool visit[MAX_N][MAX_N][MAX_N];
int cnt = 0;

void getNearNum(int a, int b, int c, int N) {
    int ar[] = {-2, -1, 0, 1, 2};
    for (int i = 0; i < 5; i++) {
        int tempa = (a + ar[i] + N) % N;
        if (tempa == 0) tempa = N;
        for (int j = 0; j < 5; j++) {
            int tempb = (b + ar[j] + N) % N;
            if (tempb == 0) tempb = N;
            for (int k = 0; k < 5; k++) {
                int tempc = (c + ar[k] + N) % N;
                if (tempc == 0) tempc = N;
                if (!visit[tempa][tempb][tempc]) {
                    cnt++;
                    visit[tempa][tempb][tempc] = true;
                    //cout << tempa << " " << tempb << " " << tempc << endl;
                }
            }
        }
    }
}

int main(int argc, char** args) {
    //ifstream fin(stdin);
    //ofstream fout(stdout);
    ifstream fin("combo.in");
    ofstream fout("combo.out");
    int N;
    int a1, a2, a3;
    int b1, b2, b3; 
    fin >> N;
    fin >> a1 >> a2 >> a3;
    fin >> b1 >> b2 >> b3;
    memset(visit, 0, sizeof(visit));
    getNearNum(a1, a2, a3, N);
    getNearNum(b1, b2, b3, N);
    fout << cnt << endl;
    return 0;
}
#endif