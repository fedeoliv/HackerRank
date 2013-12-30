// https://www.hackerrank.com/challenges/ajourney
#include <iostream>
#include <algorithm>

using namespace std;

string multiply(string n1, string n2) {
    int s1 = n1.size();
    int s2 = n2.size();
    string res = string(s1 + s2, '0');

    for (int i = s1 - 1; i >= 0; i--) {
        int carry = 0;

        for (int j = s2 - 1; j >= 0 || carry; j--) {
            int n = (res[s1 - 1 - i + s2 - 1 - j] - '0') +
                (j >= 0 ? (n1[i] - '0') * (n2[j] - '0') : 0) + carry;
            res[s1 - 1 - i + s2 - 1 - j] = (n % 10) + '0';
            carry = n / 10;
        }
    }

    reverse(res.begin(), res.end());

    while (res[0] == '0') res.erase(res.begin());

    if (res.size() == 0)
        res = "0";

    return res;
}

string sum(string n1, string n2) {
    int s1 = n1.size();
    int s2 = n2.size();
    string res = string(max(s1, s2) + 1, '0');

    int carry = 0;
    int S = res.size();

    for (int i = 0; i < S - 1 || carry; i++) {
        int digit = carry;

        if (i < s1)
            digit += n1[s1 - 1 - i] - '0';

        if (i < s2)
            digit += n2[s2 - 1 - i] - '0';

        res[S - 1 - i] = (digit % 10) + '0';
        carry = digit / 10;
    }

    while (res.size() > 0 && res[0] == '0') res.erase(res.begin());
    if (res == "") return "0";

    return res;
}

string getNumberOfWays(int N, int K) {
    string left = "1", right = "1", nLeft = "2", nRight = "2";
    N--;

    while (N) {
        if (N & 1) {
            left = multiply(left, nLeft);
            right = multiply(right, nRight);
        }

        nLeft = multiply(nLeft, nLeft);
        nLeft = nLeft.substr(0, min(18, (int) nLeft.size()));
        nRight = multiply(nRight, nRight);
        nRight = nRight.substr(max((int) nRight.size() - 18, 0));

        N >>= 1;
    }

    return sum(left.substr(0, min(K, (int) left.size())),
               right.substr(max((int) right.size() - K, 0)));
}

int main() {
    int T, N, K;

    cin >> T;

    for (int i = 0; i < T; i++) {
        cin >> N >> K;
        cout << getNumberOfWays(N, K) << endl;
    }

    return 0;
}
