#include <iostream>

using namespace std;

typedef long long LL;
const int MODULO = 1000000007;

LL get_answer(LL x, LL k) {
    if (k == 0) return 1;

    if (k & 1ll)
        return (x * get_answer(x,k - 1ll)) % MODULO;
    else
        return get_answer((x * x) % MODULO, k / 2ll);
}

int main() {
    int T;
    LL A,B;
    string str_A, str_B;

    cin >> T;

    while(T--) {
        A = B = 0;

        cin >> str_A >> str_B;

        for (int i = 0; i < str_A.length(); ++i) A = (A * 10ll + (str_A[i] - '0')) % MODULO;
        for (int i = 0; i < str_B.length(); ++i) B = (B * 10ll + (str_B[i] - '0')) % (MODULO-1);

        cout << get_answer(A, B) << endl;
    }

    return 0;
}
