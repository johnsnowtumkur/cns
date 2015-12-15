/* Implement RSA algorithm (key generation, encryption, and decryption) considering two users as two different processes. */
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#include<ctype.h>
typedef long int int32;
int32 t,e,n,d,p,q;
char msg[50],en[50],m[50];
int32 gcd(int32 a,int32 b)
{
	int32 n=1;
	while(n)
	{
		n= a%b;
		a=b;
		b=n;
	}
	return a;
}
void keygen()
{
    int32 phi,s;
    printf("\nUSER1 : Enter two prime numbers: ");
    scanf("%d%d",&p,&q);

    n = p*q;
    phi=(p-1)*(q-1);
    e=1;
    do
    {
    	e++;
    	t=gcd(phi,e);
    	printf("%ld ",t);
    }while(t!=1&&e<phi);
    // selec d such that d*e = 1+ k*phi for some integer k.
    d = 0;
    do
    {
        d++;
        s = (d*e)%phi;
    }while(s!=1);

    printf("\nUSER1 : Public key: { e=%d n=%d }",e,n);
    printf("\nUSER1 : Private key: { d=%d n=%d }\n",d,n);

}
/**
	Params: 
		cipher: key (e in case of encryption OR d in case of decryption)
		iptext: the text to be encrypted OR decrypted (msg in case of encryption and en in case of decryption)
		optext: the o/p text (ciphertext 'en' in case of encryption OR plaintext in case of decryption)

*/
void decryptencrypt(int32 cipher,char iptext[50],char optext[50]) 
{ 
	int32 ct,key=cipher,k,len; 
	int32 i=0,j; 
	len = strlen(iptext);
	while(i!=len) 
	{ 
	    ct=tolower(iptext[i]);
	    ct-=96; 
	    k=1; 
	    for(j=0;j<key;j++) 
	    { 
		k=k*ct; 
		k=k%n; 
	    } 
	    optext[i]=k+96;
	    i++;
	} 
	optext[i]='\0';
}

void main()
{
	int p1[2],p2[2]; 										// 0 - read ; 1 - write
	int32 pu[2];
	pid_t id;
	pipe(p1);												// user1 to user2
	pipe(p2);												// user2 to user1
	id = fork();
	if(id!=0){	// parent process is USER1
		keygen();
		pu[0] = e;											// PU{e,n}
		pu[1] = n;
		write(p1[1],pu,sizeof(pu));							// send the public key to USER2
		wait();
		read(p2[0],en,sizeof(en));							// receive the encrypted text
		printf("\nUSER1 : The encrypted message recieved is %s",en);
		decryptencrypt(d,en,m);								// decrypt the encrypted text using the private key 'd'
		printf("\nUSER1 : The decrypted message is : %s\n",m);
	}
	else{		// child process is USER2
		read(p1[0], pu, sizeof(pu)); 						// read the public key PU{e,n}
		printf("\nUSER2 : The received public key is PU{%ld,%ld}",pu[0],pu[1]);
		e=pu[0],n=pu[1];
		printf("\nUSER2 : Enter the message to be encrypted: ");
		gets(msg);
		decryptencrypt(e,msg,en);							// encrypt the message using the public key 'e'
		printf("\nUSER2 : The encrypted message sent is %s",en);
		write(p2[1],en, sizeof(en));						// send the encrypted message to the USER2
	}
}
