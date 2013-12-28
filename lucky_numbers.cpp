// https://www.hackerrank.com/challenges/lucky-numbers

#include <iostream>
using namespace std;

typedef unsigned long long LL;
const int MAX_LENGTH = 18, MAX_SUM = 162, MAX_SQUARE_SUM = 1458;
int primes[1460], start[19][163], end[19][163];

LL dyn_table[20][164][1460];
LL ans[19][10][164][1460];

void get_primes() {
    for (int i = 0; i <= MAX_SQUARE_SUM; ++i)
        primes[i] = 1;

    primes[0] = primes[1] = 0;

    for (int i = 2; i * i <= MAX_SQUARE_SUM; ++i) {
        if (!primes[i]) continue;

        for (int j = 2; i * j <= MAX_SQUARE_SUM; ++j)
            primes[i*j] = 0;
    }
}

void get_table() {
    for (int i = 0; i <= MAX_LENGTH; i++) {
        for (int j = 0; j <= MAX_SUM; j++) {
            for (int k = 0; k <= MAX_SQUARE_SUM; k++) {
                dyn_table[i][j][k] = 0;
            }
        }
    }

    dyn_table[0][0][0] = 1;

    for (int i = 0; i < MAX_LENGTH; i++)
        for (int j = 0; j <= 9 * i; j++)
            for (int k = 0; k <= 9 * 9 * i; k++)
                for (int l = 0; l < 10; ++l)
                    dyn_table[i + 1][j + l][k + l*l] += dyn_table[i][j][k];
}

LL count_lucky (LL maxp) {
    LL result = 0, step_result, step;
    int len = 0, split_max[MAX_LENGTH], sum = 0, sq_sum = 0;

    while (maxp) {
        split_max[len] = maxp % 10;
        maxp /= 10;
        len++;
    }

    for (int i = len-1; i >= 0; i--) {
        step_result = 0;
        int x1 = 9 * i;

        for (int l = 0; l < split_max[i]; l++) {
            int x = l*l + sq_sum, y = l + sum;
            step = 0;

            if(ans[i][l][sum][sq_sum] != 0) {
                step_result +=ans[i][l][sum][sq_sum];
                continue;
            }

            for (int j = 0; j <= x1; j++) {
                if(primes[j + y])
                    for (int k = start[i][j]; k <= end[i][j]; k++) {
                        if (primes[k + x]) {
                            step_result += dyn_table[i][j][k];
                            step += dyn_table[i][j][k];
                        }
                }
            }

            ans[i][l][sum][sq_sum] = step;
        }

        result += step_result;
        sum += split_max[i];
        sq_sum += split_max[i] * split_max[i];
    }

    if (primes[sum] && primes[sq_sum]) result++;
    return result;
}

int main() {
    get_primes();
    get_table();

    for(int i = 0; i <= 18; i++)
        for(int j = 0;j <= 163; j++) {
            for(int k = 0; k <= 1458; k++)
                if(dyn_table[i][j][k] != 0ll) {
                    start[i][j] = k;
                    break;
                }

                for(int k = 1460; k >= 0; k--)
                    if(dyn_table[i][j][k] != 0ll) {
                        end[i][j]=k;
                        break;
                    }
        }

    int cases = 0;
    cin >> cases;

    for (int i = 0; i < cases; i++) {
        LL a, b;

        cin >> a >> b;

        if(b == 1000000000000000000ll) b--;
        cout << count_lucky(b) - count_lucky(a-1) << endl;
    }

    return 0;
}
