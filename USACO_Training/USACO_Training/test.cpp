#ifdef __TEST__
/*
ID: shuoxie1
PROG: test
LANG: C++
*/
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char** args) {
    ifstream fin("test.in");
    ofstream fout("test.out");
    int a, b;
    fin >> a >> b;
    fout << a + b << endl;
    return 0;
}
#endif