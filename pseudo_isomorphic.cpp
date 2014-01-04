// https://www.hackerrank.com/challenges/pseudo-isomorphic-substrings
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

#define LOGMAX 17
#define NMAX 131072
#define DEBUG 0
#define USE_FILES 0

int qans, qmin, qmax, nactsuff, pmin, pmax, N;
long long cans, sumlcp, sumactsuff;
int bit[LOGMAX + 1], logidx[NMAX];
int rmq[2][NMAX][LOGMAX], lcp[NMAX];
char S[NMAX];

void compute_bits() {
	int i, j;
	bit[0] = 1;

	for (i = 1; i <= LOGMAX; i++)
		bit[i] = bit[i - 1] << 1;

	logidx[1] = 0;

	for (i = 2, j = 1; i < NMAX; i++) {
		if (i == bit[j + 1]) j++;
		logidx[i] = j;
	}
}

void pre_compute_RMQ() {
	int i, j;

	for (i = 1; i < N; i++) {
		rmq[0][i][0] = rmq[1][i][0] = lcp[i];

		for (j = 1; j < LOGMAX && i - bit[j] >= 0; j++) {
			rmq[0][i][j] = rmq[0][i - bit[j - 1]][j - 1];

			if (rmq[0][i][j - 1] < rmq[0][i][j])
				rmq[0][i][j] = rmq[0][i][j - 1];
		}
	}

	for (i = N - 1; i >= 1; i--) {
		for (j = 1; j < LOGMAX && i + bit[j] <= N; j++) {
			rmq[1][i][j] = rmq[1][i + bit[j - 1]][j - 1];

			if (rmq[1][i][j - 1] < rmq[1][i][j])
				rmq[1][i][j] = rmq[1][i][j - 1];
		}
	}
}

void get_query() {
	int idx = logidx[qmax - qmin + 1];
	qans = rmq[0][qmax][idx];
	if (rmq[1][qmin][idx] < qans)
		qans = rmq[1][qmin][idx];
}

void read_input() {
	if (USE_FILES)
		freopen("x.txt", "r", stdin);
	scanf("%s", S + 1);
	N = strlen(S + 1);
}

void reverse_S() {
	int i;
	char c;
	for (i = 1; i <= N / 2; i++) {
		c = S[i];
		S[i] = S[N - i + 1];
		S[N - i + 1] = c;
	}
}

int D[NMAX];
map<char, int> lastpoz, nextpoz;
map<char, int>::iterator it;
vector<int> out[NMAX];
vector<pair<int, char> > vpoz;
int cidx[NMAX][30];

void pre_process_str() {
	int i, j, k;

	for (i = 1; i <= N; i++) {
		D[i] = i - lastpoz[S[i]];
		lastpoz[S[i]] = i;

		for (j = i - D[i] + 1; j <= i; j++)
			out[j].push_back(i);
	}

	if (DEBUG) {
		fprintf(stderr, "D:");

		for (i = 1; i <= N; i++)
			fprintf(stderr, " %d", D[i]);

		fprintf(stderr, "\n");
	}

	char ch;

	for (ch = 'a'; ch <= 'z'; ch++)
		nextpoz[ch] = N + 1;

	for (i = N; i >= 1; i--) {
		nextpoz[S[i]] = i;
		vpoz.clear();

		for (it = nextpoz.begin(); it != nextpoz.end(); it++)
			vpoz.push_back(make_pair(it->second, it->first));
		sort(vpoz.begin(), vpoz.end());

		for (j = 0; j < vpoz.size(); j++)
			cidx[i][vpoz[j].second - 'a'] = j;
	}
}

int group[LOGMAX + 1][NMAX], vs[NMAX], vsrev[NMAX], vsaux[NMAX], r, ii, jj, kk;

int LCP(int s1, int s2) {
	if (group[r][s1] == group[r][s2]) {
		int p = s1 + bit[r], q = s2 + bit[r], lenmax, u, poz;

		if (p > N || q > N) return bit[r];

		if (group[r][p] != group[r][q]) {
			qmin = min(vsrev[p], vsrev[q]);
			qmax = max(vsrev[p], vsrev[q]) - 1;
			get_query();
			lenmax = bit[r] + qans;
		} else
			lenmax = bit[r + 1];

		for (u = 0; u < out[p].size(); u++) {
			poz = out[p][u];

			if (poz - s1 >= lenmax) break;

			if (poz - D[poz] >= s1 && D[poz - s1 + s2] != D[poz]) {
				lenmax = poz - s1;
				break;
			}
		}

		for (u = 0; u < out[q].size(); u++) {
			poz = out[q][u];

			if (poz - s2 >= lenmax) break;

			if (poz - D[poz] >= s2 && D[poz - s2 + s1] != D[poz]) {
				lenmax = poz - s2;
				break;
			}
		}

		return lenmax;
	} else {
		qmin = min(vsrev[s1], vsrev[s2]);
		qmax = max(vsrev[s1], vsrev[s2]) - 1;
		get_query();
		return qans;
	}
}

void compute_LCPs() {
	int i, j, p, q, lenmax, u, poz;

	for (i = 1; i < N; i++)
		lcp[i] = LCP(vs[i], vs[i + 1]);

	if (DEBUG)
		for (i = 1; i < N; i++)
			fprintf(stderr, "i=%d: LCP(%d,%d)=%d\n", i, vs[i], vs[i + 1], lcp[i]);
}

int d1, d2, clcp;

inline int compare_suffixes(int s1, int s2) {
	clcp = LCP(s1, s2);
	d1 = s1 + clcp;
	d2 = s2 + clcp;

	if (d1 > N) return +1;
	if (d2 > N) return -1;
	return (cidx[s1][S[d1] - 'a'] - cidx[s2][S[d2] - 'a']);
}

void merge_sort(int li, int ls) {
	if (li >= ls) return;

	int mid = (li + ls) >> 1;

	merge_sort(li, mid);
	merge_sort(mid + 1, ls);

	ii = li; jj = mid + 1; kk = li - 1;

	while (ii <= mid && jj <= ls) {
		kk++;

		if (compare_suffixes(vs[ii], vs[jj]) <= 0) {
			vsaux[kk] = vs[ii];
			ii++;
		} else {
			vsaux[kk] = vs[jj];
			jj++;
		}
	}

	for (; ii <= mid; ii++) {
		kk++;
		vsaux[kk] = vs[ii];
	}

	for (; jj <= ls; jj++) {
		kk++;
		vsaux[kk] = vs[jj];
	}

	for (kk = li; kk <= ls; kk++)
		vs[kk] = vsaux[kk];
}

void suffix_array() {
	int i, j, ng = 1;

	for (i = 1; i <= N; i++) {
		vs[i] = i;
		vsrev[i] = i;
		lcp[i] = 1;
		group[0][i] = 0;
	}

	for (r = 0; r < LOGMAX; r++) {
		pre_compute_RMQ();
		merge_sort(1, N);

		ng = 0;
		group[r + 1][vs[1]] = 0;

		compute_LCPs();
		for (i = 2; i <= N; i++) {
			if (lcp[i - 1] != bit[r + 1])
				ng++;
			group[r + 1][vs[i]] = ng;
		}

		ng++;

		for (i = 1; i <= N; i++)
			vsrev[vs[i]] = i;

		if (DEBUG) {
			fprintf(stderr, "Suffix array after round %d/%d:", r + 1, LOGMAX);
			for (i = 1; i <= N; i++)
				fprintf(stderr, " %d(%d)", vs[i], group[r + 1][vs[i]]);
			fprintf(stderr, "\n");
		}
	}
}

int cnt[2 * NMAX];

void UpdateCnt(int idx, int v) {
	sumactsuff += v * vs[idx];
	nactsuff += v;
	idx = NMAX + idx - 1;
	while (idx >= 1) {
		cnt[idx] += v;
		idx >>= 1;
	}
}

int GetPred(int idx) {
	idx = NMAX + idx - 1;
	int p;
	while (idx > 1) {
		p = idx >> 1;
		if ((idx & 1) == 1 && cnt[p] > cnt[idx]) {
			idx--;
			break;
		}
		idx = p;
	}

	if (idx == 1)
		return 0;

	while (idx < NMAX) {
		idx <<= 1;
		if (cnt[idx + 1] >= 1)
			idx++;
	}

	return idx - NMAX + 1;
}

int GetSucc(int idx) {
	idx = NMAX + idx - 1;
	int p;
	while (idx > 1) {
		p = idx >> 1;
		if ((idx & 1) == 0 && cnt[p] > cnt[idx]) {
			idx++;
			break;
		}
		idx = p;
	}

	if (idx == 1)
		return 0;

	while (idx < NMAX) {
		idx <<= 1;
		if (cnt[idx] == 0)
			idx++;
	}

	return idx - NMAX + 1;
}

#define QSIZE 10000000

int qactsuff[QSIZE], nextqactsuff[QSIZE], startactsuff[NMAX], nq;
int idxmax[NMAX];

int update_LCPPairState(int s1, int s2, int coef) {
	int idx, result = 2;
	qmin = s1; qmax = s2 - 1;
	get_query();

	if (qans == 0)
		return 0;

	s1 = vs[s1]; s2 = vs[s2];
	if (s1 > s2) {
		idx = s1; s1 = s2; s2 = idx;
		result = 1;
	}

	idx = s2 + qans - 1;
	if (idx > pmax)
		return result;

	sumlcp += coef * qans;
	if (coef == 1) {
		if (result == 2)
			qmin = qmax + 1;
		if (idx > idxmax[qmin]) {
			nq++;
			if (nq >= QSIZE) {
				fprintf(stderr, "!! QSIZE exceeded\n");
				exit(1);
			}
			qactsuff[nq] = qmin;
			nextqactsuff[nq] = startactsuff[idx];
			startactsuff[idx] = nq;
			idxmax[qmin] = idx;
		}
	}
	return 0;
}

void update_state(int s, int coef) {
	int pred, succ, p, res, removed;

	pred = GetPred(s);
	succ = GetSucc(s);

	if (DEBUG)
		fprintf(stderr, "  suffix: s=%d pred=%d succ=%d\n", s, pred, succ);

	if (pred > 0 && succ > 0)
		update_LCPPairState(pred, succ, -1);

	removed = 0;
	while (pred > 0) {
		res = update_LCPPairState(pred, s, 1);
		if (!res)
			break;
		if (res == 1) {
			UpdateCnt(pred, -1);
			p = GetPred(pred);
			if (p > 0)
				update_LCPPairState(p, pred, -1);
			pred = p;
		} else {
			removed = 1;
			break;
		}
	}

	if (!removed) {
		while (succ > 0) {
			res = update_LCPPairState(s, succ, coef);
			if (!res)
				break;
			if (res == 2) {
				UpdateCnt(succ, -1);
				p = GetSucc(succ);
				if (p > 0)
					update_LCPPairState(succ, p, -1);
				succ = p;
			} else {
				removed = 1;
				break;
			}
		}
	}

	if (removed) {
		pred = GetPred(s);
		succ = GetSucc(s);
		if (pred > 0 && succ > 0)
			update_LCPPairState(pred, succ, 1);
	}
}

void process_op() {
	int opidx;

	sumlcp = sumactsuff = 0;
	nactsuff = 0;
	pmin = N + 1;
	pmax = N;

	for (opidx = 1; opidx <= N; opidx++) {
		pmin--;
		UpdateCnt(vsrev[pmin], 1);
		update_state(vsrev[pmin], 1);
		cans = (long long) (pmax + 1) * (long long) nactsuff;
		cans -= sumactsuff;
		cans -= sumlcp;
		if (DEBUG)
			fprintf(stderr, "op=%d pmin=%d suff=%d cans=%lld pmax=%d nactsuff=%d sumactsuff=%lld sumlcp=%lld\n", opidx, pmin, vsrev[pmin], cans, pmax, nactsuff, sumactsuff, sumlcp);
		printf("%lld\n", cans);
	}
}

int main() {
	compute_bits();
	read_input();
	reverse_S();
	pre_process_str();
	suffix_array();
	pre_compute_RMQ();
	process_op();
	return 0;
}
