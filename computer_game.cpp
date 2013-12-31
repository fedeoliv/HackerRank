#include <iostream>
#include <cstring>
#include <cmath>
#include <map>
#include <set>
#include <vector>

using namespace std;

vector<bool> calcSieve(int maxValue) {
    vector<bool> isPrime = vector<bool>(maxValue, true);
    isPrime[0] = isPrime[1] = false;
    int L = sqrt(maxValue);

    for (int i = 2; i <= L; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j < maxValue; j += i) {
                isPrime[j] = false;
            }
        }
    }

    return isPrime;
}

vector<int> compressSieve(vector<bool> isPrime) {
    vector<int> primes;
    int maxValue = isPrime.size();

    for (int i = 2; i < maxValue; i++) {
        if (isPrime[i])
            primes.push_back(i);
    }

    return primes;
}

bool match(int u,
           int ** primeIdsA,
           int * primeIdsLength,
           int ** bMatchArr,
           int * bMatchLength,
           int * visitedL,
           int * visitedR,
           int * matchL,
           int * matchR,
           int visitedI) {
    if (visitedL[u] == visitedI)
        return false;
    visitedL[u] = visitedI;
    int * factors = primeIdsA[u];

    for (int i = 0; i < primeIdsLength[u]; i++) {
        if (visitedR[factors[i]] == visitedI)
            continue;
        for (int j = 0; j < bMatchLength[factors[i]]; j++) {
            int v = bMatchArr[factors[i]][j];
            if (matchR[v] < 0) {
                matchL[u] = v;
                matchR[v] = u;
                return true;
            }
        }
    }

    for (int i = 0; i < primeIdsLength[u]; i++) {
        if (visitedR[factors[i]] == visitedI)
            continue;
        visitedR[factors[i]] = visitedI;
        for (int j = 0; j < bMatchLength[factors[i]]; j++) {
            int v = bMatchArr[factors[i]][j];
            if (matchL[u] != v &&
                match(matchR[v],
                      primeIdsA,
                      primeIdsLength,
                      bMatchArr,
                      bMatchLength,
                      visitedL,
                      visitedR,
                      matchL,
                      matchR,
                      visitedI)) {
                matchL[u] = v;
                matchR[v] = u;
                return true;
            }
        }
    }

    return false;
}

int getPrimeId(int prime, map<int, int> & primeIds) {
    if (primeIds.find(prime) == primeIds.end())
        primeIds[prime] = primeIds.size();
    return primeIds[prime];
}

int getMaximumRemovals(vector<int> a, vector<int> b) {
    static int MAX = 1000000000;
    vector<bool> isPrime = calcSieve(sqrt(MAX));
    vector<int> primes = compressSieve(isPrime);

    map<int, int> primeIds;
    int * primeFactors = new int[primes.size()];
    int ** primeIdsA = new int*[a.size()];
    int * primeIdsALength = new int[a.size()];

    for (unsigned int i = 0; i < a.size(); i++) {
        int x = a[i];
        int p = 0;
        for (unsigned int j = 0; j < primes.size() && primes[j] * primes[j] <= x; j++) {
            if (x % primes[j] == 0)
                primeFactors[p++] = primes[j];
            while (x % primes[j] == 0)
                x /= primes[j];
        }
        if (x > 1)
            primeFactors[p++] = x;

        primeIdsA[i] = new int[p];
        primeIdsALength[i] = p;
        for (int j = 0; j < p; j++) {
            primeIdsA[i][p - j - 1] =
                getPrimeId(primeFactors[j], primeIds);
        }
    }

    vector<vector<int> > bMatchList = vector<vector<int> >(primeIds.size() + 1, vector<int>());
    for (unsigned int i = 0; i < b.size(); i++) {
        int x = b[i];
        for (unsigned int j = 0; j < primes.size() && primes[j] * primes[j] <= x; j++) {
            if (x % primes[j] == 0 && primeIds.find(primes[j]) != primeIds.end())
                bMatchList[primeIds[primes[j]]].push_back(i);
            while (x % primes[j] == 0)
                x /= primes[j];
        }
        if (x > 1 && primeIds.find(x) != primeIds.end())
            bMatchList[primeIds[x]].push_back(i);
    }

    int * matchL = new int[a.size()];
    int * matchR = new int[b.size()];
    int * visitedL = new int[a.size()];
    int * visitedR = new int[primeIds.size()];

    memset(matchL, -1, a.size() * sizeof(int));
    memset(matchR, -1, b.size() * sizeof(int));
    memset(visitedL, -1, a.size() * sizeof(int));
    memset(visitedR, -1, primeIds.size() * sizeof(int));

    int ** bMatchArr = new int*[bMatchList.size()];
    int * bMatchLength = new int[bMatchList.size()];
    for (unsigned int i = 0; i < bMatchList.size(); i++) {
        bMatchArr[i] = new int[bMatchList[i].size()];
        bMatchLength[i] = bMatchList[i].size();
        for (unsigned int j = 0; j < bMatchList[i].size(); j++)
            bMatchArr[i][j] = bMatchList[i][j];
    }

    int t = 0;
    for (unsigned int i = 0; i < a.size(); i++) {
        if (match(i,
                  primeIdsA,
                  primeIdsALength,
                  bMatchArr,
                  bMatchLength,
                  visitedL,
                  visitedR,
                  matchL,
                  matchR,
                  i))
            t++;
    }

    return t;
}

int main() {
    int N, temp;
    vector<int> a, b;
    cin >> N;

    for (int i = 0; i < N; i++) {
        cin >> temp;
        a.push_back(temp);
    }

    for (int i = 0; i < N; i++) {
        cin >> temp;
        b.push_back(temp);
    }

    cout << getMaximumRemovals(a, b) << endl;

    return 0;
}
