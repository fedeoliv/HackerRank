// https://www.hackerrank.com/challenges/niceClique

#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>

using namespace std;

#define MAXP 40000000
#define MAXD 1000000000000000l
#define MAXN 200

bool isPrime[MAXP], ppd[MAXN], psd[MAXN];
int primes[MAXP], nPrimes;

long long modMult(long long a, long long b, long long c) {
    long long x = 0, y = a % c;

    for ( ; b > 0; y = (y * 2) % c, b >>= 1)
        if (b & 1)
            x = (x + y) % c;

    return x % c;
}

long long modPow(long long a, long long b, long long c) {
    long long x = 1, y = a;

    for ( ; b > 0; y = modMult(y, y, c), b >>= 1)
        if (b & 1)
            x = modMult(x, y, c);

    return x % c;
}

bool isProbablePrime(long long p, int iteration = 20) {
    if (p < 2) return false;
    if (p != 2 && p % 2 == 0) return false;

    long long a, temp, mod, s = p - 1;

    while ((s & 1) == 0)
        s >>= 1;

    while (iteration--) {
        a = rand() % (p - 1) + 1, temp = s;

        for (mod = modPow(a, temp, p); temp != p - 1 && mod != 1 && mod != p - 1; temp <<= 1)
            mod = modMult(mod, mod, p);

        if (mod != p - 1 && temp % 2 == 0) return false;
    }

    return true;
}

void calcPrimes() {
    memset(isPrime, true, sizeof(isPrime));

    isPrime[1] = false;
    int l = (int) sqrt(MAXD);

    for (int i = 2; i <= (int) sqrt(l); i++) {
        if (isPrime[i]) {
            for (int j = i + i; j <= l; j += i)
                isPrime[j] = false;
        }
    }

    nPrimes = 0;
    for (int i = 1; i <= l; i++) {
        if (isPrime[i])
            primes[nPrimes++] = i;
    }
}

void calcParities(int i, long long n) {
    while (n > 1) {
        if ((n > primes[nPrimes - 1] && isProbablePrime(n)) ||
            (n <= primes[nPrimes - 1] && isPrime[n])) {
            ppd[i] ^= 1;
            if (n > 2)
                psd[i] = 0;
            n /= n;
        }

        int l = (int) sqrt(n);

        for (int j = 0; j < nPrimes && primes[j] <= l; j++) {
            if (n % primes[j] == 0) {
                int pp = psd[i];

                while (n % primes[j] == 0) {
                    if (primes[j] > 2 && (pp % 2))
                        psd[i] ^= 1;

                    n /= primes[j];
                }

                ppd[i] ^= 1;
                break;
            }
        }
    }
}

int getMaximumSubsetSize(vector<long long> ds) {
    calcPrimes();

    memset(ppd, 0, sizeof(ppd));
    memset(psd, 1, sizeof(psd));

    int N = ds.size();

    for (int i = 0; i < N; i++)
        calcParities(i, ds[i]);

    int ppd0 = 0;
    int ppd1 = 0;
    int psd0 = 0;
    int psd1 = 0;

    for (int i = 0; i < N; i++) {
        if (ppd[i]) ppd1++;
        else ppd0++;

        if (psd[i]) psd1++;
        else psd0++;
    }

    return max(ppd0, max(ppd1, max(psd0, psd1)));
}

int main() {
    int n;
    long long d;
    vector<long long> ds;

    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> d;
        ds.push_back(d);
    }

    cout << getMaximumSubsetSize(ds) << endl;

    return 0;
}
