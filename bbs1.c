#include<stdio.h>
#include<time.h>
#include<math.h>
typedef unsigned long long int u32;
typedef unsigned short u16;
#define COMPOSITE 0
#define PRIME     1
u16 modular_exponent_16(u16 base, u16 power, u16 modulus) {
     u32 result = 1;
     int i;
     for (i=15; i>=0; i--) {
         result = (result*result) % modulus;
         if (power & (1 << i)) {
             result = (result*base) % modulus;
         }
     }
     return (u16)result; /* Will not truncate since modulus is a u16 */
 }
int miller_rabin_pass_16(u16 a, u16 n) {
     u16 power, s, d, i;
     s = 0;
     d = n - 1;
     while ((d % 2) == 0) {
         d /= 2;
         s++;
     }
     power = modular_exponent_16(a, d, n);
     if (power == 1) return PRIME;
     for(i=0; i < s-1; i++) {
         if (power == n-1) return PRIME;
         power = modular_exponent_16(power, 2, n);
     }
     if (power == n-1) return PRIME;
     return COMPOSITE;
 }

 int miller_rabin_16(u16 n) {
     if (n <= 1) return COMPOSITE;
     if (n == 2) return PRIME;
     if (miller_rabin_pass_16( 2, n) == PRIME &&
         (n <= 7  || miller_rabin_pass_16( 7, n) == PRIME) &&
         (n <= 61 || miller_rabin_pass_16(61, n) == PRIME))
         return PRIME;
     else
         return COMPOSITE;
 }
u32 gcd(u32 a,u32 b)
{
    u32 n=1;
    while(n)
    {
        n=a%b;
        a=b;
        b=n;
    }
    return a;
}

void main()
{
    void check(u32);
    int p,q,i,no;
    u32 n,s,res=0,x;
    printf("Enter two prime numbers (3mod4): ");
    scanf("%d%d",&p,&q);
    n=p*q;
    printf("Enter the no of bits required: ");
    scanf("%d",&no);
    srand(time(NULL));
    do{
        s= rand();
    }while(gcd(s,n)!=1);
    x=(s*s)%n;
    for(i=1;i<=no;i++)
    {
        x = (x*x)%n;
        res = (res<<1)|(x&1);
    }
    printf("Random no. = %llu\n",res);
   puts(miller_rabin_16(res) == PRIME ? "INCONCLUSIVE" : "COMPOSITE");
}
