// https://www.hackerrank.com/challenges/repeat-k-sums

#include <cstdio>
#include <map>
using namespace std;

int Tot;
long long a[100010];
map <long long,int> mp;

void dfs(int now, int ee, int les) {
    if (les == 0 || now+1 == ee) {
        Tot++;
        return;
    }

    for (int i = 0; i <= les; i++)
        dfs(now+1, ee, les-i);
}

void dfs2(int now, long long num, int les) {
    if (now == 0) num += les*a[0];

    if (les == 0 || now == 0) {
        mp[num]--;
        if (mp[num] == 0) mp.erase(num);
        return;
    }

    for (int i = 0; i <= les;i++)
        dfs2(now-1, num + i*a[now], les-i);
}

int main() {
    int T;
    scanf("%d",&T);

    while (T--) {
        int n,m;
        scanf("%d%d", &n, &m);
        Tot = 0;
        dfs(0, n, m);

        for (int i = 0; i < Tot; i++) {
            long long x;
            scanf("%lld", &x);
            mp[x]++;
        }

        for (int i = 0; i < n; i++) {
            long long now = mp.begin()->first;
            if (i == 0) {
                a[i] = now / m;
                mp[now]--;
                if (mp[now] == 0) mp.erase(now);
            } else {
                a[i] = now - a[0]*(m-1);

                for (int j = 1; j <= m; j++)
                    dfs2(i-1, a[i]*j, m-j);
            }
        }

        for (int i = 0; i < n; i++) {
            if (i) printf(" ");
            printf("%lld", a[i]);
        }

        puts("");
    }

    return 0;
}
