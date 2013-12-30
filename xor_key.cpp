#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

#define MAXN 100000
#define MAXQ 50000
#define MAXB 15

struct Trie {
    Trie * next[2];
    vector<int> i;

    Trie() {
        this->next[0] = NULL;
        this->next[1] = NULL;
    }
};

int N, Q;
int n[MAXN];
int a[MAXQ];
int p[MAXQ];
int q[MAXQ];
int m[MAXQ];

Trie * t;

void fill(int v, int i, Trie * c, int r = MAXB) {
    int s = (v & (1 << r)) >> r;

    if (c->next[s] == NULL)
        c->next[s] = new Trie();

    c->i.push_back(i);

    if (r >= 0)
        fill(v, i, c->next[s], r - 1);
}

void calculateMaxValues() {
    memset(m, 0, sizeof(m));
    t = new Trie();

    for (int i = 0; i < N; i++)
        fill(n[i], i + 1, t);

    for (int i = 0; i < Q; i++) {
        int best = 0;

        Trie * c = t;
        for (int j = 15; j >= 0; j--) {
            int b = !((a[i] & (1 << j)) >> j);
            if (c->next[b] != NULL &&
                lower_bound(c->next[b]->i.begin(), c->next[b]->i.end(), p[i]) !=
                upper_bound(c->next[b]->i.begin(), c->next[b]->i.end(), q[i])) {
                best |= b << j;
                c = c->next[b];
            } else {
                best |= (!b) << j;
                c = c->next[!b];
            }
        }

        m[i] = best ^ a[i];
    }
}

int main() {
    int T;

    cin >> T;
    for (int i = 0; i < T; i++) {
        cin >> N >> Q;

        for (int j = 0; j < N; j++)
            cin >> n[j];

        for (int j = 0; j < Q; j++) {
            cin >> a[j];
            cin >> p[j];
            cin >> q[j];
        }

        calculateMaxValues();

        for (int j = 0; j < Q; j++)
            cout << m[j] << endl;
    }

    return 0;
}
