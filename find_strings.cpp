// https://www.hackerrank.com/challenges/find-strings

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

class SuffixAutomaton {
  public:
    SuffixAutomaton() {
        root_ = new Node(0);
        Nodes.resize(1);
        Nodes[0].push_back(root_);
    }

    void add(const string& data) {
        if (data.size() + 1 > Nodes.size())
            Nodes.resize(data.size() + 1);

        this->data.push_back(data);
    }

    void build() {
        vector<Node*> now(data.size(), root_);

        for (int i = 0; i < int(Nodes.size()) - 1; ++i) {
            for (int j = 0; j < int(data.size()); ++j) {
                if (i >= int(data[j].size())) continue;
                now[j] = extend(now[j], i + 1, data[j][i] - 'a');
            }
        }
    }

    void prepare() {
        for (int i = int(Nodes.size()) - 1; i >= 0; --i)
            for (vector<Node*>::iterator it = Nodes[i].begin(); it != Nodes[i].end(); ++it) {
                Node *p = *it;

                for (int j = 0; j < 26; ++j)
                    if (p->next[j])
                        p->total += p->next[j]->total;

                p->total += 1;
            }
    }

    string kthSubstring(int which) {
        which++;

        if (which > root_->total)
            return "INVALID";
        Node *k = root_;

        string answer = "";

        while (which > 1) {
            --which;
            for (int i = 0; i < 26; ++i)
                if (k->next[i]) {
                    if (k->next[i]->total < which)
                        which -= k->next[i]->total;
                    else {
                        k = k->next[i];
                        answer += i + 'a';
                        break;
                    }
                }
        }

        return answer;
    }

  private:
    class Node {
      public:
        Node(const int &_length, Node * const _link = 0, Node** const _next = 0):
                length(_length),
                link(_link),
                total(0) {
            if (not _next)
                memset(next, 0, sizeof(next));
            else
                memcpy(next, _next, sizeof(next));
        }

        int length;
        Node *link;
        Node *next[26];

        int total;
    };

    Node* extend(Node* const last_node, int length, int edge) {
        if (last_node->next[edge])
            return last_node->next[edge];

        Node *now = new Node(length);
        Nodes[now->length].push_back(now);

        Node *k;

        for (k = last_node; k and not k->next[edge]; k = k->link)
            k->next[edge] = now;

        if (k == 0) {
            now -> link = root_;
            return now;
        }

        Node *p = k -> next[edge];

        if (k -> length + 1 == p -> length) {
            now -> link = p;
            return now;
        }

        Node *clone = new Node(k -> length + 1, p -> link, p -> next);
        Nodes[clone->length].push_back(clone);

        p -> link = now -> link = clone;

        for (; k and k->next[edge] == p; k = k->link)
            k->next[edge] = clone;

        return now;
    }

    Node *root_;

    vector< vector<Node*> > Nodes;
    vector<string> data;
};


int main() {
    int N; cin >> N;

    SuffixAutomaton A;

    for (int i = 0; i < N; ++i) {
        string S; cin >> S;
        A.add(S);
    }

    A.build();

    A.prepare();

    int Q; cin >> Q;

    for (int i = 0; i < Q; ++i) {
        int K; cin >> K;
        cout << A.kthSubstring(K) << endl;
    }
}
