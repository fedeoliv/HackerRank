#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
using namespace std;
struct Node
{
	int data;
	Node* next;
	Node* prev;
};/*
    Insert Node in a doubly sorted linked list
    After each insertion, the list should be sorted
   Node is defined as
   struct Node
   {
     int data;
     Node *next;
     Node *prev
   }
*/
Node* SortedInsert(Node *head,int data)
{
    Node *cur = new Node();

    cur->data = data;
    cur->next = cur->prev = NULL;

    if(head == NULL) return cur;

    Node *pos = head;

    while(pos != NULL && pos->data <= data)
        pos = pos->next;

    if(pos == NULL) {
        Node *tail = head;

        while(tail->next != NULL)
            tail = tail->next;

        tail->next = cur;
        cur->prev = tail;

        return head;
    }

    Node *pre = pos->prev;

    if(pre == NULL) {
        cur->next = head;
        head->prev = cur;

        return cur;
    }

    pre->next = cur;
    cur->prev = pre;
    cur->next = pos;
    pos->prev = cur;

    return head;
}void Print(Node *head) {
	if(head == NULL) return;
	while(head->next != NULL){ cout<<head->data<<" "; head = head->next;}
	cout<<head->data<<" ";
	while(head->prev != NULL) { cout<<head->data<<" "; head = head->prev; }
	cout<<head->data<<"\n";
}
int main()
{
	int t; cin>>t;
	Node *head = NULL;
	while(t--) {
	   int n; cin>>n;
           head = NULL;
	   for(int i = 0;i<n;i++) {
		   int x; cin>>x;
		   head = SortedInsert(head,x);
	       Print(head);
	   }
	}
}
