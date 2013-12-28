// https://www.hackerrank.com/challenges/print-the-elements-of-a-linked-list-in-reverse

/*
  Print elements of a linked list in reverse order as standard output
  head pointer could be NULL as well for empty list
  Node is defined as
  struct Node
  {
     int data;
     struct Node *next;
  }
*/
/*
  Print elements of a linked list in reverse order as standard output
  head pointer could be NULL as well for empty list
  Node is defined as
  struct Node
  {
     int data;
     struct Node *next;
  }
*/

#include <vector>
void ReversePrint(Node *head)
{
    vector<int> elements;

    while(head != NULL) {
        elements.push_back(head->data);
        head = head->next;
    }

    for(int i = elements.size() - 1;i >= 0;i--)
        cout << elements[i] << endl;
}
