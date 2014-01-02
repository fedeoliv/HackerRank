// https://www.hackerrank.com/challenges/brick-tiling

#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

typedef long long LL;
const int MOD = 1000000007, inf = 0x3f3f3f3f, maxn = 25, maxs = 1 << 8;
LL dp[maxn][maxs][maxs];
int state[maxn], cur, nxt, n, m, initJ, initK;

bool is_valid(int mask, int pos) {
    return (mask & (1 << pos)) == 0;
}

void dfs(int dep, int s1, int s2, int s3, int current) {
    if (current >= (1 << m)) return;

    if (current == (1 << m) - 1) {
        dp[nxt][s2][s3] = (dp[nxt][s2][s3] + dp[cur][initJ][initK]) % MOD;
        return;
    }

    if (s1 & (1 << dep))
        dfs(dep + 1, s1, s2, s3, current);
    else {
        if (dep + 1 < m && is_valid(s2, dep) && is_valid(s3, dep) && is_valid(s3, dep + 1))
            dfs(dep + 1, s1, s2 | (1 << dep), s3 | (1 << dep) | (1 << (dep + 1)), current | (1 << dep));

        if (dep >= 1 && is_valid(s2, dep) && is_valid(s3, dep) && is_valid(s3, dep - 1))
            dfs(dep + 1, s1, s2 | (1 << dep), s3 | (1 << dep) | (1 << (dep - 1)), current | (1 << dep));

        if (dep + 1 < m && is_valid(s1, dep + 1) && is_valid(s2, dep + 1) && is_valid(s3, dep + 1))
            dfs(dep + 2, s1, s2 | (1 << (dep + 1)), s3 | (1 << (dep + 1)), current | (1 << dep) | (1 << (dep + 1)));

        if (dep + 1 < m && is_valid(s1, dep + 1) && is_valid(s2, dep) && is_valid(s3, dep))
            dfs(dep + 2, s1, s2 | (1 << dep), s3 | (1 << dep), current | (1 << dep) | (1 << (dep + 1)));

        if (dep + 2 < m && is_valid(s2, dep) && is_valid(s2, dep + 1) && is_valid(s2, dep + 2))
            dfs(dep + 1, s1, s2 | (1 << dep) | (1 << (dep + 1)) | (1 << (dep + 2)), s3, current | (1 << dep));

        if (dep >= 2 && is_valid(s2, dep) && is_valid(s2, dep - 1) && is_valid(s2, dep - 2))
            dfs(dep + 1, s1, s2 | (1 << (dep - 2)) | (1 << (dep - 1)) | (1 << dep), s3, current | (1 << dep));

        if (dep + 2 < m && is_valid(s2, dep) && is_valid(s1, dep + 1) && is_valid(s1, dep + 2))
            dfs(dep + 3, s1, s2 | (1 << dep), s3, current | (1 << dep) | (1 << (dep + 1)) | (1 << (dep + 2)));

        if (dep + 2 < m && is_valid(s1, dep + 1) && is_valid(s1, dep + 2) && is_valid(s2, dep + 2))
            dfs(dep + 3, s1, s2 | (1 << (dep + 2)), s3, current | (1 << dep) | (1 << (dep + 1)) | (1 << (dep + 2)));
    }
}

char str[10];

int main() {
    int ts;

    cin >> ts;

    while (ts--) {
        memset(state, 0, sizeof(state));
        cin >> n >> m;

        for (int i = 1; i <= n; i++) {
            cin >> str;

            for (int j = 0; j < m; j++)
                if (str[j] == '#')
                    state[i] |= (1 << j);
        }

        if (n == 1) {
            if (state[1] == (1 << m) - 1) puts("1");
            else puts("0");
            continue;
        }

        memset(dp, 0, sizeof(dp));
        dp[2][state[1]][state[2]] = 1;

        for (int i = 2; i <= n; i++) {
            cur = i, nxt = i + 1;

            for (int j = 0; j < (1 << m); j++) {
                for (int k = 0; k < (1 << m); k++) {
                    if (dp[cur][j][k] == 0) continue;
                    initJ = j; initK = k;
                    dfs(0, j, k, state[i + 1], j);
                }
            }
        }

        cout << dp[n + 1][(1 << m) - 1][0] << endl;
    }

    return 0;
}
