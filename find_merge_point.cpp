#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
using namespace std;
struct Node
{
	int data;
	Node* next;
};/*
   Find merge point of two linked lists
   Node is defined as
   struct Node
   {
       int data;
       Node* next;
   }
*/
#include <stack>

int FindMergeNode(Node *headA, Node *headB)
{
    stack<Node *> sta, stb;

    if(headA == NULL || headB == NULL) return 0;

    Node *cur = headA;

    while(cur != NULL) {
        sta.push(cur);
        cur = cur->next;
    }

    cur = headB;

    while(cur != NULL) {
        stb.push(cur);
        cur = cur->next;
    }

    int node = 0;

    while(!sta.empty() && !stb.empty()) {
        Node *pa = sta.top();
        Node *pb = stb.top();

        sta.pop();
        stb.pop();

        if(pa->data != pb->data) break;
        else node = pa->data;
    }

    return node;
}int main()
{
	Node *A, *B, *C, *D,*E,*F,*G;
	A = new Node();	B= new Node();  C= new Node(); D = new Node(); E = new Node(); F= new Node();G = new Node();
	A->data = 2; B->data = 4; C->data = 3; D->data = 5; E->data = 7; F->data = 6;G->data = 11;

	// case 1 =
	A->next = B; B->next = C; C->next = D; D->next = E; E->next = NULL;
	F->next = G; G->next = C;
	cout<<FindMergeNode(A,F)<<"\n";
	//case 2.
	A->next = B; B->next = C; C->next = E;  E->next = NULL;
	F->next = G; G->next = D;D->next = C;
	cout<<FindMergeNode(A,F)<<"\n";
	//case 3:
	A->next = B; B->next = E; E->next = NULL;
	F->next = G; G->next = D;D->next = C; C->next = E;
	cout<<FindMergeNode(A,F)<<"\n";
}
