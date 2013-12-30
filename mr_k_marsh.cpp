#include <iostream>
#include <string>

using namespace std;

#define MAX 500

int M, N;
string l[MAX];
bool h[MAX][MAX][MAX], v[MAX][MAX][MAX];

int getPerimeter() {
    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++)
            for (int k = 0; k < MAX; k++) {
                h[i][j][k] = false;
                v[i][j][k] = false;
            }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (l[i][j] == '.') {
                h[i][j][j] = true;
                v[j][i][i] = true;
            }
        }
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = j + 1; k < N; k++) {
                h[i][j][k] = h[i][j][k - 1] && l[i][k] == '.';
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            for (int k = j + 1; k < M; k++) {
                v[i][j][k] = v[i][j][k - 1] && l[k][i] == '.';
            }
        }
    }

    int best = 0;

    for (int i = 0; i < M; i++) {
        for (int j = i + 1; j < M; j++) {
            for (int k = 0; k < N; k++) {
                if (v[k][i][j]) {
                    int lo = k + 1;
                    int hi = N - 1;
                    while (lo <= hi) {
                        int mid = (lo + hi) / 2;
                        if (h[i][k][mid] && h[j][k][mid]) {
                            lo = mid + 1;
                        } else {
                            hi = mid - 1;
                        }
                    }
                    for (int l = lo; l > k; l--) {
                        if (v[l][i][j] && h[i][k][l] && h[j][k][l]) {
                            int l1 = j - i + 1;
                            int l2 = l - k + 1;
                            best = max(best, 2 * (l1 - 1) + 2 * (l2 - 1));
                            break;
                        }
                    }
                }
            }
        }
    }

    return best;
}

int main() {
    cin >> M >> N;
    for (int i = 0; i < M; i++) {
        cin >> l[i];
    }
    int p = getPerimeter();
    if (p > 0)
        cout << p << endl;
    else
        cout << "impossible" << endl;
    return 0;
}
