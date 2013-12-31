#include <iostream>
#include <map>
#include <algorithm>
#include <string.h>

using namespace std;

double Matrix[1000][1000];

string Normalize(string s){
    string res;
    int num[26], val=0;
    memset(num, -1, sizeof(num));

    for(int i = 0; i < s.size(); i++) {
        if(num[s[i]-'a'] == -1)
            num[s[i]-'a'] = val++;

        res.push_back(('a' + num[s[i] - 'a']));
    }

    return res;
}

map<string, int> ids;
map<string, double> ans;

double solve(string s) {
    s = Normalize(s);

    if(ans.find(s) != ans.end())
        return ans[s];

    ids.clear();
    string next = s;
    sort(next.begin(), next.end());

    do {
        string next_s = Normalize(next);

        if(ids.find(next_s) == ids.end()) {
            int size = ids.size();
            ids[next_s] = size;
        }

    } while(next_permutation(next.begin(), next.end()));

    int N = ids.size(), len = s.size(), swapSize = len * (len-1) / 2;

    for(int i = 0; i <= N; i++)
        for(int j = 0;j <= N; j++)
            Matrix[i][j] = 0;

    for(map<string, int>::iterator it = ids.begin(); it != ids.end(); it++){
        string str = it->first;
        int id = it->second;

        if(Matrix[id][N]!=0) continue;

        Matrix[id][N] = Matrix[id][id] = 1;
        string tmp = str;

        reverse(tmp.begin(), tmp.end());

        if(tmp == str){
            Matrix[id][N] = 0;
            continue;
        }

        for(int i = 0; i < len; i++) {
            for(int j = i + 1; j < len; j++) {
                swap(str[i], str[j]);

                int id2 = ids[Normalize(str)];
                Matrix[id][id2] -= 1.0 / swapSize;
                swap(str[i], str[j]);
            }
        }
    }

    for(int i = 0; i < N; i++) {
        for(int j = N; j >= i; j--)
            Matrix[i][j] /= Matrix[i][i];

        for(int j = 0; j < N; j++) {
            if(i != j) {
                for(int k = N; k >= i; k--)
                    Matrix[j][k]-= Matrix[i][k] * Matrix[j][i];
            }
        }
    }

    for(map<string,int>::iterator it = ids.begin(); it != ids.end(); it++){
        string str = it->first;
        int id = it->second;

        if(ans.find(str) == ans.end())
            ans[str] = Matrix[id][N];
    }

    return ans[s];
}

int main() {
    int T;
    cin >> T;

    for(int t = 0; t < T; t++){
        string str;
        cin >> str;
        cout << solve(str) << endl;
    }

    return 0;
}
