#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
void swap(int *a,int *b)
{
	int t=*a;
	*a=*b;
	*b=t;
}
void init(int key[],int len,int s[])
{
	int i,j,t[256];
	for(i=0;i<256;i++)
	{
		s[i]=i;
		t[i]=key[i%len];
	}
	for(i=0,j=0;i<256;i++) 
	{
		j=(j+s[i]+t[i])%256;
		swap(&s[i],&s[j]);
	}
}
void stream(int s[],int len,int key[])
{
	int i=0,j=0,k=0;
	while(k<len)
	{
		i = (i+1)%256;
		j=(j+s[i])%256;
		swap(&s[i],&s[j]);
		key[k++]=s[(s[i]+s[j])%256];
	}
}
void encrypt(int p[],int key[],int len,int c[])
{
	int i;
	for(i=0;i<len;i++)
		c[i]=p[i]^key[i];
	printf("\nThe encrypted message is: ");
	for(i=0;i<len;i++)
		printf("%d\t",c[i]);
}
void decrypt(int p[],int key[],int len,int c[])
{
	int i;
	for(i=0;i<len;i++)
		p[i]=c[i]^key[i];
	printf("\nThe decrypted message is: ");
	for(i=0;i<len;i++)
		printf("%d\t",p[i]);
}
void main()
{
		int s[256],k[256],len,key[500],p[500],c[500];
		int i;
		printf("Enter the length of the key: ");
		scanf("%d",&len);
		printf("Enter the key : ");
		for(i=0;i<len;i++)
			scanf("%d",&k[i]);
		init(k,len,s);
		printf("Enter the length of the message: ");
		scanf("%d",&len);
		printf("Enter the message: \n");
		for(i=0;i<len;i++)
			scanf("%d",&p[i]);
		stream(s,len,key);
		encrypt(p,key,len,c);
		decrypt(p,key,len,c);
}
