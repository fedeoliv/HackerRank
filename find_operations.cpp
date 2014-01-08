// https://www.hackerrank.com/challenges/FLIP

#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN = 25;
int N, D;
int B[MAXN][MAXN], E[MAXN*MAXN][MAXN*MAXN], S[MAXN*MAXN];

bool is_possible(int i,int j) {
    return i >= 0 && i < N && j >= 0 && j < N;
}

int main () {
    int blah = scanf("%d%d", &N, &D);

    for (int i = 0;i < N; ++i)
        for(int j = 0;j < N; ++j) {
          blah = scanf("%d", &B[i][j]);
          S[i * N + j] = B[i][j];
        }

    for (int i = 0; i < N; ++i)
        for (int j = 0;j < N; ++j) {
          for (int a = -D; a <= D; ++a)
            for (int b = abs(a) - D; b <= D - abs(a); ++b)
              if (is_possible(i + a, j + b))
                E[i * N + j][(i + a) * N + (j + b)] = 1;
        }

    int L = N*N, cur = 0;
    bool possible = 1;

    for(int j = 0; j < L; ++j) {
        for (int i = cur; i < L; ++i)
          if (E[i][j] == 1) {
            if (i != cur) {
              for (int k=0;k<L;++k) swap(E[cur][k], E[i][k]);
              swap(S[cur], S[i]);
            }

            break;
          }

        if(E[cur][j] == 0) continue;

        for (int i = 0; i < L; ++i)
          if (i != cur && E[i][j] == 1) {
            for (int k = 0; k < L; ++k) E[i][k] ^= E[cur][k];
            S[i] ^= S[cur];
          }

        ++cur;
    }

    for (int i = L-1; i >= 0; --i) {
        int ret = 0, it = -1;

        for (int j=L-1;j>=0;--j) {
          ret += E[i][j];
          if (E[i][j]) it = j;
        }

        if(ret == 0 && S[i] == 1) {
          possible = 0;
          break;
        }

        for (int j = L-1; j >= 0 && ret > 1; --j) {
          if (E[i][j] == 1) {
            E[i][j] = 0;
            --ret;
          }
        }

        if (ret == 1) {
          for (int k=0;k<L;++k)
            if (k != i && E[k][it] == 1) {
              E[k][it] = 0;
              S[k] ^= S[i];
            }
        }
    }

    if (!possible)
        printf("Impossible\n");
    else {
        printf("Possible\n");
        int ret = 0;

        for(int i = 0; i < L; ++i) ret += S[i];
        printf("%d\n",ret);

        for(int i = 0; i < L; ++i)
          if(S[i] == 1) {
            for (int j = 0; j < L; ++j)
              if(E[i][j] == 1) {
                printf("%d %d\n", j/N, j%N);
                break;
              }
          }
    }
}
