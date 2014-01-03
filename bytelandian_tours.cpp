// https://www.hackerrank.com/challenges/bytelandian-tours

#include<iostream>
#include<vector>

using namespace std ;

#define MOD 1000000007
#define MAXN 10002

vector<int> G[MAXN];
int n, fac[MAXN];
char isLeaf[MAXN];

int get_answer() {
    int ret = 1,path = n;

    for(int i = 0;i < n; i++)
        path -= isLeaf[i] = G[i].size() == 1;

    for(int i = 0;i < n; i++)
        if(!isLeaf[i]) {
            int ct = 0, ct2 = 0 ;

            for(int j = 0;j < G[i].size();j++)
                if(!isLeaf[G[i][j]]) ct++;
                else ct2++;

            if(ct > 2) return 0 ;
            ret = 1LL * ret * fac[ct2] % MOD;
        }

    return path == 1 ? ret : 2 * ret % MOD;
}

int main() {
    fac[0] = 1 ;

    for(int i = 1; i < MAXN; i++)
    fac[i] = 1LL * i * fac[i - 1] % MOD;

    int runs ;
    cin >> runs;

    while(runs--) {
        cin >> n;
        for(int i = 0; i < MAXN; i++)
            G[i].clear();

        for(int i = 1; i < n; i++) {
            int a, b;
            cin >> a >> b;
            G[a].push_back(b);
            G[b].push_back(a);
        }

        cout << get_answer() << endl;
    }

    return 0;
}
