// https://www.hackerrank.com/contests/nov13/challenges/bday-gift

#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    int N, number_ball;
    double total = 0;

    cin >> N;

    cout << fixed;
    cout << setprecision(1);

    for(int i = 0; i < N; i++) {
        cin >> number_ball;
        total += 0.5 * number_ball;
    }

    cout << total << endl;

    return 0;
}
