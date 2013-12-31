// https://www.hackerrank.com/challenges/circle-summation

#include <iostream>
#include <cstdio>
#include <vector>
#include <list>
#include <unordered_set>

using namespace std;

typedef unsigned long long ullong;

#define MOD_NUM 1000000007ull

class SquareMatrix {
public:
        SquareMatrix(int _size, int _exp)
                : size(_size), exp(_exp) {
                //cout << _size << " " << _exp << endl;
                M = vector< vector<ullong> > (size, vector<ullong>(size, 0));
                orig = vector< vector<ullong> > (size, vector<ullong>(size, 0));
                initCircleSummation();
        }

        void multiply(const vector<ullong> &v, vector<ullong> & output) {
                output = vector<ullong>(v.size(), 0);
                for(int row = 0; row < size; ++row)
                        for(int col = 0; col < size; ++col)
                                output[row] =
                                        (output[row] + (M[row][col] * v[col])%MOD_NUM)
                                        %MOD_NUM;
        }

        void print() {
                for(int row = 0; row < size; ++row) {
                        for(int col = 0; col < size; ++col)
                                printf("%d ", M[row][col]);
                        printf("\n");
                }
                printf("\n");
        }

private:
        void initCircleSummation() {
                for(int index = 1; index < size; index++)
                        orig[index-1][index] = M[index-1][index] = 1;
                M[size-1][0] = M[size-1][1] = M[size-1][size-1] = 1;
                orig[size-1][0] = orig[size-1][1] = orig[size-1][size-1] = 1;
                findExponential(exp);
        }

        void findExponential(int _exp) {

                if(_exp >= 2) {
                        findExponential(_exp/2);
                        multiplyWithItself();

                        if(_exp % 2 == 1)
                                multiplyWithOriginal();
                }
        }
        void multiplyWithItself() {
                vector<vector<ullong> > temp =
                        vector< vector<ullong> > (size, vector<ullong>(size, 0));
                for(int row = 0; row < size; ++row)
                        for(int col = 0; col < size; ++col) {
                                for(int k = 0; k < size; ++k)
                                    temp[row][col] =
                                                (temp[row][col] + (M[row][k] *
                                                                                   M[k][col] ) %MOD_NUM )
                                                % MOD_NUM;
                        }

                for(int row = 0; row < size; ++row)
                        for(int col = 0; col < size; ++col)
                                M[row][col] = temp[row][col];
        }

        void multiplyWithOriginal() {
                vector<vector<ullong> > temp =
                        vector< vector<ullong> > (size, vector<ullong>(size, 0));
                for(int row = 0; row < size; ++row)
                        for(int col = 0; col < size; ++col) {
                                for(int row2 = 0; row2 < size; ++row2)
                                    temp[row][col] =
                                                (temp[row][col] + (M[row][row2] *
                                                                                   orig[row2][col] ) %MOD_NUM )
                                                % MOD_NUM;
                        }
                for(int row = 0; row < size; ++row)
                        for(int col = 0; col < size; ++col)
                                M[row][col] = temp[row][col];
        }

        vector<vector<ullong> > M, orig;
        int size;
        int exp;
};

void print(vector<ullong> &vec, int n) {
        int index = 0;
        for(auto it = vec.begin() + vec.size() - n;
                it != vec.end(); ++it, ++index) {
                printf("%d", *it);
                if(index < vec.size()-1)
                        printf(" ");
        }
        for(auto it = vec.begin();
                it != vec.begin() + vec.size() - n; ++it, ++index) {
                printf("%d", *it);
                if(index < vec.size()-1)
                        printf(" ");
        }
}

void rotateBy1(vector<ullong> &vec) {
        list<ullong> rotated(vec.begin()+1, vec.end());
        rotated.push_back(vec[0]);
        vec.clear();
        vec = vector<ullong>(rotated.begin(), rotated.end());
}

void solveCircleSummation() {
        int nTests;
        scanf(" %d", &nTests);
        for(int test = 0; test < nTests; ++test) {
                int N;
                int mSize;
                scanf(" %d %d", &N, &mSize);

                vector<ullong> vec;
                for(int entry = 0; entry < N; ++entry) {
                        int inp;
                        scanf(" %d", &inp);
                        vec.push_back(inp);
                }

                SquareMatrix sqMat = SquareMatrix(N, mSize);
                int N_1 = mSize%N;
                vector<ullong> finalOut(N, 0);
                for(int entry = 0; entry < N; ++entry) {
                        sqMat.multiply(vec, finalOut);
                        print(finalOut, N_1);
                        printf("\n");
                        N_1 = (N_1 + 1) % N;
                        rotateBy1(vec);
                }
                if(test < nTests -1)
                        printf("\n");
        }
}

int main() {
        solveCircleSummation();
        return 0;
}
