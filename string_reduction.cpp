#include <iostream>
#include <string>

using namespace std;

#define MODULO 1000000

int a[110][110][3][2];

int main() {
    string str;
    int x, y, ts, next;

    cin >> ts;

    while (ts--) {
        cin >> str;

        for (int i = 0; i < 110; i ++) {
          for (int j = 0; j < 110; j ++) {
            for (int k = 0; k < 3; k ++)
              a[i][j][k][0] = a[i][j][k][1] = MODULO;
          }
        }

        for (int len = 1; len <= str.size(); len ++) {
            for (int i = 0; i + len - 1 < str.size(); i ++) {
                x = i;
                y = x + len - 1;

                if (x == y)
                    a[x][y][str[i] - 'a'][1] = 1;
                else {
                    for (int k = x; k + 1 <= y; k ++) {
                        for (int l1 = 0; l1 < 3; l1 ++) {
                            for (int l2 = 0; l2 < 3; l2 ++) {
                                if (l1 == l2) {
                                    a[x][y][l1][0] = min(a[x][y][l1][0], min(a[x][k][l1][0] + a[k + 1][y][l1][0], a[x][k][l1][1] + a[k + 1][y][l1][1]));
                                    a[x][y][l1][1] = min(a[x][y][l1][1], min(a[x][k][l1][0] + a[k + 1][y][l1][1], a[x][k][l1][1] + a[k + 1][y][l1][0]));
                                } else {
                                    next = 3 - l1 - l2;

                                    if (a[x][k][l1][1] < MODULO && a[k + 1][y][l2][1] < MODULO) a[x][y][next][1] = 1;
                                    if (a[x][k][l1][1] < MODULO && a[k + 1][y][l2][0] < MODULO) a[x][y][l1][1] = 1;
                                    if (a[x][k][l1][0] < MODULO && a[k + 1][y][l2][1] < MODULO) a[x][y][l2][1] = 1;
                                    if (a[x][k][l1][0] < MODULO && a[k + 1][y][l2][0] < MODULO) {
                                        a[x][y][l1][0] = min(a[x][y][l1][0], 2);
                                        a[x][y][l2][0] = min(a[x][y][l2][0], 2);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        int ans = MODULO;

        for (int i = 0; i < 3; i ++) {
            ans = min(a[0][str.size() - 1][i][0], ans);
            ans = min(ans, a[0][str.size() - 1][i][1]);
        }

        cout << ans << endl;
  }

  return 0;
}
