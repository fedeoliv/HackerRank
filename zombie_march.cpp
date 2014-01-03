// https://www.hackerrank.com/challenges/zombie-march

#include <iostream>
#include <map>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

#define zero(n) memset(n,0,sizeof(n))

class point {
    public :
    int y;
    double value;

    point(int a, double b) {
        y = a;
        value = b;
    }
};

static int near(double a) {
    if(a - (int) a > 0.5)
        return (int) a + 1;

    return (int) a;
};

static bool canfinish(double *a1, double *a2, int n) {
    for(int i = 0; i <= n-1; i++)
        if(near(a1[i]) != near(a2[i]))
            return false;

    return true;
};

bool get_sort( const int &v1, const int &v2) {
    return v1 > v2;
}

bool solve() {
    int iCase;

    cin >> iCase;

    for(; iCase > 0; iCase--) {
        int n, m, k;

        cin >> n >> m >> k;

        map<int,vector<point>* > graph;
        vector<point> *v;
        map<int,vector<point>* >::iterator mIter;

        int nums[n];
        zero(nums);

        for(int i = 0 ;i < m ; i++) {
            int x;
            int y;

            cin >> x >> y;

            nums[x]++;
            nums[y]++;
            point p1(x , 1);
            point p2(y , 1);

            mIter = graph.find(y);

            if(graph.end() == mIter) {
                v = new vector<point>;
                graph.insert(pair<int , vector<point>* >(y,v));
            } else
                v = mIter->second;

            v->push_back(p1);
            mIter = graph.find(x);

            if(graph.end() == mIter) {
                v = new vector<point>;
                graph.insert(pair<int , vector<point>* >(x,v));
            } else
                v = mIter->second;

            v->push_back(p2);
        }

        for(mIter = graph.begin() ; mIter != graph.end() ; mIter++) {
            v = mIter->second;

            for(int i = 0; i < v->size() ; i++) {
                point *p = &(*v)[i];
                p->value /= nums[p->y];
            }
        }

        double arry1[n];
        double arry2[n];
        zero(arry1);
        zero(arry2);

        double * newarray;
        double * old;
        newarray = arry1;
        old = arry2;

        for(int i = 0 ; i < n ; i++)
            in >> old[i];

        for(int i = 0;i <= k-1; i++) {
            for(int j = 0;j <= n-1; j++) {
                double t = 0;
                vector<point> *v;
                mIter = graph.find(j);

                if(graph.end() == mIter) {
                    newarray[j] = 0;
                    continue;
                } else
                    v = mIter->second;

                for(int i = 0; i < v->size(); i++) {
                    point *p = &(*v)[i];
                    t += p->value * old[p->y];
                }

                newarray[j]=t;
            }

            if(canfinish(newarray, old, n)) break;
            swap(newarray,old);
        }

        vector<int> vInt;

        for(int i = 0; i< n ;i++)
            vInt.push_back(near(old[i]));

        sort(vInt.begin(),vInt.end(), get_sort);

        for(int i = 0 ; i < 5 ; i++)
            cout << vInt[i] <<" ";

        cout << endl;
    }

    return true;
}

int main() {
    solve();

    return 0;
}
