#include<stdio.h>
#include<math.h>
#include<stdlib.h>
int p,q,n,s,b;
int num;
int i,rem;
int x[10];

void MillerRabin(int n)
{
	int k,q,j,m;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if((n-1)==pow(2,i)*j)
			{
				k=i;
				q=j;
				break;
			}
		}
	}
	//Generate a random number
	int a;
	a=((int)rand()%n);
	printf("\na is %d",a);
	if(((int)pow(a,q))%n==1)
	{
		printf("\nInconcusive\n");
		return;
	}
	for(m=0;m<k;m++)
	{
		if(((int)pow(a,((2,j)*q))%n)==n-1)
		{
			printf("\nInconclusive\n");
			return;
		}
	}
	printf("\nComposite\n");
	return;	
}
int gcd(int n,int s)
{
	if(n>s)
	{
		if(s>0)
			return (gcd(s,n%s));
		else
			return n;
	}
}

void BlumBlumShub()
{
	n=p*q;
	printf("\nEnter a random number that is reativey prime to %d : ",n);
	scanf("%d",&s);
	if(gcd(n,s)==1)
	{
		x[0] = (s*s)%n;
		num = 0;
		printf("\nEnter the number of times : ");
		scanf("%d",&num);
		printf("\n%d",x[0]);
		int d;
		for(d=1;d<=num;d++)
		{
			printf("\nIteration %d : \n",d);
			x[d] = ((int)pow(x[d-1],2))%n;
			//find pairity
			printf("%d ",x[d]);
			MillerRabin(x[d]);
		}
	}
}

int checkPandQ()
{
	int flag = 0,i;
	for(i=1;i<p;i++)
		if(p%i==0)
			flag++;
	if(flag!=1)
	{
		printf("\n%d is composite",p);
		exit(1);
	}
	flag = 0;
	for(i=1;i<q;i++)
	{
		if(q%i==0)
			flag++;
	}
	if(flag!=1)
	{
		printf("\n%d is composite",q);
		exit(1);
	}
	if((p%4==3)&&(q%4==3))
		return 1;
	else
		return 0;
}

int main()
{
	printf("\nEnter 2 large prime numbers congruent to 3mod4\n");
	scanf("%d%d",&p,&q);
	if(checkPandQ()==1)
	{
		BlumBlumShub();
	}
	else
	{
		printf("\nEnter 2 large prime numbers congruent 3mod4\n");
	}
	return 0;
}
