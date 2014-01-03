// https://www.hackerrank.com/challenges/points-in-a-plane

#include <iostream>
#include <cstring>

using namespace std;

typedef long long LL;
typedef unsigned long long ULL;

#define N 22
#define MOD 1000000007

int ed[66666];
int x[N], y[N], n, nn, T;
int good[66666], f[66666], fc[66666], gn = 0, g[66666];

void get_turns_needed(int T) {
       while (T--) {
            cin >> n;

            for (int i = 0; i < n; i++)
                cin >> x[i] >> y[i];

            nn = 1 << n;
            gn = 0;

            for (int i = 1; i < nn; i++) {
                int state = 0, a, b, c;
                good[i] = true;

                if (ed[i] < 3) {
                    g[gn++] = i;
                    continue;
                }

                for (int j = 0; j < n; j++) if (i & (1 << j)) {
                    if (state == 0) {
                        state = 1;
                        a = y[j];
                        b = -x[j];
                    } else
                    if (state == 1) {
                        a -= y[j];
                        b += x[j];
                        c = - a * x[j] - b * y[j];
                        state = 2;
                    } else {
                        if (a * x[j] + b * y[j] + c != 0) {
                            good[i] = false;
                            break;
                        }
                    }
                }

                if (good[i]) g[gn++] = i;
            }

            memset(f, 63, sizeof(f));

            f[0] = 0;
            fc[0] = 1;

            for (int i = 1; i < nn; ++i) {
                if (good[i]) {
                    f[i] = 1;
                    fc[i] = 1;
                    continue;
                }

                if ((1 << ed[i]) > gn) {
                    for (int j = 0; j < gn; ++j) {
                        if ( (g[j] | i) != i) continue;

                        if (f[i ^ g[j]] + 1 < f[i]) {
                            f[i] = f[i ^ g[j]] + 1;
                            fc[i] = fc[i ^ g[j]];
                        } else if (f[i ^ g[j]] + 1 == f[i])
                            fc[i] = (fc[i] + fc[i ^ g[j]]) % MOD;
                    }
                } else {
                    for (int j = (i - 1) & i; j; j = (j - 1) & i) {
                        if (!good[j]) continue;

                        if (f[i ^ j] + 1 < f[i]) {
                            f[i] = f[i ^ j] + 1;
                            fc[i] = fc[i ^ j];
                        } else if (f[i ^ j] + 1 == f[i])
                            fc[i] = (fc[i] + fc[i ^ j]) % MOD;
                    }
                }
            }

            cout << f[nn - 1] << " " << fc[nn - 1] << endl;
    }
}

int main() {
    ed[0] = 0;

    for (int i = 1; i < 65536; ++i)
        ed[i] = ed[i & (i - 1)] + 1;

    cin >> T;

    get_turns_needed(T);
    return 0;
}
