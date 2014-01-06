#include <iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;
struct Node
{
	int data;
	Node *next;
};int CompareLists(Node *headA, Node* headB)
{
    bool end = true;
    int countA = 0, countB = 0;
    Node *temp = headB;

    while(temp != NULL) {
        countB++;
        temp = temp->next;
    }

    while(headA != NULL) {
        countA++;

        if(headA->data == headB->data) {
            headA = headA->next;
            headB = headB->next;
        } else {
            end = false;
            break;
        }
    }

    if(end && countA == countB)
        return 1;
    else
        return 0;
}Node* Insert(Node *head,int x)
{
   Node *temp = new Node();
   temp->data = x;
   temp->next = NULL;
   if(head == NULL)
   {
       return temp;
   }
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
		Node *B = NULL;
		int m;cin>>m;
		while(m--){
			int x; cin>>x;
			A = Insert(A,x);}
		int n; cin>>n;
        while(n--){
			int y;cin>>y;
			B = Insert(B,y);
		}
		cout<<CompareLists(A,B)<<"\n";
	}
}
