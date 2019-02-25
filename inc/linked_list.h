typedef struct list_node
{
    int data;
    list_node* next;
    list_node* prev;
}list_node;

int printList(list_node *head);
int printListRev(list_node *head);
int allocMemForNode(list_node **node);
int listLen(list_node *head);
int deleteNode(list_node **node);
int deleteList(list_node **head);
int addNode( list_node **head, list_node *data, int position );
int addNode( list_node **head, list_node *data, int position );
int removeNode( list_node **head, list_node **data, int position );
int removeNode( list_node **head, list_node **data, int position );
int addAtEnd( list_node **head, list_node *data );
int addAtStart( list_node **head, list_node *data );
int removeFromEnd( list_node **head, list_node **data );
int removeFromStart( list_node **head, list_node **data );
int ReverseList(list_node **head);
int dupList(list_node *source,list_node **copy);
list_node* findTail(list_node *head);
