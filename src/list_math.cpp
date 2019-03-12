#include <iostream>
#include <conio.h>
#include <error_code.h>
#include <linked_list.h>
#include <fstream>

using namespace std;
//Utility
int dummy_node_count(list_node *head)
{
    int count = 0;
    while(head!=NULL)
    {
        if(head->data < 1)
        {
            count++;
            head = head->next;
        }
        else 
            return count;
    }
    return count;
}

int compareIntList(list_node *operand1, list_node *operand2)
{
    int list_len1 = 0, list_len2 = 0, null_node1 = 0,null_node2 = 0;
    list_node *temp1 = operand1, *temp2 = operand2;
    cout<<__func__ <<":enter"<<endl;
    //Last node is the 10^n value so if the lists are of equal length then compare the last node.
    //error case
    if(NULL == operand1 || NULL == operand2)
    {
        cout<<__func__ <<"Null Parameters"<<endl;
        return 0;
    }
    list_len1 = listLen(temp1);
    list_len2 = listLen(temp2);

    //We need to remove the last zeros.
    cout<<__func__ <<"list_len1:"<<list_len1<<" list_len2:"<<list_len2<<endl;

    printList(operand1);
    printList(operand2);

    if(list_len1 == list_len2)
    {
        while(operand1 != NULL && operand1->data == operand2->data)
        {
            operand1 = operand1->next;
            operand2 = operand2->next;
        }
        if(operand1->data > operand2->data)
        {
            return 1;
        }    
        else
        {
            return 2;
        }
    }
    else if(list_len1>list_len2)
    {
        return 1;
    }
    else
    {
        return 2;
    }
    cout<<__func__ <<":exit"<<endl;    
    return 0;
}

int findBigSmall(list_node **Big, list_node **Small,list_node *operand1, list_node *operand2 )
{
    int compare_op = compareIntList(operand1,operand2);
    cout<<__func__ <<"Compare_op"<<compare_op<<endl;
    //First we need to find the largest number and then sub it with the smallest. 
    if(1 == compare_op)
    {
        *Big = operand1;
        *Small = operand2;
    }
    else if(2 == compare_op)
    {
        *Big = operand2;
        *Small = operand1;
    }
    else
    {
        return EBADPARAM;
    }
    return ESUCCESS;
}

int addList(list_node *operand1, list_node *operand2, list_node **result)
{
    list_node temp,*sum;
    int carry = 0;
    operand1 = findTail(operand1);
    operand2 = findTail(operand2);
    //Add both the operands.
    while(NULL != operand1 && NULL != operand2)
    {
        temp.data = operand1->data + operand2->data + carry;
        cout<<"temp.data:"<<temp.data<<"\n";
        carry = (temp.data)/10;
        temp.data = (temp.data)%10;
        cout<<"carry:"<<carry<<"\n";

        allocMemForNode(&sum);
        sum->data = temp.data;
        addAtStart(result,sum);
        cout<<"sum:"<<sum->data<<"\n";

        operand1 = operand1->prev;
        operand2 = operand2->prev;
    }

    //Now its possible that atleast one is big. 
    if(NULL != operand1)
    {
        temp.data = operand1->data + carry;
        carry = 0;
        allocMemForNode(&sum);
        sum->data = temp.data;
        operand1 = operand1->prev;
        addAtStart(result,sum);
    }
    else if(NULL != operand2)
    {
        temp.data = operand2->data + carry;
        carry = 0;
        allocMemForNode(&sum);
        sum->data = temp.data;
        addAtStart(result,sum);    
        operand2 = operand2->prev;    
    }
    printList(*result);
    //New node is required.
    if(0!=carry)
    {
        allocMemForNode(&sum);
        sum->data = carry;
        addAtStart(result,sum);
    }
    printList(*result);

    return ESUCCESS;
}


int subList(list_node *operand1, list_node *operand2, list_node **result)
{
    list_node *Big = NULL, *Small = NULL;
    
    if(ESUCCESS != findBigSmall(&Big, &Small,operand1,operand2))
    {
        cout<<__func__ <<"findBigSmall failed!"<<endl;
        return EFAILED;
    }

    //  start using rev of the list
    Big = findTail(Big);
    Small = findTail(Small);

    //Now we need to do Big - small
    int borrow = 0;
    list_node temp,*sub;

    //Sub both the operands.
    while(NULL != Big && NULL != Small)
    {
        if(Big->data < (Small->data + borrow))
        {
            temp.data = 10 + Big->data - Small->data - borrow;
            borrow = 1;
        }
        else
        {
            temp.data = Big->data - Small->data - borrow;
            borrow = 0;
        }

        allocMemForNode(&sub);
        sub->data = temp.data;
        addAtStart(result,sub);
        
        Big = Big->prev;
        Small = Small->prev;
    }
    cout<<__func__ <<"Iter1 done"<<endl;
    //Now its possible that Big has more digits. 
    while(NULL != Big)
    {
        if(Big->data < borrow)
        {
            temp.data = 10 + Big->data - borrow;
            borrow = 1;
        }
        else
        {
            temp.data = Big->data - borrow;
            borrow = 0;
        }

        allocMemForNode(&sub);
        sub->data = temp.data;
        Big = Big->prev;
        addAtStart(result,sub);
    }
    cout<<__func__ <<"Before Print"<<endl;
    stripFromStart(result);
    printList(*result);

    return ESUCCESS;
}

int multiplyList(list_node *operand1, list_node *operand2, list_node **result)
{
    list_node *Big = NULL, *Small = NULL, temp, *Big_temp = NULL, *sum = NULL, *sum_temp = NULL;
    int carry = 0,small_index = 0,res_len = 0,idx = 0;

    if(ESUCCESS != findBigSmall(&Big, &Small,operand1,operand2))
    {
        cout<<__func__ <<"findBigSmall failed!"<<endl;
        return EFAILED;
    }

    Big = findTail(Big);
    Small = findTail(Small);

    res_len = listLenRev(Big) + listLenRev(Small);
    cout<<__func__ <<"Resule_len="<<res_len<<endl;

    Big_temp = Big;
    while(res_len>0)
    {
        allocMemForNode(&sum);
        addAtStart(result,sum);
        res_len--;
    }

    sum = findTail(*result);
    //create result of len Big + Small
    while(NULL != Small)
    {
        idx = 0;
        carry = 0;
        while(idx < small_index)
        {
            idx++;
            sum = sum->prev;
        }
        while(NULL != Big)
        {
            temp.data = (Small->data * Big->data) + carry;

            sum->data = sum->data + temp.data;
            
            carry = (sum->data)/10;
            sum->data = (sum->data)%10;

            sum = sum->prev;
            Big = Big->prev;
        }
        cout<<"carry="<<carry<<"sum->data:"<<sum->data<<endl;
        while(carry>0)
        {
            sum->data = sum->data + carry;

            carry = (sum->data)/10;
            sum->data = (sum->data)%10;

            sum = sum->prev;
        }
        cout<<__func__ <<"Before Print"<<endl;
        printList(*result);
        Small = Small->prev;
        Big = Big_temp;    
        sum = findTail(*result);;
        small_index++;
    }

    //We need to add at the next place.
    cout<<__func__ <<"Before Print"<<endl;
    stripFromStart(result);
    printList(*result);
    return ESUCCESS;
}

int divideList(list_node *operand1c, list_node *operand2c, list_node **quotient, list_node **reminder)
{
    int compare_op = 0;
    list_node *sum = NULL,*result_temp = NULL, *temp_result = NULL, *temp_operand1 = NULL,*operand1 =NULL, *operand2 = NULL;
    cout<<__func__<<":Entry"<<endl;
    allocMemForNode(&sum);
    sum->data = 0;
    addAtStart(quotient,sum);
    dupList(operand1c, &operand1);
    dupList(operand2c, &operand2);

    list_node *temp_1;
    allocMemForNode(&temp_1);
    temp_1->data = 1;

    while(1 == compareIntList(operand1,operand2))
    {
        cout<<"compare_loop_enter"<<endl;
        temp_operand1 = NULL;
        subList(operand1,operand2,&temp_operand1);
        deleteList(&operand1);
        operand1 = temp_operand1;

        cout<<"Operand1:"<<endl;
        printList(operand1);
        
        //cout<<"Quotient:"<<endl;
        //printList(*quotient);
        temp_result = NULL;
        addList(*quotient,temp_1,&temp_result);
        
        cout<<"Temp1:"<<endl;
        printList(temp_1);

        deleteList(quotient);
        *quotient = temp_result;

        cout<<"Quotient:"<<endl;
        printList(*quotient);

        cout<<"compare_loop_exit"<<endl;
    }
    dupList(operand1, reminder);
    cout<<"Operand1:"<<endl;
    printList(operand1);
    return ESUCCESS;
}