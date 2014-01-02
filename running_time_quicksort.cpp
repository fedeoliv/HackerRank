#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int quickSortCount(vector<int> &ar, int lo, int hi){
    if (lo + 1 >= hi) return 0;
    int mid = lo, total = 0;

    for (int i = lo; i < hi - 1; i++){
        if (ar[i] < ar[hi - 1]){
            swap(ar[i], ar[mid++]);
            total++;
        }
    }

    swap(ar[mid], ar[hi - 1]);
    total++;
    total += quickSortCount(ar, lo, mid);
    total += quickSortCount(ar, mid + 1, hi);

    return total;
}

int insertSortCount(vector<int> &ar){
    int n = ar.size(), total = 0;

    for (int i = 1; i < n; i++){
        int p = ar[i];
        int j = i - 1;

        while (j >= 0 && ar[j] > p){
            ar[j + 1] = ar[j];
            total++;
            j--;
        }

        ar[j + 1] = p;
    }

    return total;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int n; cin >> n;
    vector<int> ar(n); for (auto &a: ar) cin >> a;
    vector<int> ar1(ar);
    cout << insertSortCount(ar1) - quickSortCount(ar, 0, n) << endl;
    return 0;
}
