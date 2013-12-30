// https://www.hackerrank.com/challenges/similarpair

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

#define MAXN 100000

int N, T, p[MAXN + 1];
vector<int> d[MAXN + 1];
long long tree[MAXN + 1];

long long read(int i) {
    long long s = 0;

    while (i > 0) {
        s += tree[i];
        i -= (i & -i);
    }

    return s;
}

void update(int i, long long v) {
    while (i <= MAXN) {
        tree[i] += v;
        i += (i & -i);
    }
}

long long readSingle(int i) {
    return read(i) - read(i - 1);
}

long long getPairs(int i) {
    long long s = 0;
    int hi = min(i + T, MAXN);
    int lo = max(i - T, 1);

    s += read(hi) - read(lo) + readSingle(lo);

    int ne = d[i].size();

    update(i, +1);

    for (int j = 0; j < ne; j++)
        s += getPairs(d[i][j]);

    update(i, -1);

    return s;
}

long long getSimilarPairs() {
    long long t = 0;

    for (int i = 1; i <= N; i++) {
        if (p[i] == -1) {
            memset(tree, 0, sizeof(tree));
            t += getPairs(i);
        }
    }

    return t;
}

int main() {
    int a, b;

    cin >> N >> T;

    memset(p, -1, sizeof(p));

    for (int i = 0; i < N - 1; i++) {
        cin >> a >> b;
        p[b] = a;
        d[a].push_back(b);
    }

    cout << getSimilarPairs() << endl;

    return 0;
}
