// https://www.hackerrank.com/challenges/missile-defend

#include <stdio.h>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

#define NMAX 131072

int N, M, i, j, f, t, x, y, lmax, v[NMAX << 1];
map<pair<int, int>, int> cnt;
map<pair<int, int>, int>::iterator it;
map<int, int> ycoord_map;
set<int> ycoord;
set<int>::iterator yit;

int get_query(int a) {
	int b = NMAX + a - 1, result = 0;

	while (b > 1) {
		if ((b & 1) == 1)
			result = max(result, v[b - 1]);

		b = b >> 1;
	}

	return result;
}

void update(int a, int val) {
	int b = NMAX + a - 1;

	while (b >= 1) {
		v[b] = max(v[b], val);
		b = b >> 1;
	}
}

int main() {
	scanf("%d", &N);

	for (i = 0; i < N; i++) {
		scanf("%d %d", &t, &f);
		x = t - f;
		y = f + t;
		cnt[make_pair(-x, -y)]++;
		ycoord.insert(y);
	}

	for (M = 0, yit = ycoord.begin(); yit != ycoord.end(); yit++) {
		M++;
		ycoord_map[*yit] = M;
	}

	for (it = cnt.begin(); it != cnt.end(); it++) {
		j = ycoord_map[-(it->first.second)];
		lmax = get_query(j);
		lmax++;
		update(j, lmax);
	}

	printf("%d\n", v[1]);

	return 0;
}
