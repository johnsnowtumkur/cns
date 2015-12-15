#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void encrypt(char[],char[],int,int);
void decrypt(char[],char[],int,int);
void bruteforce(char[],char[]);
int main()
{
    char plain[50],cipher[50];
    int k1,k2;
    printf("Enter the plain text: ");
    gets(plain);
    printf("Enter the keys for lowercase and uppercase letters, respectively:\n");
    scanf("%d%d",&k1,&k2);
    encrypt(plain,cipher,k1,k2);
    decrypt(plain,cipher,k1,k2);
    bruteforce(plain,cipher);
    return 0;
}
void encrypt(char p[],char c[],int k1,int k2)
{
	int i;
    for(i=0;i<strlen(p);i++)
    {
        if(isupper(p[i]))
            c[i]=(p[i]-'A'+k2)%26+'A';
        else if(islower(p[i]))
            c[i]=(p[i]-'a'+k1)%26+'a';
        else
            c[i]=p[i];
    }
    c[i]='\0';
    printf("The encrypted text is: %s\n",c);
}
void decrypt(char p[],char c[],int k1,int k2)
{
	int i,n=strlen(c);
    for(i=0;i<n;i++)
    {
        if(isupper(c[i]))
            p[i]=(c[i]-'A'+26-k2)%26+'A';
        else if(islower(c[i]))
            p[i]=(c[i]-'a'+26-k1)%26+'a';
        else
            p[i]=c[i];
    }
    p[i]='\0';
    printf("Decrypted text with k1= %2d and k2= %2d : %s\n",k1,k2,p);
}
void bruteforce(char p[],char c[])
{
    int k1,k2,i,j;
    char temp[50];

    printf("\n\n");
    for(i=0;i<26;i++)
        for(j=0;j<26;j++)
        {
            decrypt(temp,c,i,j);
            if(strcmp(temp,p)==0)
            {
                printf("\nKeys found....k1 = %2d and k2= %2d \n",i,j);
                return;
            }
        }
}
