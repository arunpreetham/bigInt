#include <blum_blum_shub.h>
#include <iostream>
#include <error_code.h>
#include <linked_list.h>
#include <list_math.h>

using namespace std;

BBS::BBS(list_node *p_local, list_node *q_local, list_node* seed_local)
{
    // p = 7 q = 11 seed = 33
    p = NULL;
    q = NULL;
    seed = NULL;
    m = NULL;
    current = NULL;
    dupList(p_local, &p);
    dupList(q_local, &q);
    dupList(seed_local, &seed);
    dupList(seed, &current);
    multiplyList(p,q, &m);
    cout <<"Initializing BBS Random Number Generator Using Params(p,q,seed,M):"<<endl;
    printListNumber(p);
    printListNumber(q);
    printListNumber(seed);
    printListNumber(m);
    
}
list_node * BBS::next_rand()
{
    list_node *r = NULL;
    list_node *q = NULL;
    list_node *sqr_i = NULL;
    list_node *current_copy = NULL;
    dupList(current, &current_copy);
    cout << __FILE__<<":"<< __func__<< ":::Next Random: \t"<<endl;
    multiplyList(current, current_copy , &sqr_i);
    cout << __FILE__<< __func__<< "Product:"<<endl;
    //printListNumber(sqr_i);
    //printListNumber(m);
    divideList(sqr_i, m, &q, &r);
    current = NULL;
    dupList(r, &current);    
    deleteList(&r);
    deleteList(&q);
    deleteList(&sqr_i);
    deleteList(&current_copy);

    return current; 
}
