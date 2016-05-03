#ifdef __3087__
#include <iostream>
#include <map>
#include <string>

using std::map;
using std::string;

map<string, string> visit;
int ret;

void bfs_shuffle(string s1, string s2, string end) {
    int len = s1.size();
    while (1) {
        if (visit.find(s1) != visit.end()) {
            ret = -1;
            break;
        }
        ret++;
        string s12;
        for (int i = 0; i < len; i++) {
            s12 += s2[i];
            s12 += s1[i];
        }
        if (s12 == end) {
            break;
        }
        else {
            visit[s1] = s2;
            s1 = s12.substr(0, len);
            s2 = s12.substr(len, len);
        }
    }
}

int main(int argc, char** args) {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int len;
        string s1, s2, s12;
        scanf("%d", &len);
        std::cin >> s1 >> s2 >> s12;
        visit.clear();
        ret = 0;
        bfs_shuffle(s1, s2, s12);
        printf("%d %d\n", i, ret);
    }
    return 0;
}
#endif