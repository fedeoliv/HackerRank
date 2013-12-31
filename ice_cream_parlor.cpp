// https://www.hackerrank.com/challenges/icecream-parlor

#include <iostream>
#include <map>
#include <vector>

using namespace std;

pair<int, int> getFlavorIndexes(vector<int> prices, int C) {
    int N = prices.size();

    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (prices[i] + prices[j] == C)
                return make_pair(i + 1, j + 1);
        }
    }

    return make_pair(-1, -1);
}

int main() {
    int T, C, L, temp;

    cin >> T;

    for (int i = 0; i < T; i++) {
        cin >> C >> L;
        vector<int> prices;

        for (int j = 0; j < L; j++) {
            cin >> temp;
            prices.push_back(temp);
        }

        pair<int, int> idx = getFlavorIndexes(prices, C);
        cout << idx.first << " " << idx.second << endl;
    }

    return 0;
}
