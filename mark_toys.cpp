// https://www.hackerrank.com/challenges/mark-and-toys

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int getMaxToys(int K, vector<int> toys) {
    int N = toys.size();
    sort(toys.begin(), toys.end());
    int totalSpent = 0;
    int nToys = 0;

    for (int i = 0; i < N && totalSpent + toys[i] <= K; i++) {
        totalSpent += toys[i];
        nToys++;
    }

    return nToys;
}

int main() {
    int N, K;
    vector<int> toys;

    cin >> N >> K;

    for (int i = 0; i < N; i++) {
        int toy;
        cin >> toy;
        toys.push_back(toy);
    }

    cout << getMaxToys(K, toys) << endl;

    return 0;
}
