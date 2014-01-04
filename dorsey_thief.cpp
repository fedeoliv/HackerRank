// https://www.hackerrank.com/challenges/dorsey-thief

#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<double,pii> pdd;

int N, X;
ll ar[MAXX];
const int MAXX = 5010, MAXN = 10010000;

pdd arr[MAXN];

int main() {
    int lim = 200000;

    scanf("%d %d", &N, &X);

    for(int i = 1; i <= X; ++i)
        ar[i] = -1;

    for(int i = 0; i < N; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        arr[i] = pdd(double(b)/a, pii(a, b));
    }

    sort(arr, arr + N);
    if (N < lim) lim = N;

    for(int i = 0; i < lim; ++i) {
        int tmp, tmp2;
        tmp = arr[i].second.second;
        tmp2 = arr[i].second.first;

        for(int j = X - tmp; j >= 0; --j)
            if (ar[j] != -1)
                ar[j + tmp] = max(ar[j + tmp], ar[j] + tmp2);
    }

    if (ar[X] == -1)
        printf("Got caught!\n");
    else
        printf("%lld\n", ar[X]);

    return 0;
}
