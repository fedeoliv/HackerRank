#include <stdio.h>
#include <string.h>
#include<iostream>
#include<algorithm>
using namespace std;

int input_int() { int x; scanf("%d", &x); return x; }

#define ZAXLEN 220000
int F[ZAXLEN];
char textbuf[ZAXLEN];
char pattern[ZAXLEN];
int  prefix[ZAXLEN];
int  suffix[ZAXLEN];

void build_failure_function(int plen, int *Z)
{
    int i,j;

    memset(F, 0, sizeof(int) * plen);
    memset(Z, -1, sizeof(int) * plen);
    F[0] = F[1] = 0;
    Z[0] = plen;
    for(i = 2; i <= plen; i++) {
        j = F[i - 1];
        while(1) {
            if(pattern[j] == pattern[i - 1]) {
                F[i] = j + 1; Z[i - F[i]] = F[i]; break;
            }
            if(j == 0) { F[i] = 0; Z[i - 1]=0; break; }
            j = F[j]; Z[i - j - 1] = max(j,Z[i - j - 1]) ;
        }
    }
    for (i=1; i<plen; ) {
        int k = Z[i];
        if (Z[i] >= 0) {
            i ++;
            for (j = 1; j<k && (Z[i]== -1); j++, i++) Z[i] = Z[j];
        }
    }
}


int main(int argc, char * argv[]) {
    int t = input_int();
    int plen, tlen;
    for(; t>0; t--) {
        memset(prefix, 0, sizeof(prefix));
        memset(suffix, 0, sizeof(suffix));
        scanf("%s", textbuf);
        tlen = strlen(textbuf);
        scanf("%s", pattern);
        plen = strlen(pattern);
        char * text = pattern + plen + 1;
        copy(textbuf, textbuf + tlen, text);

        build_failure_function(plen+1+tlen, prefix);
        int* textprefix = prefix+plen+1;

        reverse(text, text + tlen);
        reverse(pattern, pattern + plen);
        build_failure_function(plen+1+tlen, suffix);

        int* textsuffix = suffix+plen+1;
        reverse(textsuffix, textsuffix + tlen);
        textsuffix[tlen] = 0;
        int last = -1;
        for (int i=0; i+plen<=tlen; i++) {
            if (textprefix[i] + textsuffix[i + plen - 1] >= plen - 1) {
                if (last > -1) {
                    printf(" ");
                }
                last = i;
                printf("%d", i);
            }
        }
        puts("");
        gets(text);
    }
}
