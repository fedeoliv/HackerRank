#include <iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;
struct Node
{
	int data;
	Node *next;
};Node* RemoveDuplicates(Node *head)
{
  // This is a "method-only" submission.
  // You only need to complete this method.
    if(head == NULL || head->next == NULL)
        return head;
    Node *cur = head;
    while(cur->next != NULL)
    {
        Node *sec = cur->next;
        while(sec != NULL && sec->data == cur->data)
            sec = sec->next;
        if(sec != NULL)
        {
            Node *del = cur->next;
            while(del != sec)
            {
                Node *_next = del->next;
                delete del;
                del = _next;
            }
        }
        else if(sec == NULL)
        {
            Node *del = cur->next;
            while(del != NULL)
            {
                Node *_next = del->next;
                delete del;
                del = _next;
            }
        }
        cur->next = sec;
        cur = sec;
        if(cur == NULL)
            break;
    }
    return head;

}void Print(Node *head)
{
	bool ok = false;
	while(head != NULL)
	{
		if(ok)cout<<" ";
		else ok = true;
		cout<<head->data;
		head = head->next;
	}
	cout<<"\n";
}
Node* Insert(Node *head,int x)
{
   Node *temp = new Node();

   temp->data = x;
   temp->next = NULL;

   if(head == NULL) return temp;

   Node *temp1;

   for(temp1 = head;temp1->next!=NULL;temp1= temp1->next);
   temp1->next = temp;return head;
}

int main()
{
	int t;
	cin>>t;
	while(t-- >0)
	{
		Node *A = NULL;
		int m;cin>>m;
		while(m--){
			int x; cin>>x;
			A = Insert(A,x);}
		A = RemoveDuplicates(A);
		Print(A);
	}
}
