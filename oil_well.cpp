// https://www.hackerrank.com/challenges/oil-well

#include <iostream>
#include <cmath>
using namespace std;

#define MAX 53
#define INF 30300000

int n, m, a[MAX][MAX], s[MAX][MAX][MAX][MAX];

void read(void){
	cin >> n >> m;

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			cin >> a[i][j];
}

int mod(int x) {
	return x < 0 ? -x : x;
}

int fine(int x, int y, int l, int r, int u, int d) {
	return max(max(abs(l-x), abs(x-r)), max(abs(y-d), abs(y-u)));
}

void din(void){
	for (int i = 0; i < n; ++i)
		for (int l = 0; l+i < n; ++l)
			for (int j = 0; j < m; ++j)
				for (int u = 0; u+j < m; ++u) {
					int r = l+i, d = u+j;

					if (l == r && u==d) {
						s[l][r][u][d]=0;
						continue;
					}

					int h = INF;

					if (l < r) {
						int kl = 0, kr = 0;
						for (int j = u; j <= d; ++j){
							if (a[l][j])
								kl += fine(l, j, l+1, r, u, d);

							if (a[r][j])
								kr += fine(r, j, l, r-1, u, d);
						}

						h = min(h, s[l+1][r][u][d] + kl);
						h = min(h, s[l][r-1][u][d] + kr);
					}

					if (u < d) {
						int ku = 0, kd = 0;
						for (int j = l; j <= r; ++j){
							if (a[j][u])
								ku += fine(j, u, l, r, u+1, d);
							if (a[j][d])
								kd += fine(j, d, l, r, u, d-1);
						}

						h = min(h, s[l][r][u+1][d] + ku);
						h = min(h, s[l][r][u][d-1] + kd);
					}

					s[l][r][u][d] = h;
				}

	cout << s[0][n-1][0][m-1] << endl;
}

int main() {
	read();
	din();

	return 0;
}
