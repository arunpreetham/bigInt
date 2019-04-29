#include <iostream>
#include <error_code.h>
#include <linked_list.h>
#include <list_math.h>
#include <blum_blum_shub.h>
#include <fstream>

using namespace std;
/*
bool isPrime(unsigned int n, int k) 
{ 
   // Corner cases 
   if (n <= 1 || n == 4)  return false; 
   if (n <= 3) return true; 
  
   // Try k times 
   while (k>0) 
   { 
       // Pick a random number in [2..n-2]         
       // Above corner cases make sure that n > 4 
       int a = 2 + rand()%(n-4);   
  
       // Fermat's little theorem 
       if (power(a, n-1, n) != 1) 
          return false; 
  
       k--; 
    } 
  
    return true; 
}

int power(list_node *a,list_node *n, list_node *p) 
{ 
    list_node *res=NULL, *temp1=NULL, *temp2=NULL;
    res = listFromString("1");
    list_node *zero = listFromString("0");
    list_node *two = listFromString("2");
    a = a % p;  // Update 'a' if 'a' >= p 
    divideList(a, p, &temp1, &a); // Update 'a' if 'a' >= p 
    temp1 = NULL;
    while (IsEqual(temp1, zero)==1) 
    { 
        // If n is odd, multiply 'a' with result 
        divideList(n, two, temp1, temp2)
        if (IsEqual(temp2, zero)) 
            multiplyList(res, a, &tenp1)
            res = (res*a) % p; 
  
        // n must be even now 
        n = n>>1; // n = n/2 
        a = (a*a) % p; 
    } 
    return res; 
} 

int power(int a, unsigned int n, int p) 
{ 
    int res = 1;      // Initialize result 
    a = a % p;  // Update 'a' if 'a' >= p 
  
    while (n > 0) 
    { 
        // If n is odd, multiply 'a' with result 
        if (n & 1) 
            res = (res*a) % p; 
  
        // n must be even now 
        n = n>>1; // n = n/2 
        a = (a*a) % p; 
    } 
    return res; 
} 
*/