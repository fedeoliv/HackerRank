// https://www.hackerrank.com/challenges/fairy-chess

#include <iostream>
#include <vector>

using namespace std;

const int MODULO = 1000000007;

void get_ways() {
    int N, M, S; cin >> N >> M >> S;

    vector< vector<int> > A(2 * N + 1, vector<int>(2 * N + 1, 0));
    vector< vector<int> > ways(2 * N + 1, vector<int>(2 * N + 1, 0));

    for (int i = 0; i < N; ++i) {
        string S; cin >> S;

        for (int j = 0; j < N; ++j) {
            if (S[j] == 'P') continue;

            int x = i + j + 1;
            int y = N - i + j;

            A[x][y] = 1;

            if (S[j] == 'L') ++ways[x][y];
        }
    }

    auto add = [](int &value, int amount) {
        value += amount;

        if (value >= MODULO) value -= MODULO;
        if (value < 0) value += MODULO;
    };

    for (int i = 0; i < M; ++i) {
        vector< vector<int> > past(2 * N + 1, vector<int>(2 * N + 1, 0));
        swap(past, ways);

        for (int j = 0; j < 2 * N + 1; ++j)
            for (int k = 0; k < 2 * N + 1; ++k) {
                if (j > 0)
                    add(past[j][k], past[j - 1][k]);
                if (k > 0)
                    add(past[j][k], past[j][k - 1]);
                if (j > 0 and k > 0)
                    add(past[j][k], -past[j - 1][k - 1]);
            }

        for (int j = 0; j < 2 * N + 1; ++j)
            for (int k = 0; k < 2 * N + 1; ++k) {
                if (A[j][k] == 0) continue;

                int x1 = max(j - S, 0);
                int x2 = min(j + S, 2 * N);

                int y1 = max(k - S, 0);
                int y2 = min(k + S, 2 * N);

                ways[j][k] = past[x2][y2];

                if (x1 > 0)
                    add(ways[j][k], -past[x1 - 1][y2]);
                if (y1 > 0)
                    add(ways[j][k], -past[x2][y1 - 1]);
                if (x1 > 0 and y1 > 0)
                    add(ways[j][k], past[x1 - 1][y1 - 1]);
            }
    }

    int output = 0;

    for (int i = 0; i < 2 * N + 1; ++i)
        for (int j = 0; j < 2 * N + 1; ++j)
            add(output, ways[i][j]);

    cout << output << endl;
}

int main() {
    int T;
    cin >> T;

    while (T--) get_ways();
    return 0;
}
