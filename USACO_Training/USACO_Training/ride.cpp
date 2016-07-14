#ifdef __RIDE__
/*
ID: shuoxie1
PROG: ride
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char** args) {
    ifstream fin("ride.in");
    ofstream fout("ride.out");
    string comet, group;
    fin >> comet >> group;
    int i;
    int c_num = 1, g_num = 1;
    for (i = 0; i < comet.size(); i++) {
        c_num *= comet[i] - 'A' + 1;
    }
    for (i = 0; i < group.size(); i++) {
        g_num *= group[i] - 'A' + 1;
    }

    if (c_num % 47 == g_num % 47)
        fout << "GO" <<endl;
    else
        fout << "STAY" << endl;
    return 0;
}
#endif