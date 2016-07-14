#ifdef __MILK2__
/*
ID: shuoxie1
PROG: milk2
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
using namespace std;

bool visit[1000001];
int main(int argc, char** args) {
    //ifstream fin(stdin);
    //ofstream fout(stdout);
    ifstream fin("milk2.in");
    ofstream fout("milk2.out");
    int i, j;
    int max = 0, max2 = 0;
    int N;
    fin >> N;
    int start, end, min_start = 1 << 30, max_end = 0;
    memset(visit, 0x00, sizeof(visit));
    for (i = 0; i < N; i++) {
        fin >> start >> end;
        if (start < min_start)
            min_start = start;
        if (end > max_end)
            max_end = end;
        memset(visit + start, 0x01, sizeof(bool) * (end - start));
    }
    int cnt;
    for (i = min_start; i < max_end;) {
        if (visit[i] == true) {
            cnt = 0;
            while (i < max_end && visit[i]) {
                cnt++;
                i++;
            }
            if (cnt > max)
                max = cnt;
        }
        if (visit[i] == false) {
            cnt = 0;
            while (i < max_end && !visit[i]) {
                cnt++;
                i++;
            }
            if (cnt > max2)
                max2 = cnt;
        }
    }
    fout << max << " " << max2 << endl;
    return 0;
}
#endif