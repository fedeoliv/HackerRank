// https://www.hackerrank.com/challenges/stitch-the-torn-wiki

#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

int ans[200000], a[100001][26], lst, n;
char s[200000];
vector<int> q[100001];
double v[1000], e[300][300];

void add(int k, char *s, int i) {
    int ch = *s;

    if (ch >= 'A' && ch <= 'Z') ch -='A'-'a';

    if (ch >= 'a' && ch <= 'z') {
        if (!a[k][ch-'a'])
            a[k][ch-'a'] = ++lst;

        add(a[k][ch-'a'], s+1, i);
    } else {
        if (k) q[k].push_back(i);
        if (*s) add(0, s + 1, i);

        return;
    }
}

void eval(int k, char *s, int r) {
    int ch = *s;

    if (ch >= 'A' && ch <= 'Z') ch -='A'-'a';
    if (ch >= 'a' && ch <= 'z') {
        if (!a[k][ch-'a'])
            a[k][ch-'a'] = ++lst;

        eval(a[k][ch-'a'], s+1, r);
    } else {
        if (k) {
            double tot = 0;

            for (int i = 0; i < n; i++) v[i] = 0;
            for (int i = 0; i < q[k].size(); i++) {
                v[q[k][i]]++;
                tot += 1.0;
            }

            if (q[k].size())
                for (int i = 0; i < n; i++)
                    e[i+1][r+1] += v[i]/tot;
        }

        if (*s) eval(0, s+1, r);
    }
}

void hungarian() {
    vector<int> u (n+1), v (n+1), p (n+1), way (n+1);

    for (int i = 1; i <= n; ++i) {
        p[0] = i;
        int j0 = 0;

        vector<double> minv (n+1, 1e18);
        vector<char> used (n+1, false);

        do {
            used[j0] = true;
            int i0 = p[j0],  j1;
            double delta = 1e18;

            for (int j = 1; j <= n; ++j)
                if (!used[j]) {
                    double cur = e[i0][j]-u[i0]-v[j];

                    if (cur < minv[j])
                        minv[j] = cur,  way[j] = j0;

                    if (minv[j] < delta)
                        delta = minv[j],  j1 = j;
                }

            for (int j = 0; j <= n; ++j)
                    if (used[j])
                    u[p[j]] += delta,  v[j] -= delta;
                else
                    minv[j] -= delta;
            j0 = j1;
        } while (p[j0] != 0);

        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }

    for (int j = 1; j <= n; ++j)
        ans[p[j]] = j;
}

int main() {
    scanf("%d", &n);
    while(getchar()!='\n');

    for (int i = 0; i < n; i++) {
        int t = 0;

        for (int ch = getchar(); ch != '\n'; ch = getchar())
            s[t++] = ch;

        s[t++] = '.';
        s[t++] = 0;

        add(0, s, i);
    }

    while (getchar()!='\n');

    for (int i = 0; i < n; i++) {
        int t = 0;

        for (int ch = getchar(); ch != '\n'; ch = getchar()) {
            if (ch == EOF) break;

            s[t++] = ch;
        }

        s[t++] = '.';
        s[t++] = 0;

        eval(0, s, i);
    }

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            e[i][j] = 1e5 - e[i][j];

    hungarian();

    for (int i = 1; i <= n; i++)
        printf("%d\n", ans[i]);

    return 0;
}
