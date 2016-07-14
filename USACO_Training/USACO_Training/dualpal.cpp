#ifdef __DUALPAL__
/*
ID: shuoxie1
PROG: dualpal
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
using namespace std;

void myitoa(int num, char buf[], int b) {
    int t_buf[65];
    int cnt = 0;
    int i, j;
    while (1) {
        if (num == 0)
            break;
        t_buf[cnt++] = num % b;
        num = num / b;
    }
    for (i = cnt - 1, j = 0; i >= 0; i--, j++) {
       if (t_buf[i] > 9)
           buf[j] = (t_buf[i] - 10) + 'A';
       else
           buf[j] = (t_buf[i] - 0) + '0';
    }
    buf[j] = '\0';
    //cout << num << " " << buf << endl;
}

bool isPalindromes(int num, int base) {
    char buffer[50];
    myitoa(num, buffer, base);
    int len = strlen(buffer);
    for (int i = 0, j = len - 1; i < j; i++, j--) {
        if (buffer[i] != buffer[j])
            return false;
    }
    return true;
}

int main(int argc, char** args) {
    //ifstream fin(stdin);
    //ofstream fout(stdout);
    ifstream fin("dualpal.in");
    ofstream fout("dualpal.out");
    int N, S;
    fin >> N >> S;
    while (1) {
        if (N == 0)
            break;
        S++;
        int cnt = 0;
        for (int i = 2; i <= 10; i++) {
            if (isPalindromes(S, i))
                cnt++;
            if (cnt == 2) {
                fout << S << endl;
                N--;
                break;
            }
        }
    }
    return 0;
}
#endif


