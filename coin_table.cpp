// https://www.hackerrank.com/challenges/coin-on-the-table

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

#define MAXN 50
#define MAXM 50
#define INF 1000000

int N, M, K, ti, tj;
string board[MAXN];
int p[MAXN][MAXM];

void dfs(int i, int j, int k, int c) {
    if (i >= 0 && j >= 0 && i < N && j < M && c < p[i][j] && k <= K) {
        p[i][j] = c;

        dfs(i - 1, j, k + 1, c + !(board[i][j] == 'U'));
        dfs(i, j - 1, k + 1, c + !(board[i][j] == 'L'));
        dfs(i + 1, j, k + 1, c + !(board[i][j] == 'D'));
        dfs(i, j + 1, k + 1, c + !(board[i][j] == 'R'));
    }
}

int getMinOperations() {
    for (int i = 0; i < MAXN; i++)
        for (int j = 0; j < MAXM; j++)
            p[i][j] = INF;

    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            if (board[i][j] == '*') {
                ti = i;
                tj = j;
            }

    dfs(0, 0, 0, 0);

    return (p[ti][tj] == INF ? -1 : p[ti][tj]);
}

int main() {
    cin >> N >> M >> K;

    for (int i = 0; i < N; i++)
        cin >> board[i];

    cout << getMinOperations() << endl;

    return 0;
}
