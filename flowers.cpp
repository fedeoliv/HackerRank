#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int getMinimumPrice(vector<int> flowers, int K) {
    int p = 0;
    int N = flowers.size();
    int x = 0;
    int c = 0;
    vector<int> m = vector<int>(N, 0);

    sort(flowers.begin(), flowers.end());
    for (int i = N - 1; i >= 0; i--) {
        m[i] = x;
        c++;
        if (c >= K) {
            x++;
            c = 0;
        }
    }

    for (int i = 0; i < N; i++)
        p += (m[i] + 1) * flowers[i];

    return p;
}

int main() {
    int N, K, f;
    cin >> N >> K;

    vector<int> flowers;
    for (int i = 0; i < N; i++) {
        cin >> f;
        flowers.push_back(f);
    }

    cout << getMinimumPrice(flowers, K) << endl;

    return 0;
}
