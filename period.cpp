// https://www.hackerrank.com/challenges/period

#include <stdio.h>
#include <iostream>

using namespace std;

typedef long long LL;

void solve() {
    int m, a, b;

    scanf("%d%d%d", &a, &b, &m);

    if (a == 0 && b == 0) {
        printf("-1\n");
        return;
    }

    LL i, ta = a, tb = b, pa = a, pb = b;
    int max_iter = 1000000;

    for (i = 1; i < max_iter; i++) {
        if (tb == 0) break;

        ta = pa * a + 5 * pb * b;
        ta %= m;
        tb = pa * b + a * pb;
        tb %= m;
        pa = ta;
        pb = tb;
    }

    if (tb == 0 and ta == 1) {
        cout << i << endl;
        return;
    }

    if (i == max_iter) {
        printf("-1\n");
        return;
    }

    long long iter_cnt = i;
    pa = ta;

    for (i = 1; i < max_iter; i++) {
        if (ta == 1) break;
        ta = ta * pa % m;
    }

    if (ta == 1) {
        cout << i * iter_cnt << endl;
        return;
    }

    if (i == max_iter) {
        printf("-1\n");
        return;
    }
}

int main() {
    int t;
    scanf("%d", &t);

    for (int i = 0; i < t; i++) solve();
    return 0;
}
