#ifdef __NAMENUM__
/*
ID: shuoxie1
PROG: namenum
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define N 5000
string dict[5000];
int CNT = 0;

#define LEN 15
string name;
char numtol[10][3] = {
    {'0', '0', '0'},
    {'0', '0', '0'},
    {'A', 'B', 'C'},
    {'D', 'E', 'F'},
    {'G', 'H', 'I'},
    {'J', 'K', 'L'},
    {'M', 'N', 'O'},
    {'P', 'R', 'S'},
    {'T', 'U', 'V'},
    {'W', 'X', 'Y'},
};
bool find_flag = false;

bool dict_find(string name);
int binary_search(string name, int start, int end);

void dfs_name(const string num, int idx, ofstream& fout) {
    if (idx == num.size()) {
        if (dict_find(name)) {
            find_flag = true;
            fout << name << endl;
        }
        return;
    }
    for (int i = 0; i < 3; i++) {
        name[idx] = numtol[num[idx] - '0'][i];
        dfs_name(num, idx + 1, fout);
    }
}

bool dict_find(string name) {
    //cout << name << endl;
    if (binary_search(name, 0, CNT - 1) > 0)
        return true;
    else 
        return false;
}

int binary_search(string name, int start, int end) {
    if (start > end) {
        return -1;
    }
    int mid = (start + end) >> 1;
    int comp = name.compare(dict[mid]);
    if (comp == 0)
        return mid;
    else if (comp > 0)
        return binary_search(name, mid + 1, end);
    else
        return binary_search(name, start, mid - 1);
}

int main(int argc, char** args) {
    //ifstream fin(stdin);
    //ofstream fout(stdout);
    ifstream fin("namenum.in");
    ofstream fout("namenum.out");
    ifstream fdict("dict.txt");
    while (fdict >> dict[CNT++]);
    string num;
    fin >> num;
    name.assign(num.size(), 0);
    dfs_name(num, 0, fout);
    if (!find_flag)
        fout << "NONE" << endl;
    return 0;
}
#endif