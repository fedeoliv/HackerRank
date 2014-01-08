// https://www.hackerrank.com/challenges/assignment

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;

#define get_lines() {int c = 0; while ((c = getchar()) != 10 && c != EOF);}

typedef long double LD;

int M, N;
const LD eps = 1e-9, pi = M_PI;
const int INF = 1 << 28;
LD p1[252], dp[252][252];

LD count_prob_less(int m) {
	memset(dp, 0, sizeof dp);
	dp[0][0] = 1;

	for (int l = 1; l <= M; l++) {
		for (int n = 1; n <= M; n++) {
			dp[l][n] = dp[l][n - 1] + dp[l - 1][n - 1];

			if (n - 1 - m >= 0)
				dp[l][n] -= dp[l - 1][n - 1 - m];
		}
	}

	LD up = 0, down = 0;
	LD C = N, CM = 1;

	for (int g = 1; g <= M; g++) {
		up += dp[g][M] * C;
		down += C * CM;
		CM /= g;
		CM *= (M - g);
		C /= g + 1;
		C *= (N - g);
	}

	return up / down;
}

void get_answer() {
	LD res = 0;

	for (int i = 1; i <= M; i++)
		p1[i] = count_prob_less(i);

	for (int i = 1; i <= M; i++)
		res += i * (p1[i] - p1[i - 1]);

	cout << fixed << setprecision(5) << res << endl;
}


int main() {
	int t;
	cin >> t;

	get_lines();

	for (int i = 0; i < t; i++) {
		cin >> M >> N;
		get_answer();
	}

	return 0;
}
