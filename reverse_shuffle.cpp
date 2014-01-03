// https://www.hackerrank.com/challenges/reverse-shuffle-merge

#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <string.h>

using namespace std;

char S[10240];
int cnt[10240][26], sub[26];

int main() {
    scanf("%s", S);

    int N = strlen(S);

    memset(cnt,0,sizeof(cnt));
    reverse(S, S+N);

    for (int p = N-1; p >= 0; p--) {
        copy(cnt[p+1], cnt[p+1]+26, cnt[p]);
        cnt[p][S[p]-'a'] += 1;
    }

    copy(cnt[0], cnt[0]+26, sub);

    for (int c = 0; c < 26;c++)
        sub[c] /= 2;

    int startPoint = -1, endPoint = 0;

    for (int i=0; i+i<N; i++) {
        do {
            startPoint += 1;
        } while (sub[S[startPoint] - 'a'] == 0);

        for (int p = startPoint; p < N; p++) {
            if ((sub[S[p]-'a']>0) && (S[p] < S[startPoint])) {
                if (p < endPoint)
                    startPoint = p;
                else {
                    int cmpres = 1;

                    for (int c = 0; c < 26; c++)
                        if (cnt[p][c] < sub[c]) {
                            cmpres = -1;
                            break;
                        }

                    if (cmpres == -1) break;

                    startPoint = p;
                    endPoint += 1;
                }
            }
        }

        sub[S[startPoint] - 'a'] -= 1;
        putchar(S[startPoint]);
    }

    puts("");
    return 0;
}
