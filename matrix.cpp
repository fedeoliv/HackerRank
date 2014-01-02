//

#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

#define PB push_back
#define MP make_pair

typedef long long LL;
const int MAXN = 100005;
const LL inf = 1LL << 55;
int N, K;
bool bad[MAXN];
LL dp[MAXN][2];
vector<pair<int, int> > adj[MAXN];

void dfs(int u, int fa) {
    dp[u][1] = 0;
    dp[u][0] = bad[u] ? inf : 0;

    for (int i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i].first, w = adj[u][i].second;

        if (v != fa) {
            dfs(v, u);
            dp[u][1] += min(dp[v][0], dp[v][1] + w);
            dp[u][1] = min(dp[u][1], dp[u][0] + dp[v][1]);

            if (!bad[u])
                dp[u][0] += min(dp[v][0], dp[v][1] + w);
        }
    }
}

int main() {
    cin >> N >> K;

    for (int i = 1; i < N; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a].PB(MP(b, c)); adj[b].PB(MP(a, c));
    }

    memset(bad, false, sizeof(bad));

    for (int i = 0; i < K; i++) {
        int x;
        cin >> x;
        bad[x] = true;
    }

    dfs(0, -1);
    LL ret = min(dp[0][0], dp[0][1]);

    cout << ret << endl;

    return 0;
}
