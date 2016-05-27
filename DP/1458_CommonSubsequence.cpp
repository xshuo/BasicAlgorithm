#ifdef __1458__
#include <iostream>

#define MAX_N 1000
char str1[MAX_N];
char str2[MAX_N];
int len[MAX_N][MAX_N];

int LCS(char* str1, char* str2, int s1, int s2) {
    if (s1 == 0 || s2 == 0)
        return 0;
    if (str1[s1 - 1] == str2[s2 - 1]) {
        if (len[s1 - 1][s2 - 1] == -1)
            len[s1 - 1][s2 - 1] = LCS(str1, str2, s1 - 1, s2 - 1);
        return len[s1 - 1][s2 - 1] + 1;
    } else {
        if (len[s1 - 1][s2] == -1)
            len[s1 - 1][s2] = LCS(str1, str2, s1 - 1, s2);
        if (len[s1][s2 - 1] == -1)
            len[s1][s2 - 1] = LCS(str1, str2, s1, s2 - 1);
        return len[s1 - 1][s2] > len[s1][s2 - 1] ? len[s1 - 1][s2] : len[s1][s2 - 1];
    }
}

int main(int argc, char** args) {
    while (scanf("%s%s", str1, str2) != EOF) {
        memset(len, 0xff, sizeof(len));
        printf("%d\n", LCS(str1, str2, strlen(str1), strlen(str2)));
    }
    return 0;
}
#endif