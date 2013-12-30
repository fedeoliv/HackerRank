// https://www.hackerrank.com/challenges/equations

#include <iostream>

using namespace std;

#define MAX 1000010
#define MODULO 1000007

int prime[MAX] = {0}, cnt[MAX] = {0};

int main() {
    long long ans = 1LL;
    int n;

    cin >> n;

    for (int i = 2; i <= MAX /i; i ++) {
        if (!prime[i]) {
          prime[i] = i;

          for (int j = i * i ; j < MAX; j += i)
            prime[j] = i;
        }
    }

    for (int i = 2; i <= n; i ++) {
        int m = i;

        while (m > 1) {
            if (prime[m] == 0)
                prime[m] = m;

            cnt[prime[m]] += 2;
            m /= prime[m];
        }
    }

    for (int i = 0; i <= n; i ++)
        ans = ans * (1 + cnt[i]) % MODULO;

    cout << ans << endl;
    return 0;
}
