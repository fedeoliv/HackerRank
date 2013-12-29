#include <vector>
#include <iostream>
#include <map>
using namespace std;

struct indexs {
    int firstIndex, secondIndex;

    indexs()
    {
        firstIndex = -1;
        secondIndex = -1;
    }

    indexs(int f)
    {
        firstIndex = f;
        secondIndex = -1;
    }
};

int insertSort(vector<long> &sorted, int value)
{
    sorted.push_back(value);
    int j;
    for (j = sorted.size() - 2; j >= 0; -- j)
    {
        if (sorted[j] > value)
            sorted[j+1] = sorted[j];
        else
            break;
    }
    sorted[j+1] = value;
    return j+1;
}

int main() {
    int i, j, k, N;
    long long totalCount = 0;
    vector<long> num;
    vector<long> sorted;
    map<long, indexs> visited;

    cin >> N;
    num.assign(N, 0);

    vector<long> bigger(N);
    vector<long> smaller(N);

    for (i = 0; i < N; ++ i) {
        cin >> num[i];
        if (visited.find(num[i]) == visited.end()) {
            indexs in(i);
            visited[num[i]] = in;
            // insertSort
            smaller[i] = insertSort(sorted, num[i]); // j+1 elements are smaller than num[i]

        } else {
            visited[num[i]].secondIndex = i;
            smaller[i] = lower_bound(sorted.begin(), sorted.end(), num[i]) - sorted.begin();
        }
    }
    sorted.clear();
    for (i = N-1; i >= 0; -- i)
    {
        int sec = visited[num[i]].secondIndex;
        if (sec == i || sec == -1) {
            int t = insertSort(sorted, num[i]);
            bigger[i] = sorted.size() - t - 1;
        } else {
            bigger[i] = sorted.size() - 1 - (lower_bound(sorted.begin(), sorted.end(), num[i]) - sorted.begin());
        }
    }
    map<long, indexs>::iterator it = visited.begin();
    while (it != visited.end())
    {
        indexs in = it->second;
        if (in.secondIndex == -1)
            totalCount += smaller[in.firstIndex] * bigger[in.firstIndex];
        else {
            totalCount += smaller[in.firstIndex] * bigger[in.firstIndex];
            totalCount += (smaller[in.secondIndex]-smaller[in.firstIndex])*bigger[in.secondIndex];
        }
        ++ it;
    }
    cout << totalCount << endl;
    return 0;
}
