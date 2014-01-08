#include<stdio.h>
#include<string.h>

typedef long long LL;
const int MODULO = 1000000007, N = 120;
int dp[N][32][2], vx[N][32], valid[32], mi[N];

int solve(int n,int k) {
    for(int i = 0;i <= 31; i++) vx[0][i] = 0;

        memset(dp,0,sizeof(dp));
        dp[0][0][0] = 1;

        for(int i = 1; i <= n; i++)
            for(int j = 0; j < 31; j++)
                vx[i][j] = (vx[i-1][j] ^ (mi[i]&(1<<j)));

        valid[31] = 1;

        for(int i = 30; i >= 0; i--)
            valid[i] = valid[i+1] && (vx[n][i] == (k & (1<<i)));

        for(int i = 1; i <= n; i++)
            for(int j = 0; j < 31; j++)
                for(int kj = 0; kj < 2; kj++) {
                    if (dp[i-1][j][kj] == 0) continue;

                    for(int k = 0; k < 31; k++)
                        if (mi[i] & (1<<(k))) {
                            int small, tmpj, tmpkj;

                            if (k > j) {
                                small = j;
                                tmpj = k;
                                tmpkj = (vx[i-1][k] ? 1 : 0);
                            } else {
                                small = k;
                                tmpj = j;

                                if (k == j)
                                    tmpkj = kj;
                                else
                                    tmpkj = kj^((mi[i] & (1<<j)) ? 1 : 0);
                            }

                            dp[i][tmpj][tmpkj] = (dp[i][tmpj][tmpkj] + ((LL) dp[i-1][j][kj]) * (1<<small)) % MODULO;
                        }
                }

        int res = 0;

        for(int i = 30; i >= 0; i--)
            if (valid[i+1])
                res = (res + dp[n][i][(k & (1<<i)) ? 1 : 0]) % MODULO;
            else break;

        return res;
}

int main() {
    int n, k = 0, res;

    scanf("%d", &n);

    for(int i = 1; i <= n; i++) {
        scanf("%d", &mi[i]);
        mi[i]++;
    }

    res = solve(n,k);

    for(int i = 1; i <= n; i++) mi[i]--;
    res = (res + MODULO - solve(n,k)) % MODULO;
    printf("%d\n", res);

    return 0;
}
