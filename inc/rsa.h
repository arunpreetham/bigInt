#include <error_code.h>
#include <linked_list.h>

class RSA{
    list_node *p, *q, *n, *phi, *d, *e;
    public:
        RSA(list_node *p, list_node *q);
        int Encrypt(list_node *plain, list_node **cipher_text);
        int Decrypt(list_node *cipher, list_node **plain_text);
};

