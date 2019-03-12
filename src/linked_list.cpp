#include <iostream>
#include <conio.h>
#include <error_code.h>
#include <linked_list.h>

using namespace std;
#define NULL 0x0
int printList(list_node *head)
{
    while( NULL != head)
    {
        cout<<head->data<<"->";
        head = head->next;
    }
    cout<<"NULL"<<endl;
    return ESUCCESS;
}

int printListRev(list_node *head)
{
    list_node *prev = NULL;
    while( NULL != head )
    {
        //find the last node.
        prev = head;
        head = head->next;
    }
    
    while( NULL != prev )
    {
        cout<<prev->data<<"->";
        prev = prev->prev;
    }

    cout<<"NULL"<<endl;
    return ESUCCESS;
}

list_node* findTail(list_node *head)
{
    list_node *temp = NULL;
    while(head!=NULL)
    {
        temp = head;
        head = head->next;
    }
    return temp;
}

int allocMemForNode(list_node **node)
{

    *node = (list_node*) malloc(sizeof(list_node));
    if(NULL == *node)
    {
        cout<<__func__ << " :Mem Alloc Failed "<<endl; 
        return EMEM_ALLOC_FAILED;
    }
    (*node)->next = NULL; 
    (*node)->prev = NULL; 
    (*node)->data = 0;
    cout<<__func__ << " :MemAlloc success! "<<endl; 
    return ESUCCESS; 
}

int listLen(list_node *head)
{
    int list_len = 1;
    if(NULL == head)
        return 0;
    while(head->next != NULL )
    {
        list_len++;
        head = head->next;
    }
    return list_len;
}

int listLenRev(list_node *tail)
{
    int list_len = 1;
    if(NULL == tail)
        return 0;
    while(tail->prev != NULL )
    {
        list_len++;
        tail = tail->prev;
    }
    return list_len;
}

int stripFromStart(list_node **head)
{
    list_node *temp = NULL;
    while((*head)!=NULL)
    {
        if((*head)->data == 0)
        {
            removeFromStart(head, &temp);
        }
        else 
            return ESUCCESS;
    }
    return ESUCCESS;
}

int deleteNode(list_node **node)
{
    (*node)->prev = NULL;
    (*node)->next = NULL;
    free(*node);
    (*node) = NULL;
    return ESUCCESS;
}

int deleteList(list_node **head)
{
    list_node *temp;
    while((*head)!= NULL)
    {
        temp = (*head)->next;
        deleteNode(head);
        (*head) = temp;
    }
    (*head) = NULL;
    return ESUCCESS;
}

int addNode( list_node **head, list_node *data, int position )
{
    //first node to be added
    if(NULL == *head)
    {
        if(position != 0) //postion must be 0.
        {
            cout<<__func__ << " position != 0 "<<endl; 
            return EBADPARAM;
        }
        *head = data;
        data->next = NULL;
        data->prev = NULL;
        cout<<__func__ << " Added at pos 0 "<<endl; 
        return ESUCCESS;
    }
    
    list_node *temp = *head;
    int32_t t_pos = 0;

    while(temp->next != NULL && t_pos != position)
    {
        t_pos++;
        temp = temp->next;
    }

    data->next = temp;
    data->prev = temp->prev;
    if(NULL != temp->prev)
    {
        temp->prev->next = data;
    }
    else
    {
        *head = data;
    }
    temp->prev = data;

    cout<<__func__ << " Added at pos "<<position<<endl; 

    return ESUCCESS;
}

int removeNode( list_node **head, list_node **data, int position )
{
    //first node, should have atleast one. 
    if(NULL == *head)
    {
        cout<<__func__ << " Head NULL "<<endl; 
        return EBADPARAM;
    }
    
    list_node *temp = *head;
    int32_t t_pos = 0;

    while(temp->next != NULL && t_pos<position)
    {
        t_pos++;
        if(t_pos == position)
            break;
        temp = temp->next;
    }
    //list length is less than position
    if(temp->next == NULL && t_pos < position)
    {
        cout<<__func__ << " List length is less than position! "<<endl; 
        return EBADPARAM;
    }
    *data = temp;
    temp = temp->next;

    *data = temp;
    
    if(NULL != temp->prev)
    {
        temp->prev->next = temp->next;
    }
    else
    {
        //First node to be deleted.
        *head = temp->next;
    }

    if(NULL != temp->next)
    {
        temp->next->prev = temp->prev;
        //if this is the head node then prev will be null.
    }

    cout<<__func__ << " Removed from pos "<<position<<endl; 
    
    return ESUCCESS;
}

int addAtEnd( list_node **head, list_node *data )
{
    cout<<__func__ << " enter "<<endl; 
    //first node to be added
    if(NULL == *head)
    {
        *head = data;
        data->prev = NULL;
        data->next = NULL;
        cout<<__func__ << " First node added "<<endl; 
        return ESUCCESS;
    }
    
    list_node *temp = *head;

    while(temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = data;
    data->prev = temp;
    data->next = NULL;

    cout<<__func__ << " Added at the end! "<<endl; 
    return ESUCCESS;
}

int addAtStart( list_node **head, list_node *data )
{
    //first node to be added
    data->next = *head;
    data->prev = NULL;

    if(NULL != (*head))
        (*head)->prev = data;
    //else its the first node to be added.

    *head = data;
    cout<<__func__ << " Added at start! "<<endl; 
    return ESUCCESS;
}

int removeFromEnd( list_node **head, list_node **data )
{
    if(*head == NULL)
    {
        cout<<__func__ << " Remove failed! Null Head "<<endl;
        return EBADPARAM; 
    }
    list_node *temp = *head;

    while(temp->next != NULL)
    {
        temp = temp->next;
    }

    *data = temp;
    if(NULL != temp->prev)
    {
        temp->prev->next = NULL;
    }
    else
    {
        //There is only one node update head to NULL. 
        *head = NULL;
    }
    
    cout<<__func__ << " Removed from end "<<endl; 
    return ESUCCESS;
}

int removeFromStart( list_node **head, list_node **data )
{
    if((*head) == NULL)
    {
        cout<<__func__ << " Remove failed! Null Head"<<endl;
        return EBADPARAM; 
    }

    *data = *head;
    *head = (*head)->next;
    (*head)->prev = NULL;
    cout<<__func__ << " Removed at start "<<endl; 
    return ESUCCESS;
}

int ReverseList(list_node **head)
{
    list_node *temp = NULL,*curr = NULL;
    if(*head == NULL)
        return EBADPARAM;

    curr = *head;
    while(NULL != curr)
    {
        //curr->next->prev
        temp = curr->prev; 
        curr->prev = curr->next;
        curr->next = temp;
        curr = curr->prev;
    }
    if(temp != NULL)
    {
        *head = temp->prev;
    }
    return ESUCCESS;
}

int dupList(list_node *source,list_node **copy)
{
    list_node *temp = NULL,*head = NULL;
    bool is_first = true;
    cout<<"duplist enter"<<endl;
    if(NULL == source)
    {
        return EBADPARAM;
    }

    while(NULL != source)
    {
        allocMemForNode(&temp);
        temp->data = source->data;
        addAtEnd(&head, temp);
        source = source->next;
        if(is_first)
        {
            *copy = head;
            is_first = false;
        }
    }
    cout<<"duplist exit"<<endl;  
    return ESUCCESS;  
}