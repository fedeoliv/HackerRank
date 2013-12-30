// https://www.hackerrank.com/challenges/permutation-game

#include <iostream>
using namespace std;

int dp[1 << 15], last[1 << 15], a[15], n;

int solve(int bits) {
    if (dp[bits] != -1) return dp[bits];

    dp[bits] = 0;

    for (int i = 0; i < n; i ++) {
        if (bits & (1 << i)) {
            if (solve(bits - (1 << i)) == 0) {
                dp[bits] = 1;
                break;
            }
        }
    }

    return dp[bits];
}

int main() {
    int t;

    cin >> t;

    while (t--) {
        cin >> n;

        for (int i = 0; i < n; i ++)
          cin >> a[i];

        dp[0] = 0;
        last[0] = 0;

        for (int i = 0; i < n; i ++) {
            for (int j = 0; j < (1 << i); j ++) {
                if (dp[j] == 0 && a[i] > last[j])
                    dp[j + (1 << i)] = 0;
                else
                    dp[j + (1 << i)] = -1;

                last[j + (1 << i)] = a[i];
            }
        }

        cout << (solve((1<<n) - 1)? "Alice" : "Bob") << endl;
    }

    return 0;
}
