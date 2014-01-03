// https://www.hackerrank.com/challenges/manipulative-numbers

#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;
typedef unsigned long long ULL;

unsigned a[111111], b[111111];
int n;

int main() {
    cin >> n;

    for (int i = 0; i < n; i++) cin >> a[i];

    for (int i = 31; i >= 0; i--) {
        for (int j = 0; j < n; j++)
            b[j] = a[j] >> i;

        sort(b, b + n);
        unsigned x = b[0];
        int cnt = 1, maxcnt = 1;

        for (int j = 1; j < n; j++) {
            if (b[j] == x) {
                ++cnt;
                if (cnt > maxcnt) maxcnt = cnt;
            } else {
                cnt = 1;
                x = b[j];
            }
        }

        if (maxcnt <= n - maxcnt) {
            cout << i << endl;
            return 0;
        }
    }

    cout << -1 << endl;

    return 0;
}
