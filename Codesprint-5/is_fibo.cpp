#include <iostream>
#include <cmath>

#define A sqrt((5 * pow(N, 2)) - 4)
#define B sqrt((5 * pow(N, 2)) + 4)

using namespace std;

int main() {
    int T;
    long long N;

    cin >> T;

    while(T--) {
        cin >> N;

        if(!(A - (long long)A) || !(B - (long long)B))
            cout << "IsFibo" << endl;
        else
            cout << "IsNotFibo" << endl;
    }

    return 0;
}
