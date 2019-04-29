#include <error_code.h>
#include <linked_list.h>

class RSA{
    list_node *p, *q, *phi, *d, *e;
    public:
        RSA(list_node *p, list_node *q);
        list_node * Encrypt(list_node *plain);
        list_node * Decrypt(list_node *cipher);
};

