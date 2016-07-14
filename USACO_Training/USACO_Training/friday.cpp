#ifdef __FRIDAY__
/*
ID: shuoxie1
PROG: friday
LANG: C++
*/

#include <iostream>
#include <fstream>
using namespace std;

int result[8];
int MONTH[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int main(int argc, char** args) {
    //ifstream fin(stdin);
    //ofstream fout(stdout);
    ifstream fin("friday.in");    
    ofstream fout("friday.out");
    int N;
    fin >> N;
    //memset(result, 0, sizeof(result));
    int Y = 1900, M = 1, D = 1;
    int W = 1;
    while (1) {
        //fout << Y << ":" << M << ":" << D << "---" << W << endl;
        if (Y >= 1900 + N)
            break;
        bool leapY = (Y % 400 == 0) || (Y % 100 != 0 && Y % 4 == 0);
        D++;
        W = (W + 1) % 7;
        if (D > MONTH[M]) {
            if (leapY && M == 2 && D == 29)
                continue;
            else {
                M++;
                D = 1;
            }
        }
        if (M > 12) {
            Y++;
            M = 1;
        }
        if (D == 13)
            result[W]++;
    }
    fout << result[6] << " "
        <<result[7] << " "
        <<result[1] << " "
        <<result[2] << " "
        <<result[3] << " "
        <<result[4] << " "
        <<result[5] << endl;
    return 0;
}
#endif