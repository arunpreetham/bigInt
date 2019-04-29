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

    cout <<"Initialized RSA with Params (p,q,n,phi):"<<endl;
    printListNumber(p);
    printListNumber(q);
    printListNumber(n);
    printListNumber(phi);

    list_node * e;
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
            cout<<"Current E"<<endl;
            printListNumber(e);
        }
    }
    /*
   // First part of public key: 
    double n = p*q; 
  
    // Finding other part of public key. 
    // e stands for encrypt 
    double e = 2; 
    double phi = (p-1)*(q-1); 
    while (e < phi) 
    { 
        // e must be co-prime to phi and 
        // smaller than phi. 
        if (gcd(e, phi)==1) 
            break; 
        else
            e++; 
    } 
  
    // Private key (d stands for decrypt) 
    // choosing d such that it satisfies 
    // d*e = 1 + k * totient 
    int k = 2;  // A constant value 
    double d = (1 + (k*phi))/e; 
        */
}