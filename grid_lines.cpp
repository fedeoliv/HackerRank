#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;
const int MAXN = 3033, MOD = 1000000007;
int N, M, K, C_cache[MAXN][MAXN], C_visited[MAXN][MAXN];
int gcd_cache[MAXN][MAXN], gcd_visited[MAXN][MAXN];

int C(int n, int k) {
    if (k < 0 || k > n) return 0;
    if (k == 0 || k == n) return 1;

    int &res = C_cache[n][k];

    if (C_visited[n][k]) return res;

    C_visited[n][k] = true;
    res = C(n - 1, k) + C(n - 1, k - 1);

    if (res >= MOD) res -= MOD;
    return res;
}

void C_init() {
    for (int i = 0; i <= max(N, M); i++){
        C_cache[i][K - 2] = C(i, K - 2);
        C_cache[i][K - 2] %= MOD;
        C_visited[i][K - 2] = true;
    }
}

int gcd(int a, int b){
    int &res = gcd_cache[a][b];
    if (gcd_visited[a][b]) return res;
    gcd_visited[a][b] = true;
    return res = b == 0? a: gcd(b, a % b);
}

void gcd_init(){
    for (int i = 0; i < MAXN; i++){
        for (int j = 0; j < MAXN; j++){
            gcd_cache[i][j] = gcd(i, j);
            gcd_visited[i][j] = true;
        }
    }
}

int F_cache[MAXN][MAXN];
int F_visited[MAXN][MAXN];

int F(int n, int m){
    if (n < 0 || m < 0) return 0;
    int &res = F_cache[n][m];
    if (F_visited[n][m]) return res;
    F_visited[n][m] = true;
    int t = gcd(n, m);
    res = C(t - 1, K - 2);
    return res;
}

void F_init(){
  for (int i = 0; i <= N; i++){
    for (int j = 0; j <= M; j++){
      int tmp = gcd_cache[i][j] - 1;
      if (tmp >= 0){
        F_cache[i][j] = C_cache[tmp][K - 2];
        F_cache[i][j] %= MOD;
      }

      F_visited[i][j] = true;
    }
  }
}

int F1_cache[MAXN][MAXN];
int F1_visited[MAXN][MAXN];

int F1(int n, int m){
    if (n < 0 || m < 0) return 0;
    int &res = F1_cache[n][m];
    if (F1_visited[n][m]) return res;
    F1_visited[n][m] = true;
    res = F1(n, m - 1) + F(n, m);
    if (res >= MOD) res -= MOD;
    return res;
}

void F1_init(){
  for (int i = 0; i <= N; i++){
    for (int j = 0; j <= M; j++){
      F1_cache[i][j] = (j - 1 >= 0 ? F1_cache[i][j - 1] : 0) + F_cache[i][j];
      F1_cache[i][j] %= MOD;
      F1_visited[i][j] = true;
    }
  }
}

int F2_cache[MAXN][MAXN];
int F2_visited[MAXN][MAXN];

int F2(int n, int m){
    if (n < 0 || m < 0) return 0;
    int &res = F2_cache[n][m];
    if (F2_visited[n][m]) return res;
    F2_visited[n][m] = true;
    res = F2(n - 1, m) + F1(n, m);
    if (res >= MOD) res -= MOD;
    return res;
}

void F2_init(){
  for (int i = 0; i <= N; i++){
    for (int j = 0; j <= M; j++){
      F2_cache[i][j] = (i - 1 >= 0 ? F2_cache[i - 1][j] : 0) + F1_cache[i][j];
      F2_cache[i][j] %= MOD;
      F2_visited[i][j] = true;
    }
  }
}

int solve(){
  LL total = 0;

  for (int i = 0; i < M; i++){
    total += F2(N, i) + F2(N, M - i) - F2(N, 0);
    total %= MOD;
  }

  for (int i = 0; i < N; i++){
    total += F2(i, M) + F2(N - i, M) - F2(0, M);
    total %= MOD;
  }

  total *= 2;
  total %= MOD;
  LL total1 = 0;

  for (int i = 0; i < N; i++){
    total1 += F2(M, i) - F2(M - 1, i - 1);
    total1 += F2(M, N - i) - F2(M - 1, N - i - 1);
    total1 -= F(0, M);
    total1 += F1(0, i - 1);
    total1 += F1(0, N - i - 1);
    total1 %= MOD;
  }

  for (int i = 0; i < M; i++){
    total1 += F2(N, i) - F2(N - 1, i - 1);
    total1 += F2(N, M - i) - F2(N - 1, M - i - 1);
    total1 -= F(0, N);
    total1 += F1(0, i - 1);
    total1 += F1(0, M - i - 1);
    total1 %= MOD;
  }

  return ((total - total1)%MOD + MOD)%MOD;
}

int main() {
    cin >> N >> M >> K;
    C_init();
    gcd_init();
    F_init();
    F1_init();
    F2_init();

    cout << solve() << endl;
    return 0;
}
