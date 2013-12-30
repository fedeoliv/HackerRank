#include <iostream>
#include <string>

using namespace std;

string getLargestDecentNumber(int N) {
    int n5 = -1;
    for (int i = 0; i <= N; i++) {
        if (i % 3 == 0 && (N - i) % 5 == 0)
            n5 = i;
    }

    if (n5 != -1)
        return string(n5, '5') + string(N - n5, '3');

    return "-1";
}

int main() {
    int T, N;
    cin >> T;

    for (int i = 0; i < T; i++) {
        cin >> N;
        cout << getLargestDecentNumber(N) << endl;
    }

    return 0;
}
