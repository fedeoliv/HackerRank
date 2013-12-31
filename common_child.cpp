// https://www.hackerrank.com/challenges/common-child

#include <iostream>
#include <string>

using namespace std;

#define MAX 5000

string s1, s2;
int c[MAX + 1][MAX + 1];

int getCommonChild() {
    int M = s1.size();
    int N = s2.size();

    for (int i = 1; i <= M; i++)
        c[i][0] = 0;

    for (int j = 0; j <= N; j++)
        c[0][j] = 0;

    for (int i = 1; i <= M; i++) {
        for (int j = 1; j <= N; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                c[i][j] = c[i - 1][j - 1] + 1;
            } else if (c[i - 1][j] >= c[i][j - 1]) {
                c[i][j] = c[i - 1][j];
            } else {
                c[i][j] = c[i][j - 1];
            }
        }
    }

    return c[M][N];
}

int main() {
    cin >> s1 >> s2;
    cout << getCommonChild() << endl;
    return 0;
}
