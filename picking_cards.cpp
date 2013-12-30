// https://www.hackerrank.com/challenges/picking-cards

#include <iostream>
#include <algorithm>

#define mod 1000000007
using namespace std;

int a[50010];

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        for (int i = 0; i <n; i ++)
            cin >> a[i];

        sort(a, a + n);
        int start = 0;
        long long ans = 1LL;

        for (int i = 0; i < n; i ++) {
            while (start < n && a[start] <= i)
                start ++;

            if (start > i)
                ans = ans * (start - i) % mod;
            else {
                ans = 0;
                break;
            }
        }

        cout << ans << endl;
    }

    return 0;
}
