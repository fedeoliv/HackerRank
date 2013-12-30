#include <iostream>
#include <cstdio>
#include <set>

using namespace std;
pair<int,long long> a[150100];

int main() {
    int n, t;

    scanf("%d", &t);

    while (t--) {
        scanf("%d", &n);

        for (int i = 0; i < n; i ++)
            scanf("%d", &a[i].first);

        for (int i = 0; i < n; i ++)
            scanf("%lld", &a[i].second);

        set<pair<int, long long> > result;

        result.clear();
        result.insert(make_pair(0, 0));

        set<pair<int, long long> >::iterator it, it2;
        long long answer = a[0].second;

        for (int i = 0; i < n; i ++) {
            it = result.lower_bound(make_pair(a[i].first, 0LL));
            it --;
            a[i].second += it->second;
            bool flag = true;

            for (it ++; it != result.end(); ) {
                if (it -> first == a[i].first && it->second > a[i].second)
                  flag = false;

                if (it->second <= a[i].second) {
                  it2 = it;
                  it ++;
                  result.erase(it2);
                } else break;
            }

            if (flag) {
                result.insert(a[i]);
                answer = max(answer, a[i].second);
            }
        }

        cout << answer << endl;
    }

    return 0;
}
