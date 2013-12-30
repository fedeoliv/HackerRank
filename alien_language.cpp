// https://www.hackerrank.com/challenges/alien-languages

#include <iostream>
#include <cstring>

using namespace std;

#define MODULO 100000007
#define MAX_M 500000
#define MAX_N 100000
#define MAX_L 20

int getPossibleWords(int n, int m) {
    static int words[MAX_M + 1];
    static int mult[MAX_L];
    static int t[MAX_N + 1][MAX_L];

    int i, j, k, nb = n / 2;
    long long d;

    memset(words, 0, sizeof(words));
    memset(mult, 0, sizeof(mult));
    memset(t, 0, sizeof(t));

    for (i = n; i > nb; i--)
        t[i][0] = 1;

    for (j = n, k = 0; j > 0; j /= 2, k++) {
        d = 0;

        for (i = n; i > 0; i--) {
            d = (d + t[i][k]) % MODULO;
            t[i / 2][k + 1] = d;
        }

        for (i = n; i > 0; i--)
            mult[k] = (mult[k] + t[i][k]) % MODULO;
    }

    words[0] = 1;

    for (i = 1; i <= m; i++) {
        d = words[i - 1];
        for (j = 0; mult[j] && i + j <= m; j++)
            words[i + j] = (words[i + j] + (d * mult[j]) % MODULO) % MODULO;
    }

    return words[m];
}

int main() {
    int t, n, m;

    cin >> t;

    for (int i = 0; i < t; i++) {
        cin >> n >> m;
        cout << getPossibleWords(n, m) << endl;
    }

    return 0;
}
