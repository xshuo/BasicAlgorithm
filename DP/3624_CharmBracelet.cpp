#ifdef __3624__
#include <iostream>

#define MAX_N 3500
#define MAX_W 13000
int weight[MAX_N];
int value[MAX_N];

//һά�����¼����״̬
int dp[MAX_W];

int knapsack(int n, int w) {
    //01 knapsack
    for (int i = w; i >= 0; i--)
        dp[i] = 0;
    //������Ų���Ĩ��ǰһ��״̬��
    for (int i = 1; i <= n; i++) {
        for (int j = w; j >= weight[i]; j--) {
            dp[j] = dp[j] > dp[j - weight[i]] + value[i] ?
                dp[j] : dp[j - weight[i]] + value[i];
        }
    }
    return dp[w];
}

int main(int argc, char** args) {
    int N, M;
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= N; i++) {
        scanf("%d%d", weight + i, value + i);
    }
    printf("%d\n", knapsack(N, M));
}
#endif