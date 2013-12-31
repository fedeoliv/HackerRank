// https://www.hackerrank.com/challenges/game-of-throne-ii

#include <iostream>
#include <string>
#include <map>

using namespace std;

bool hasAnagramPalindrome(string s) {
    map<char, int> charCount;
    for (unsigned int i = 0; i < s.size(); i++)
        charCount[s[i]]++;

    int oddCount = 0;
    for (map<char, int>::iterator itr = charCount.begin();
         itr != charCount.end();
         itr++) {
        if (itr->second % 2)
            oddCount++;
    }

    return oddCount <= 1;
}

long long modFactorial(long long n, long long mod) {
    long long t = 1;
    for (int i = 1; i <= n; i++)
        t = (t * i) % mod;

    return t;
}

long long modMult(long long n1, long long n2, long long mod) {
    return (n1 * n2) % mod;
}

long long modInv(long long n, long long mod) {
    long long b0 = mod, t, q;
    long long x0 = 0, x1 = 1;
    if (mod == 1)
        return 1;
    while (n > 1) {
        q = n / mod;
        t = mod, mod = n % mod, n = t;
        t = x0, x0 = x1 - q * x0, x1 = t;
    }
    if (x1 < 0)
        x1 += b0;
    return x1;
}

long long modDiv(long long n1, long long n2, long long mod) {
    return modMult(n1, modInv(n2, mod), mod);
}

long long getAnagramStrings(string s) {
    static int MOD = 1000000007;

    if (!hasAnagramPalindrome(s))
        return 0;

    map<char, int> charCount;
    for (unsigned int i = 0; i < s.size(); i++)
        charCount[s[i]]++;

    long long numerator = modFactorial(s.size() / 2, MOD);
    long long denominator = 1;
    for (map<char, int>::iterator itr = charCount.begin();
         itr != charCount.end();
         itr++) {
        if (itr->second % 2 == 0) {
            denominator = modMult(denominator,
                                  modFactorial(itr->second / 2, MOD),
                                  MOD);
        }
    }

    return modDiv(numerator, denominator, MOD);
}

int main() {
    string s;
    cin >> s;
    cout << getAnagramStrings(s) << endl;
    return 0;
}
