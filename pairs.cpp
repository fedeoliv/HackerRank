// https://www.hackerrank.com/challenges/pairs

#include <iostream>
#include <algorithm>

using namespace std;

#define LOOP_J(i, b, n) for (int i = b; i < n; i++)
#define LOOP_I(i, n) LOOP_J(i, 0, n)

int nums[100000];

int main(void) {
    int n, k;
    int pairs = 0;

    cin >> n >> k;

    LOOP_I(i, n) cin >> nums[i];
    sort(nums, nums + n, greater<int>());

    LOOP_I(i, n) {
        LOOP_J(j, i + 1, n) {
            if (nums[i] - nums[j] == k) pairs++;
            if (nums[i] - nums[j] > k) break;
        }
    }

    cout << pairs << endl;

    return 0;
}
