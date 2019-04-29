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
    phi = NULL;
    d = NULL;
    e = NULL;
    dupList(p_local, &p);
    dupList(q_local, &q);
    allocMemForNode(&phi);
    multiplyList(p_local,q_local, &phi);
    cout <<"Initialized RSA with Params (p,q,phi):"<<endl;
    printListNumber(p);
    printListNumber(q);
    printListNumber(phi);
}