// https://www.hackerrank.com/challenges/game-of-thrones

#include <bitset>
#include <iostream>

using namespace std;

int main() {
    char in;
    bitset<26> A;

    while (cin >> in)
        A.flip(in - 'a');

    cout << (A.count() <= 1 ? "YES" : "NO") << endl;

    return 0;
}
