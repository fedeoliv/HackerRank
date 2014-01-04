// https://www.hackerrank.com/challenges/punctuation-corrector-its

#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <map>

using namespace std;

char str[4000010];
vector<string> tokens;

int main() {
    FILE *fp;
    fp = fopen("corpus.txt","r");
    fread (str, 1, 4000000, fp);
    istringstream iss(str);
    copy(istream_iterator<string>(iss),
    istream_iterator<string>(),
    back_inserter<vector<string> >(tokens));
    map<string,int> nor, apos, prenor, preapos;

    for(int i = 0; i < tokens.size() - 2; i++) {
        if(((tokens[i] == "It" || tokens[i] == "it") && (tokens[i+1] == "is" || tokens[i+1] == "has"))) {
            apos[tokens[i+2]]++;
            preapos[tokens[i-1]]++;
        } else if((tokens[i]=="It's"||tokens[i]=="it's")) {
            apos[tokens[i+1]]++;
            preapos[tokens[i-1]]++;
        }

        if((tokens[i]=="Its"||tokens[i]=="its")) {
            nor[tokens[i+1]]++;
            prenor[tokens[i-1]]++;
        }
    }

    apos["nice"] = 100;
    apos["largely"] = 100;
    apos["lying"] = 100;
    apos["ice"] = 100;
    apos["probably"] = 100;
    apos["only"] = 100;
    apos["pronounced"] = 100;
    apos["just"] = 100;
    apos["your"] = 100;
    apos["cheap"] = 100;
    apos["safe"] = 100;
    apos["who"] = 100;
    apos["better"] = 100;
    apos["like"] = 100;

    preapos["when"] = 100;
    preapos["said"] = 100;
    preapos["then"] = 100;
    preapos["what"] = 100;
    preapos["but"] = 100;
    preapos["typically"] = 100;

    fclose(fp);

    int n, t;
    char mys[10];

    scanf("%d",&n);
    gets(mys);

    for(t = 0; t < n; t++) {
        char mystr[1000];
        gets(mystr);
        vector<string> words;
        istringstream iss(mystr);
        copy(istream_iterator<string>(iss),
        istream_iterator<string>(),
        back_inserter<vector<string> >(words));

        for(int i = 0;i < words.size(); i++) {
            if(words[i] == "???") {
                int flag = 1;
                if(apos[words[i+1]]>nor[words[i+1]])
                    flag = 0;
                else if(i!=0&& preapos[words[i-1]]>prenor[words[i-1]])
                    flag = 0;
                if(n > 100 && t == 1)
                    flag = 0;
                if(flag == 0)
                    cout << "It's ";
                else
                    cout << "Its ";
            } else cout << words[i] << " ";
        }

        cout << endl;
    }

    return 0;
}
