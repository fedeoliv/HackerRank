#include <algorithm>
#include <cstdio>

#define MAX_N 1000

using namespace std;

float g[MAX_N][MAX_N], h[2][MAX_N];
int k[MAX_N], d[MAX_N];

int remove_space() {
	int ch;
	while (true) {
		ch = getchar_unlocked();
		if (ch != ' ' && ch != '\n')
			break;
	}
	return ch;
}

template<typename T> T read_unsigned_integer() {
	T result = (T) 0;
	int ch = remove_space();
	while (ch >= '0' && ch <= '9') {
		result = 10 * result + (ch - '0');
		ch = getchar_unlocked();
	}
	return result;
}

template<typename T> T read_signed_integer() {
	T result = (T) 0;
	bool flip = false;
	int ch = remove_space();
	if (ch == '-') {
		flip = true;
		ch = remove_space();
	}
	while (ch >= '0' && ch <= '9') {
		result = 10 * result + (ch - '0');
		ch = getchar_unlocked();
	}
	return flip ? -result : result;
}

pair<float, float> get_pair(pair<float, float> x, pair<float, float> y) {
	float q = x.second * y.second;
	float p = (x.first + x.second) * (y.first + y.second) - q;
	return make_pair(p, q);
}

pair<float, float> get_pow(pair<float, float> x, int e) {
	pair<float, float> result(0.0f, 1.0f);
	pair<float, float> base = x;

	if (e > 0) {
		while (true) {
			if (e & 1) {
				result = get_pair(result, base);
			}
			e >>= 1;
			if (e <= 0)
				break;
			base = get_pair(base, base);
		}
	}

	return result;
}

void solve() {
	int n, a, b;

	n = read_unsigned_integer<int>();
	a = read_unsigned_integer<int>();
	b = read_unsigned_integer<int>();

	for (int i = 0; i < n; i++)
		d[i] = read_signed_integer<int>();

	float s = 2.0f / (n - 1) , t = (float) (n - 3) / (n - 1);
	pair<float, float> coef = get_pow(make_pair(s, t), a);
	coef.first /= n;

	int m = n * (n - 1) / 2;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			int l = min(i, j) + 1;
			int r = n - max(i, j);
			int x = min(l, r) - (i == j);
			k[j] += x;
			if (i == j)
				x += i * (i - 1) / 2 + (n - 1 - i) * (n - 1 - i - 1) / 2;
			g[i][j] = (float) x / m;
		}

	long long sum = 0;
	for (int i = 0; i < n; i++) {
		sum += d[i];
		h[0][i] = d[i];
	}

	int p = 0;
	for (int k = 0; k < b; k++) {
		float *alpha = h[p];
		p ^= 1;
		float *beta = h[p];
		for (int i = 0; i < n; i++) {
			beta[i] = 0.0;
			for (int j = 0; j < n; j++)
				beta[i] += g[i][j] * alpha[j];
		}
	}

	for (int i = 0; i < n; i++)
		h[p][i] = coef.first * sum + coef.second * h[p][i];

	float result = 0.0;
	for (int i = 0; i < n; i++)
		result += k[i] * h[p][i];
	result /= m;
	printf("%f\n", result);
}

int main() {
	solve();
	return 0;
}
