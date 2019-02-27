#include <iostream>
#include <conio.h>
#include <error_code.h>
#include <linked_list.h>
#include <list_math.h>
#include <fstream>

using namespace std;

int convert_ascii_to_digit(char digit)
{
    return (int)(digit - 48);
}

int main()
{
    std::ifstream fin;
    std::ofstream fout;
    char digit_c;
    list_node *input1 = NULL,*input2 = NULL,*result = NULL;

    //Open input file 1 and store it in operand1
    cout<<"Input file1:"<<endl;
    fin.open("input1.txt", ios::in);

	while (fin.get(digit_c)) {
        cout<<convert_ascii_to_digit(digit_c);
        list_node *t_data = NULL;
        allocMemForNode(&t_data);
        t_data->data = convert_ascii_to_digit(digit_c);
        addAtStart(&input1,t_data);
	}
    fin.close();
    printList(input1);

    //Open input file 2 and store it in operand2
    cout<<"Input file2:"<<endl;
    fin.open("input2.txt", ios::in);

	while (fin.get(digit_c)) {
        cout<<convert_ascii_to_digit(digit_c);
        list_node *t_data = NULL;
        allocMemForNode(&t_data);
        t_data->data = convert_ascii_to_digit(digit_c);
        addAtStart(&input2,t_data);
	}
    fin.close();
    printList(input2);

    //Result file
    cout<<"Result file:"<<endl;
    fout.open("result.txt", ios::out);
    fout<<"Input 1: "<<endl;
    {
        list_node *temp = input1, *temp1 = NULL;
        while(NULL != temp)
        {
            temp1 = temp;
            temp = temp->next;
        }
        while(NULL != temp1)
        {
            fout<<temp1->data;
            temp1 = temp1->prev;
        }
        fout<<endl;
    }
    fout<<"Input 2: "<<endl;
    {
        list_node *temp = input2, *temp1 = NULL;
        while(NULL != temp)
        {
            temp1 = temp;
            temp = temp->next;
        }
        while(NULL != temp1)
        {
            fout<<temp1->data;
            temp1 = temp1->prev;
        }
        fout<<endl;
    }
    //Addition
    addList(input1,input2, &result);
    fout<<"Addition Result: "<<endl;
    {
        list_node *temp = result;
        while( NULL != temp)
        {
            fout<<temp->data;
            temp = temp->next;
        }
        fout<<endl;
    }
    deleteList(&result);

    printList(input1);
    printList(input2);
    //Substract
    subList(input1,input2, &result);
    fout<<"Substract Result: "<<endl;
    {
        list_node *temp = result;
        while( NULL != temp)
        {
            fout<<temp->data;
            temp = temp->next;
        }
        fout<<endl;
    }
    deleteList(&result);

    //multiplyList
    multiplyList(input1,input2, &result);
    fout<<"multiplyList Result: "<<endl;
    {
        list_node *temp = result;
        while( NULL != temp)
        {
            fout<<temp->data;
            temp = temp->next;
        }
        fout<<endl;
    }
    deleteList(&result);

    //Divid List
    list_node *quotient = NULL, *reminder = NULL;
    divideList(input1,input2, &quotient, &reminder);
    fout<<"Divide Result Quotient: "<<endl;
    {
        list_node *temp = quotient;
        while(NULL != temp)
        {
            fout<<temp->data;
            temp = temp->next;
        }
        fout<<endl<<"Reminder:";

        temp = reminder;
        while(NULL != temp)
        {
            fout<<temp->data;
            temp = temp->next;
        }
        fout<<endl;
    }
    deleteList(&quotient);
    deleteList(&reminder);

    fout.close();
    deleteList(&input1);
    deleteList(&input2);

    getch();
    return ESUCCESS;
}