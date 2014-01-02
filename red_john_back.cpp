// https://www.hackerrank.com/challenges/red-john-is-back

#include <iostream>
#include <vector>

using namespace std;

#define PB push_back

const int MAX = 41;
int f[MAX], cnt[MAX];
vector<int> prime;

void getPrime(int n) {
    vector<bool> mk(n + 1);
    for (int i = 2; i <= n; i++) {
        if (!mk[i]) {
            prime.PB(i);

            for (int j = 2; i * j <= n; j++)
                mk[i * j] = true;
        }
    }
}

int main() {
    int test;

    for (int i = 0; i < 4; i++)
        f[i] = 1;

    for (int i = 4; i < 41; i++)
        f[i] = f[i - 1] + f[i - 4];

    getPrime(f[40]);

    for (int i = 1; i <= 40; i++) {
        for (int j = 0; j < prime.size(); j++) {
            if (prime[j] > f[i]) break;
            cnt[i]++;
        }
    }

    cin >> test;

    while (test--) {
        int n;

        cin >> n;
        cout << cnt[n] << endl;
    }

    return 0;
}
