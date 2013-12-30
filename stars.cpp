// https://www.hackerrank.com/challenges/stars

#include <iostream>
#include <vector>

using namespace std;

double x[200], y[200], eps = 1e-6;
int w[200];

int main() {
    int n, ans = 0, cnt1, cnt2;
    double dx1, dx2, dy1, dy2;

    cin >> n;

    vector<pair<double, double> > p;
    p.clear();

    for (int i = 0; i < n; i ++) {
        cin >> x[i] >> y[i] >> w[i];

        for (int j = -1; j <= 1; j += 2)
            for (int k = -1; k <= 1; k += 2)
                p.push_back(make_pair(x[i] + j * 1e-5, y[i] + k * 1e-5));
    }

    for (int i = 0; i < p.size(); i ++) {
        for (int j = i + 1; j < p.size(); j ++) {
            cnt1 = 0;
            cnt2 = 0;
            dx1 = p[j].first - p[i].first;
            dy1 = p[j].second - p[i].second;

            for (int k = 0; k < n; k ++) {
                dx2 = x[k] - p[i].first;
                dy2 = y[k] - p[i].second;

                if (dx1 * dy2 - dx2 * dy1 > 0.0)
                    cnt1 += w[k];
                else
                  cnt2 += w[k];
            }

            ans = max(ans, min(cnt1, cnt2));
        }
    }

    cout << ans << endl;
    return 0;
}
