// https://www.hackerrank.com/challenges/clique

#include <iostream>
using namespace std;

int get_calc(int m, int n) {
    int g1 = n % m;
    int g2 = m - g1;
    int sz1 = n / m + 1;
    int sz2 = n / m;

    return g1 * sz1 * g2 * sz2 + g1 * (g1 - 1) * sz1 * sz1 / 2 + g2 * (g2 - 1) * sz2 * sz2 / 2;
}

int main() {
    int ts;

    cin >> ts;

    while (ts--) {
        int n, k, lo = 1, hi = n + 1, ret = -1;

        cin >> n >> k;

        while (lo + 1 < hi) {
            int mid = lo + (hi - lo) / 2;

            if (get_calc(mid, n) < k)
                lo = mid;
            else hi = mid;
        }

        cout << hi << endl;
    }

    return 0;
}
