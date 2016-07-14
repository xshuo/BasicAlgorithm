#ifdef __PALSQUARE__
/*
ID: shuoxie1
PROG: palsquare
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <string.h>
using namespace std;

void printNumBaseB(int num, int B, ofstream& fout);
bool isPalindromes(int num, int base);

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
}

int main(int argc, char** args) {
    //ifstream fin(stdin);
    //ofstream fout(stdout);
    ifstream fin("palsquare.in");
    ofstream fout("palsquare.out");
    int B;
    fin >> B;
    for (int i = 1; i <= 300; i++) {
        //fout << "----";
        //printNumBaseB(i, B, fout);
        //fout << "----" << endl;
        if (isPalindromes(i * i, B)) {
            printNumBaseB(i, B, fout);
            fout << " ";
            printNumBaseB(i * i, B, fout);
            fout << endl;
        }
    }
    return 0;
}

void printNumBaseB(int num, int B, ofstream& fout) {
    char buffer[50];
    myitoa(num, buffer, B);
    fout << buffer;
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
#endif