#ifdef __3356__
#include <iostream>

#define MAX_N 1100
char str1[MAX_N];
char str2[MAX_N];
int dp_tbl[MAX_N][MAX_N];

inline int min(int a, int b, int c) {
    return (a < b ? a : b) < c ? (a < b ? a : b) : c;
}

int edit_dist(char* str1, char* str2, int m, int n) {
    if (m == 0)
        return n;
    if (n == 0)
        return m;
    if (str1[m - 1] == str2[n - 1]) {
        if (dp_tbl[m - 1][n - 1] == -1)
            dp_tbl[m - 1][n - 1] = edit_dist(str1, str2, m - 1, n - 1);
        return dp_tbl[m - 1][n - 1];
    } else {
        //replace
        if (dp_tbl[m - 1][n - 1] == -1)
            dp_tbl[m - 1][n - 1] = edit_dist(str1, str2, m - 1, n - 1);
        //delete
        if (dp_tbl[m - 1][n] == -1)
            dp_tbl[m - 1][n] = edit_dist(str1, str2, m - 1, n);
        //insert
        if (dp_tbl[m][n - 1] == -1)
            dp_tbl[m][n - 1] = edit_dist(str1, str2, m, n - 1);
        return 1 + min(dp_tbl[m - 1][n - 1], dp_tbl[m - 1][n], dp_tbl[m][n - 1]);
    }
}

int main(int argc, char** args) {
    int s1, s2;
    while (scanf("%d%s%d%s", &s1, str1, &s2, str2) != EOF) {
        memset(dp_tbl, 0xff, sizeof(dp_tbl));
        printf("%d\n", edit_dist(str1, str2, s1, s2));
    }
    return 0;
}
#endif