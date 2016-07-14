#ifdef __MILK__
/*
ID: shuoxie1
PROG: milk
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

typedef struct Node {
    int P;
    int A;
    bool operator< (const Node& x) {
        return P < x.P;
    }
} Node;

Node milkMakers[5010];
int main(int argc, char** args) {
    //ifstream fin(stdin);
    //ofstream fout(stdout);
    ifstream fin("milk.in");
    ofstream fout("milk.out");
    int N, M;
    fin >> N >> M;
    for (int i = 0; i < M; i++) {
        fin >> milkMakers[i].P >> milkMakers[i].A;
    }
    sort(milkMakers, milkMakers + M);
    int sum = 0;
    for (int i = 0; i < M; i++) {
        if (N > milkMakers[i].A) {
            sum += milkMakers[i].A * milkMakers[i].P;
            N -= milkMakers[i].A;
        } else {
            sum += N * milkMakers[i].P;
            break;
        }
    }
    fout << sum << endl;
    return 0;
}
#endif