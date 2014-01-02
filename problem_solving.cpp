// https://www.hackerrank.com/challenges/problem-solving

#include <iostream>
#include <cstring>

using namespace std;

#define abs(x) ((x) > 0 ? (x) : -(x))

const int MAX = 305;
int N, K;
int v[MAX], cx[MAX], cy[MAX], adj[MAX][MAX], mk[MAX];

bool path(int i) {
    for (int j = 1; j <= N; j++) {
        if (adj[i][j] && !mk[j]) {
            mk[j] = true;

            if (cy[j] == -1 || path(cy[j])) {
                cx[i] = j;
                cy[j] = i;
                return true;
            }
        }
    }

    return false;
}

int get_max_match() {
    int res = 0;

    memset(cx, -1, sizeof(cx));
    memset(cy, -1, sizeof(cy));

    for (int i = 1; i <= N; i++) {
        memset(mk, 0, sizeof(mk));

        if (path(i)) res++;
    }

    return res;
}

int main() {
    int test;
    cin >> test;

    while (test--) {
        memset(adj, 0, sizeof(adj));

        cin >> N >> K;

        for (int i = 1; i <= N; i++)
                cin >> v[i];

        for (int i = 1; i <= N; i++)
            for (int j = i + 1; j <= N; j++)
                if (abs(v[j] - v[i]) >= K) adj[i][j] = 1;

        cout << N - get_max_match() << endl;
    }

    return 0;
}
