// https://www.hackerrank.com/challenges/stone-piles

#include <iostream>
#include <vector>
#include <set>
#include <string>

using namespace std;

int n, ans[51];
set<int> st;

void dfs(int start, int rest, int result) {
    if (rest == 0)
        st.insert(result);
    else
        for (int i = start + 1; i <= rest && i < n; i ++)
            dfs(i, rest - i, result ^ ans[i]);
}

int main() {
    ans [1] = ans[2] = 0;
    int i, j, t, res = 0;
    string str[2] = {"BOB", "ALICE"};

    for (i = 3; i <= 50; i ++) {
        n = i;
        st.clear();

        dfs(0, i, 0);
        set<int>::iterator it;

        for (j = 0; st.find(j) != st.end(); j ++);
            ans[i] = j;
    }

    cin >> t;

    while (t--) {
        cin >> n;
        res = 0;

        for (i = 0; i < n; i ++) {
            cin >> j;
            res = res ^ ans[j];
        }

        if (res == 0)
            cout << str[0] << endl;
        else
            cout << str[1] << endl;
    }

    return 0;
}
