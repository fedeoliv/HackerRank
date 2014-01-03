#include <iostream>
#include <algorithm>

using namespace std;

#define N 111111

struct Tp {
    int l, r, add;
    int cnt[4];
} T[3*N];

void Init(int v, int l, int r) {
    T[v].l = l, T[v].r = r;
    T[v].cnt[0] = r - l  + 1;

    if (l < r) {
        Init(v + v, l, (r + l) >> 1);
        Init(v + v + 1, (r + l + 2) >> 1, r);
    }
}

void Xor(int v, int r, int x) {
    if (T[v].r <= r) {
        T[v].add ^= x;
        return;
    }

    if (T[v].l > r) return;

    Xor(v + v, r, x);
    Xor(v + v + 1, r, x);

    T[v].cnt[0] = T[v + v].cnt[T[v + v].add] + T[v + v + 1].cnt[T[v + v + 1].add];
    T[v].cnt[1] = T[v + v].cnt[T[v + v].add ^ 1] + T[v + v + 1].cnt[T[v + v + 1].add ^ 1];
    T[v].cnt[2] = T[v + v].cnt[T[v + v].add ^ 2] + T[v + v + 1].cnt[T[v + v + 1].add ^ 2];
    T[v].cnt[3] = T[v + v].cnt[T[v + v].add ^ 3] + T[v + v + 1].cnt[T[v + v + 1].add ^ 3];
}

void Cnt(int v, int r, int* ca, int add = 0) {
    if (T[v].r <= r) {
        add ^= T[v].add;
        ca[add] += T[v].cnt[0];
        ca[add ^ 1] += T[v].cnt[1];
        ca[add ^ 2] += T[v].cnt[2];
        ca[add ^ 3] += T[v].cnt[3];
        return;
    }

    if (T[v].l > r) return;

    Cnt(v + v, r, ca, add ^ T[v].add);
    Cnt(v + v + 1, r, ca, add ^ T[v].add);
}

int x[N], y[N];

int main() {
    int n, last;
    cin >> n;

    for (int i = 1; i <= n; ++i)
        cin >> x[i] >> y[i];

    Init(1, 1, n);

    last = 0;

    for (int i = n; i > 0; --i) {
        Xor(1, i, last ^ (((x[i] < 0) << 1) + (y[i] < 0)));
        last = (((x[i] < 0) << 1) + (y[i] < 0));
    }

    int q, l, r, cnt1[4], cnt2[4];
    char ch;

    cin >> q;

    for (int i = 0; i < q; ++i) {
        cin >> ch >> l >> r;

        if (ch == 'Y') {
            Xor(1, r, 2);
            if (l > 1) Xor(1, l - 1, 2);
        } else if (ch == 'X') {
            Xor(1, r, 1);
            if (l > 1) Xor(1, l - 1, 1);
        } else if (ch == 'C') {
            cnt1[0] = cnt1[1] = cnt1[2] = cnt1[3] = 0;
            cnt2[0] = cnt2[1] = cnt2[2] = cnt2[3] = 0;
            Cnt(1, r, cnt1);
            if (l > 1) Cnt(1, l - 1, cnt2);

            cout << cnt1[0] - cnt2[0] << " " << cnt1[2] - cnt2[2]
            << cnt1[3] - cnt2[3] << cnt1[1] - cnt2[1] << endl;
        }
    }

    return 0;
}
