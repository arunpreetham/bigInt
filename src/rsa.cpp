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
    cout <<endl<<"Initialized RSA with Params (p,q,n,phi):"<<endl;
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
            break; 
        }
        else{
            dupList(e, &temp_e);
            deleteList(&e);
            addList(temp_e,one,&e);
        }
    }
    cout <<"rsa:E found calculate D"<<endl;
    cout<<"rsa:E value is :";
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
    addList(k_times_phi, one, &k_times_phi_plus_1);
    allocMemForNode(&d);
    allocMemForNode(&dummy);

    divideList(k_times_phi_plus_1,e,&d,&dummy);
    
    cout << "rsa:D and E values are:"<<endl;
    cout <<"rsa:D ->";
    printListNumber(d);
    cout <<"rsa:E ->";
    printListNumber(e);
    this->p = p;
    this->q = q;
    this->n = n;
    this->phi = phi;
    this->d = d;
    this->e = e;
}

int RSA::Encrypt(list_node *plain, list_node **cipher_text){
    list_node *cipher;
    cipher = NULL;
    list_node *temp;
    temp = NULL;
    list_node *dummy;
    dummy = NULL;
    exp(plain,e,&temp);
    divideList(temp,n,&dummy,&cipher);
    *cipher_text = cipher;
    return ESUCCESS;

}

int RSA::Decrypt(list_node *cipher, list_node **plain_text)
{
    list_node *plain;
    plain = NULL;
    list_node *temp;
    temp = NULL;
    list_node *dummy;
    dummy = NULL;
    exp(cipher,d,&temp);
    divideList(temp,n,&dummy,&plain);
    *plain_text = plain;
    return ESUCCESS;
}