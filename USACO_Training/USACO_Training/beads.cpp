#ifdef __BEADS__
/*
ID: shuoxie1
PROG: beads
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;


int main(int argc, char** args) {
    //ifstream fin(stdin);
    //ofstream fout(stdout);
    ifstream fin("beads.in");
    ofstream fout("beads.out");
    int size;
    string necklace;
    fin >> size;
    fin >> necklace;
    int ret = 0;
    int i;
    for (i = 0; i < size; i++) {
        string temp = necklace.substr(i, size - i) + necklace.substr(0, i);
        int cnt1 = 0, cnt2 = size - 1;
        char flag = ' ';
        while (1) {
            if (cnt1 >= size)
                break;
            if (temp[cnt1] == 'w') {
                cnt1++;
                continue;
            }
            if (flag == ' ')
                flag = temp[cnt1];
            if (temp[cnt1] == flag)
                cnt1++;
            else break;            
        }
        flag = ' ';
        while (1) {
            if (cnt2 < cnt1)
                break;
            if (temp[cnt2] == 'w') {
                cnt2--;
                continue;
            }
            if (flag == ' ')
                flag = temp[cnt2];
            if (temp[cnt2] == flag)
                cnt2--;
            else break; 
        }
        if (ret < cnt1 + (size - cnt2 - 1))
            ret = cnt1 + (size - cnt2 - 1);
    }
    fout << ret << endl;
    return 0;
}
#endif