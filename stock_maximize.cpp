// https://www.hackerrank.com/challenges/stockmax

#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

#define MAXN 50000

int N;
int wot[MAXN];
int l[MAXN];

long long getMaximumProfit() {
    memset(l, 0, sizeof(l));

    l[N - 1] = wot[N - 1];
    for (int i = N - 2; i >= 0; i--)
        l[i] = max(wot[i], l[i + 1]);

    long long best = 0;
    long long s = 0;

    for (int i = 0; i < N; i++) {
        if (i == N - 1 || l[i + 1] < l[i]) {
            best += s * wot[i];
            s = 0;
        } else if (l[i + 1] >= wot[i]) {
            s++;
            best -= wot[i];
        }
    }

    return best;
}

int main() {
    int T;
    cin >> T;

    for (int i = 0; i < T; i++) {
        cin >> N;

        for (int j = 0; j < N; j++)
            cin >> wot[j];

        cout << getMaximumProfit() << endl;
    }

    return 0;
}
