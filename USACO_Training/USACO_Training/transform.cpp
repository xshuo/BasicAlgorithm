#ifdef __TRANSFORM__
/*
ID: shuoxie1
PROG: transform
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;


bool transform1(const string a[], const string b[], int size) 
{
    for (int i = 0; i < size; i++) {
        string line = "";
        for (int j = size - 1; j >= 0; j--) {
            line += a[j][i];
        }
        if (line != b[i])
            return false;
    }
    return true;
}

bool transform2(const string a[], const string b[], int size) 
{
    string temp[12];
    for (int i = 0; i < size; i++) {
        string line = "";
        for (int j = size - 1; j >= 0; j--) {
            line += a[j][i];
        }
        temp[i] = line;
    }
    return transform1(temp, b, size);
}

bool transform3(const string a[], const string b[], int size) 
{
    for (int i = size - 1, b_cnt = 0; i >= 0; i--, b_cnt++) {
        string line = "";
        for (int j = 0; j < size; j++) {
            line += a[j][i];
        }
        if (line != b[b_cnt])
            return false;
    }
    return true;
}

bool transform4(const string a[], const string b[], int size) 
{
    string temp[12];
    for (int i = 0; i < size; i++) {
        for (int j = size - 1; j >= 0; j--) {
            temp[i] += a[i][j];
        }
    }
    for (int i = 0; i < size; i++) {
        if (temp[i] != b[i])
            return false;
    }
    return true;
}

bool transform5(const string a[], const string b[], int size) 
{
    string temp[12];
    for (int i = 0; i < size; i++) {
        for (int j = size - 1; j >= 0; j--) {
            temp[i] += a[i][j];
        }
    }
    if (transform1(temp, b, size) ||
        transform2(temp, b, size) ||
        transform3(temp, b, size))
        return true;
    return false;
}

bool transform6(const string a[], const string b[], int size) 
{
    for (int i = 0; i < size; i++) {
        if (a[i] != b[i])
            return false;
    }
    return true;
}

int transform(const string a[], const string b[], int size) {
    if (transform1(a, b, size))
        return 1;
    else if (transform2(a, b, size))
        return 2;
    else if (transform3(a, b, size))
        return 3;
    else if (transform4(a, b, size))
        return 4;
    else if (transform5(a, b, size))
        return 5;
    else if (transform6(a, b, size))
        return 6;
    else return 7;
}

int main(int argc, char** args) {
    //ifstream fin(stdin);
    //ofstream fout(stdout);
    ifstream fin("transform.in");
    ofstream fout("transform.out");
    int N;
    int i;
    string square1[12];
    string square2[12];

    fin >> N;
    for (i = 0; i < N; i++)
        fin >> square1[i];
    for (i = 0; i < N; i++)
        fin >> square2[i];
    fout << transform(square1, square2, N) << endl;
}
#endif