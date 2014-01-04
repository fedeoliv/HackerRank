// https://www.hackerrank.com/challenges/starfleet

#include <stdio.h>
#include <algorithm>
#include <map>

using namespace std;

#define STEP_SIZE 5000
#define MAXN 50005

int N, fN, Q, V;
int occur[15][15][50005], best[15][15];
int x[MAXN], y[MAXN], F[MAXN], f[MAXN];
map<int, int> freqCompression;
pair<int, int> fp[MAXN];

int main() {
	scanf("%d%d%d", &N, &Q, &V);
	fN = 0;

	for(int i = 0; i < N; ++i) {
		scanf("%d%d%d", x+i, y+i, F+i);

		if(freqCompression[F[i]] == 0)
			freqCompression[F[i]] = ++fN;

		F[i] = freqCompression[F[i]]-1;
		fp[i] = make_pair(y[i], F[i]);
	}

	sort(fp, fp+N);

	for(int i = 0; i < N; ++i)
		f[i] = fp[i].second;

	for(int i = 0; i <= N; i += STEP_SIZE)
		for(int j = i; j <= N; j += STEP_SIZE) {
			int I = i / STEP_SIZE, J = j / STEP_SIZE;
			for(int k = 0; k < 50000; ++k)
				occur[I][J][k] = 0;

			best[I][J] = 0;

			for(int k = i; k < j; ++k) {
				++occur[I][J][f[k]];

				if(occur[I][J][f[k]] > best[I][J])
					best[I][J]=occur[I][J][f[k]];
			}
		}

	for(int i = 0; i < Q; ++i) {
		int a, b, t;
		scanf("%d%d%d", &a, &b, &t);
		int c = lower_bound(fp, fp+N, make_pair(b, -1))-fp;
		int d = lower_bound(fp, fp+N, make_pair(a, 999999999))-fp;
		int low = c / STEP_SIZE + 1, upp = d / STEP_SIZE;
		int stop = min(low*STEP_SIZE, d);
		int start = max(upp*STEP_SIZE, stop);

		if(upp < low) upp = low;
		int B = best[low][upp];

		for(int j = c; j < stop; ++j) {
			++occur[low][upp][f[j]];
			if(occur[low][upp][f[j]] > B)
				B = occur[low][upp][f[j]];
		}

		for(int j = start; j < d; ++j){
			++occur[low][upp][f[j]];
			if(occur[low][upp][f[j]] > B)
				B = occur[low][upp][f[j]];
		}

		printf("%d\n", B);

		for(int j = c; j < stop; ++j)
			--occur[low][upp][f[j]];

		for(int j = start; j < d; ++j)
			--occur[low][upp][f[j]];
	}

	return 0;
}
