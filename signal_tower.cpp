// https://www.hackerrank.com/challenges/signal-tower

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define LL long long
#define MM(a,x) memset(a,x,sizeof(a));
#define pb push_back
#define mid ((l + r) >> 1)

template<class T> void PV(T a, T b) {while(a != b) cout << *a++ << " "; cout << endl;}
template<class T> inline bool chmin(T &a, T b) {return a > b ? a = b, 1 : 0;}
template<class T> inline bool chmax(T &a, T b) {return a < b ? a = b, 1 : 0;}
const int inf = 0x3f3f3f3f;
const int mod = int(1e9) + 7;

int tr[20][100010], sum[20][100010], as[100010];
LL psum[20][100010];

void build(int p, int l, int r) {
	int lm = 0, i, ls = l, rs = mid + 1;

	for(i = mid; i >= l; i--) {
		if(as[i] == as[mid]) lm++;
		else break;
	}

	for(i = l; i <= r; i++) {
		if(i == l) sum[p][i] = 0;
		else sum[p][i] = sum[p][i - 1];

		if(tr[p][i] == as[mid]) {
			if(lm) {
				lm--;
				sum[p][i]++;
				tr[p + 1][ls++] = tr[p][i];
			} else
				tr[p + 1][rs++] = tr[p][i];
		} else if(tr[p][i] < as[mid]) {
			sum[p][i]++;
			tr[p + 1][ls++] = tr[p][i];
		} else {
			tr[p + 1][rs++] = tr[p][i];
		}
		psum[p][i] = psum[p][i - 1] + tr[p][i];
	}

	if(l == r) return;

	build(p + 1, l, mid);
	build(p + 1, mid + 1, r);
}

int query(int p, int l, int r, int ql, int qr, int k, LL &lsum) {
	int s, ss;

	if(l == r) {
		lsum += tr[p][l];
		return tr[p][l];
	}

	if(ql == l)
		s = 0, ss = sum[p][qr];
	else
		s = sum[p][ql - 1], ss = sum[p][qr] - s;

	if(k <= ss) {
		int L = l + s, R = l + sum[p][qr] - 1;
		return query(p + 1, l, mid, L, R, k, lsum);
	} else {
		lsum += psum[p + 1][l + s + ss - 1] - psum[p + 1][l + s - 1];
		int L = mid + 1 - l + ql - s, R = mid + 1 - l + qr - sum[p][qr];
		return query(p + 1, mid + 1, r, L, R, k - ss, lsum);
	}
}

int n, Q, A[100010], B[100010], X[100010], Y[100010], L[100010], R[100010];
LL psumX[100010], psumY[100010];

int main() {
	cin >> n >> Q;

	for(int i = 1; i <= n; i++) cin >> A[i];
	for(int i = 1; i <= n; i++) cin >> B[i];

	for(int i = 1; i <= n; i++) {
		X[i] = A[i] + B[i];
		Y[i] = A[i] - B[i];
		psumX[i] = psumX[i - 1] + X[i];
		psumY[i] = psumY[i - 1] + Y[i];
	}

	vector<LL> retx, rety;

    for(int i = 0; i < Q; i++) cin >> L[i] >> R[i];

	{
		for(int i = 1; i <= n; i++) {
			tr[0][i] = X[i];
			as[i] = X[i];
		}

		sort(as + 1, as + n + 1);
		build(0, 1, n);

		for(int i = 0; i < Q; i++) {
			int l = L[i], r = R[i];
			LL lsum = 0;
			LL median = query(0, 1, n, l, r, mid - l + 1, lsum);
			LL rsum = psumX[r] - psumX[l - 1] - lsum;
			LL res = (mid - l + 1) * median - lsum + rsum - (r - mid) * median;
			retx.pb(res);
		}
	}

	{
		for(int i = 1; i <= n; i++) {
			tr[0][i] = Y[i];
			as[i] = Y[i];
		}

		sort(as + 1, as + n + 1);
		build(0, 1, n);

		for(int i = 0; i < Q; i++) {
			int l = L[i], r = R[i];
			LL lsum = 0;
			LL median = query(0, 1, n, l, r, mid - l + 1, lsum);
			LL rsum = psumY[r] - psumY[l - 1] - lsum;
			LL res = (mid - l + 1) * median - lsum + rsum - (r - mid) * median;
			rety.pb(res);
		}
	}

	for(int i = 0; i < Q; i++) {
		LL ret = retx[i] + rety[i];
		cout << ret / 2;
		if(ret % 2) cout << ".50" << endl;
		else cout << ".00" << endl;
	}

	return 0;
}
