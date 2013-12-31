// https://www.hackerrank.com/challenges/anagram

#include <iostream>
#include <string>
#include <map>

using namespace std;

int getChangesToAnagram(string s1, string s2) {
    int total, N1;
    int N2 = s2.size();
    map<char, int> charCount;

    total = N1 = s1.size();

    if (N1 != N2) return -1;

    for (int i = 0; i < N2; i++)
        charCount[s2[i]]++;

    for (int i = 0; i < N1; i++) {
        if (charCount[s1[i]] > 0) {
            total--;
            charCount[s1[i]]--;
        }
    }

    return total;
}

int main() {
    int N;
    cin >> N;

    for (int i = 0; i < N; i++) {
        string s;
        cin >> s;
        cout << getChangesToAnagram(s.substr(0, s.size() / 2), s.substr(s.size() / 2)) << endl;
    }
}
