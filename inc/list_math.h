int addList(list_node *operand1, list_node *operand2, list_node **result);

int subList(list_node *operand1, list_node *operand2, list_node **result);

int multiplyList(list_node *operand1, list_node *operand2, list_node **result);

int divideList(list_node *operand1, list_node *operand2, list_node **quotient, list_node **reminder);

int compareRevIntList(list_node *operand1, list_node *operand2);
int compareIntList(list_node *operand1, list_node *operand2);
int gcd(list_node *operand1, list_node *operand2, list_node **result);
int exp(list_node *base, list_node* exp, list_node **result);