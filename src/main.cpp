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
    list_node *addend1 = NULL,*addend2 = NULL,*result = NULL;

    //Open input file 1 and store it in operand1
    cout<<"Input file1:"<<endl;
    fin.open("input1.txt", ios::in);

	while (fin.get(digit_c)) {
        cout<<convert_ascii_to_digit(digit_c);
        list_node *t_data = NULL;
        allocMemForNode(&t_data);
        t_data->data = convert_ascii_to_digit(digit_c);
        addAtStart(&addend1,t_data);
	}
    fin.close();
    printList(addend1);

    //Open input file 2 and store it in operand2
    cout<<"Input file2:"<<endl;
    fin.open("input2.txt", ios::in);

	while (fin.get(digit_c)) {
        cout<<convert_ascii_to_digit(digit_c);
        list_node *t_data = NULL;
        allocMemForNode(&t_data);
        t_data->data = convert_ascii_to_digit(digit_c);
        addAtStart(&addend2,t_data);
	}
    fin.close();
    printList(addend2);

    //Result file
    cout<<"Result file:"<<endl;
    fout.open("result.txt", ios::out);
    fout<<"Input 1: "<<endl;
    {
        list_node *temp = addend1;
        while( NULL != temp)
        {
            fout<<temp->data;
            temp = temp->next;
        }
        fout<<endl;
    }
    fout<<"Input 2: "<<endl;
    {
        list_node *temp = addend2;
        while( NULL != temp)
        {
            fout<<temp->data;
            temp = temp->next;
        }
        fout<<endl;
    }
    //Addition
    addList(addend1,addend2, &result);
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

    printList(addend1);
    printList(addend2);
    //Substract
    subList(addend1,addend2, &result);
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
    multiplyList(addend1,addend2, &result);
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
    divideList(addend1,addend2, &quotient, &reminder);
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
    deleteList(&addend1);
    deleteList(&addend2);

    getch();
    return ESUCCESS;
}