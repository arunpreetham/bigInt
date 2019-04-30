#include <blum_blum_shub.h>
#include <iostream>
#include <error_code.h>
#include <linked_list.h>
#include <list_math.h>
#include <rsa.h>
using namespace std;

RSA::RSA(list_node *p_local, list_node *q_local)
{
    // p = 7 q = 11 seed = 33
    p = NULL;
    q = NULL;
    n = NULL;
    phi = NULL;
    d = NULL;
    e = NULL;
    list_node *p_minus_1 = NULL;
    list_node *q_minus_1 = NULL;

    dupList(p_local, &p);
    dupList(q_local, &q);
    list_node *one;
    one = listFromString("1");
    allocMemForNode(&n);
    allocMemForNode(&phi);

    //Calculate N

    multiplyList(p_local,q_local, &n);
    
    // Calculate Phi
    subList(p,one, &p_minus_1);
    subList(q,one, &q_minus_1);
    multiplyList(p_minus_1, q_minus_1, &phi);
    cout <<"Initialized RSA with Params (p,q,n,phi):";
    printListNumber(p);
    printListNumber(q);
    printListNumber(n);
    printListNumber(phi);

    list_node * e, *d;
    e = listFromString("2");
    list_node *temp;
    list_node *temp_e;
    while(compareIntList(e, phi)==-1) 
    {
        temp = NULL;
        gcd(e, phi, &temp);
        if (compareIntList(temp, one)==0)
        {
            cout<<"Co prime found"<<endl; 
            break; 
        }
        else{
            cout<<"Checking once again"<<endl;
            dupList(e, &temp_e);
            deleteList(&e);
            addList(temp_e,one,&e);
            cout<<"Current E:";
            printListNumber(e);
        }
    }
    cout <<"E found calculate D"<<endl;
    cout<<"E value is :";
    printListNumber(e);
    list_node *k;
    list_node *k_times_phi;
    list_node *k_times_phi_plus_1;
    list_node *dummy;
    k = NULL;
    k_times_phi = NULL;
    k_times_phi_plus_1 = NULL;
    dummy = NULL;
    k = listFromString("2");  // A constant value 
    multiplyList(k, phi, &k_times_phi);
    cout <<"Computed ktimesphi";
    printListNumber(k_times_phi);
    addList(k_times_phi, one, &k_times_phi_plus_1);
    cout <<"Computed ktimesphiplusone";
    
    printListNumber(k_times_phi_plus_1);    
    
    cout<<"hereiam"<<endl;
    allocMemForNode(&d);
    allocMemForNode(&dummy);

    divideList(k_times_phi_plus_1,e,&d,&dummy);
    
    cout << "D and E values are:"<<endl;
    printListNumber(d);
    printListNumber(e);
    //https://www.geeksforgeeks.org/rsa-algorithm-cryptography/
}

list_node * RSA::Encrypt(list_node *plain){
    
}
//list_node * RSA::Decrypt(list_node *cipher)