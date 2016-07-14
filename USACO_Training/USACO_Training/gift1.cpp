#ifdef __GIFT1__
/*
ID: shuoxie1
PROG: gift1
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;

typedef struct Money_Node {
    int start, end;
    Money_Node(int s, int e): start(s), end(e){}
} Node;

int main(int argc, char** args) {
    ifstream fin("gift1.in");
    //ofstream fout(stdout);
    ofstream fout("gift1.out");
    map<string, Node> m;
    string names[15];
    int i, num;
    string name;
    fin >> num;
    for (i = 0; i < num; i++) {
        fin >> name;
        names[i] = name;
        Node temp(0, 0);
        m.insert(pair<string, Node>(name, temp));
    }
    while (fin >> name) {
        int money, d_num;
        fin >> money >> d_num;
        map<string, Node>::iterator it = m.find(name);
        if (it != m.end()) {
            it->second.start = money;
            if (d_num != 0)
                it->second.end += money % d_num;
        }
        for (i = 0; i < d_num; i++) {
            fin >> name;
            map<string, Node>::iterator it = m.find(name);
            if (it != m.end()) {
                it->second.end += money / d_num;
            }
        }
    }
    for (i = 0; i < num; i++) {
        map<string, Node>::iterator it = m.find(names[i]);
        fout << names[i] << " " << it->second.end - it->second.start << endl;
    }
    return 0;
}
#endif