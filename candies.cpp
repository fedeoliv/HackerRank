#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int getMinimumCandies(vector<int> c) {
    int N = c.size();
    vector<int> minR = vector<int>(N, 1);
    vector<int> minL = vector<int>(N, 1);

    for (int i = N - 2; i >= 0; i--) {
        if (c[i + 1] < c[i])
            minR[i] = 1 + minR[i + 1];
    }

    for (int i = 1; i < N; i++) {
        if (c[i - 1] < c[i])
            minL[i] = 1 + minL[i - 1];
    }

    int t = 0;
    for (int i = 0; i < N; i++)
        t += max(minR[i], minL[i]);

    return t;
}

int main() {
    int N, x;
    cin >> N;

    vector<int> c;
    for (int i = 0; i < N; i++) {
        cin >> x;
        c.push_back(x);
    }

    cout << getMinimumCandies(c) << endl;

    return 0;
}
