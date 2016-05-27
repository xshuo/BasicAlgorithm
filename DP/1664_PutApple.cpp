#ifdef __1664__
#include <iostream>

#define MAX_MN 11
int dp[MAX_MN][MAX_MN];

int put_apple(int m, int n) {
    if (m < 0)
        return 0;
    if (m == 0 || n == 1) {
        return 1;
    }

    if (dp[m][n])
        return dp[m][n];

    dp[m][n] = put_apple(m - n, n) + put_apple(m, n - 1);
    return dp[m][n];
}

int main(int argc, char** args) {
    int cas;
    int m, n;
    scanf("%d", &cas);
    while (cas--) {
        scanf("%d%d", &m, &n);
        memset(dp, 0, sizeof(dp));
        printf("%d\n", put_apple(m, n));
    }
    return 0;
}
#endif