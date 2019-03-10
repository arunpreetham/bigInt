#include <error_code.h>
#include <linked_list.h>

class BBS{
    list_node *p, *q, *m, *seed, *current;
    public:
        BBS(list_node *p, list_node *q, list_node*seed);
        list_node * next_rand();
};

