#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<netinet/in.h>
typedef long int int32;
int32 t,e,d,n,p,q;
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
    printf("\nEnter two prime numbers: ");
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

    d = 0;
    do
    {
        d++;
        s = (d*e)%phi;
    }while(s!=1);

    printf("\nPublic key: { e=%d n=%d }",e,n);
    printf("\nPrivate key: { d=%d n=%d }\n",d,n);
}
int32 decryptencrypt(int32 key,int32 msg) 
{ 
	int32 k;
	int32 i=0,j; 
    k=1; 
    for(j=0;j<key;j++) 
    { 
		k=k*msg; 
		k=k%n; 
    } 
    return k;
}
void main()
{
	int sockfd,clen;
	int32 msg,en,m;
	int32 pu[2];
	struct sockaddr_in server;
	int port;
	char host[15];
	clen = sizeof(server);
	bzero((char*)&server,sizeof(server));
	printf("Enter the port number: ");
	scanf("%d",&port);
	printf("Enter the receiver address : ");
	scanf("%s",host);
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = inet_addr(host);
	connect(sockfd,(struct sockaddr*)&server,sizeof(server));
	keygen();
	pu[0] = e;											// PU{e,n}
	pu[1] = n;
	
	send(sockfd,(char*)pu,sizeof(pu),0);
	printf("Public key sent...\n");
	printf("Waiting to receive encrypted message...\n");
//	bzero((char*)&server,clen);
	
	recv(sockfd,&en,sizeof(en),0);
	
	printf("Recieved the encrypted message: %ld \n",en);
	printf("Decrypting...\n");
	m = decryptencrypt(d,en);
	printf("The decrypted message is : %ld \n",m);
	close(sockfd);
}
