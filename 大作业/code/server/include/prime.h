#ifndef __PRIME_H__
#define __PRIME_H__
#include <math.h>
extern int prime[1000];
bool isPrime(int n)
{
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    int foo = (int)sqrt(n);
    for (int i = 3; i <= foo; i += 2)
        if (n % i == 0) return false;
    return true;
}
void genPrime()
{
    int base = 1;
    for (int i = 0; i < 1000; i++)
    {

        while (base++)
        {
            if (isPrime(base))
            {
                prime[i] = base;
                break;
            }
        }
    }
}
#endif // !__PRIME_H__

