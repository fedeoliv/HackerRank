#include <iostream>
#include <vector>

using namespace std;

void outputSteps(vector<int> ar) {
    int M = ar.size();

    for (int N = 2; N <= M; N++) {
        int el = ar[N - 1];
        for (int i = N - 1; i >= 0; i--) {
            if (i > 0 && ar[i - 1] > el)
                ar[i] = ar[i - 1];
            else
                ar[i] = el;

            if (ar[i] <= el)
                break;
        }

        for (int j = 0; j < M; j++) {
            cout << ar[j];
            if (j + 1 < M)
                cout << " ";
            else
                cout << endl;
        }
    }
}

int main() {
    int s, x;
    cin >> s;

    vector<int> ar;
    for (int i = 0; i < s; i++) {
        cin >> x;
        ar.push_back(x);
    }

    outputSteps(ar);
}
