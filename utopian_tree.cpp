#include <iostream>

using namespace std;

int main() {
    int T;

    cin >> T;

    for(int i = 0; i < T; i++){
        int N, height = 1;

        cin >> N;

        for(int j = 0; j < N; j++){
            if(j % 2 == 0) height *= 2;
            else height++;
        }

        cout << height << endl;
    }

    return 0;
}
