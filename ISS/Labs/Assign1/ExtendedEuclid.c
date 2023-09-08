#include <stdio.h>

int v[3];

void func(int a, int b)
{
    int a0=a, b0=b,t0=0,t=1,s0=1,s=0;
    int q=(int)(a0/b0);
    int r=a0-q*b0;
    
    while(r>0)
    {
        int temp=t0-q*t;
        t0=t;
        t=temp;
        s0=s;
        s=temp;
        a0=b0;
        b0=r;
        q=(int)(a0/b0);
        r=a0-q*b0;
    }
    
    r=b0;
    v[0]=r;
    v[1]=s;
    v[2]=t;
   return;
   
   int main()
   {
       int a,b;
       printf("Enter the value of a: ");
       scanf("%d", &a);
       printf("Enter the value of b: ");
       scanf("%d", &b);
       
       func(a,b);
       printf("r: %d\ns: %d\n: %d",v[0],v[1],v[2]);
   }
}