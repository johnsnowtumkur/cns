/* USER A */
#include<stdio.h>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h>
void main()
{
	struct sockaddr_in kdc;
	int sfda,idA,idB,nonce,i;
	int port,portb, snd[3],rcv[6],sndb[2];
	int ka,ks,c,p;

	sfda= socket(AF_INET,SOCK_STREAM,0);

	printf("Enter the Master Key of User A: ");
	scanf("%d",&ka);
		
	printf("Enter the KDC port: ");
	scanf("%d",&port);
	printf("Enter the User B port: ");
	scanf("%d",&portb);

	bzero((char *)&kdc,sizeof(kdc));
	kdc.sin_family= AF_INET;
	kdc.sin_addr.s_addr=inet_addr("127.0.0.1");
	kdc.sin_port=htons(port);
	printf("Connecting to KDC...\n");
	connect(sfda,(struct sockaddr *)&kdc,sizeof(kdc));
		
	printf("Enter the Identity of A:\n");
	scanf("%d",&idA);
	
	printf("Enter the Identity of B:\n");
	scanf("%d",&idB);
	
	printf("Enter the nonce value:\n");
	scanf("%d",&nonce);
	
	snd[0]=idA;
	snd[1]=idB;
	snd[2]=nonce;
		
	printf("Sending idA, idB and nonce...\n");
	write(sfda,snd,sizeof(snd)); 				// IDA||IDB||N1
	
	printf("Waiting to read the values...\n");
	read(sfda,rcv,sizeof(rcv));					// Read E(Ka,Ks||IDA||IDB||N1)||E(Kb,Ks||IDA)
	close(sfda);								// Communication over with KDC, closed the connection
		
	ks = rcv[0]^ka;
	sndb[0] =rcv[4]; // E(Kb,Ks)
	sndb[1] =rcv[5]; // E(Kb,IDA)
	printf("Session Key is : %d\n \n",ks);	
	
	printf("Connecting to USER B...\n");
	sfda = socket(AF_INET,SOCK_STREAM,0);		// Creating a Socket to Connect to User B
	bzero((char*)&kdc,sizeof(kdc));
	kdc.sin_family=AF_INET;
	kdc.sin_addr.s_addr=inet_addr("127.0.0.1");
	kdc.sin_port = htons(portb);
	
	
	connect(sfda,(struct sockaddr*)&kdc,sizeof(kdc));

	write(sfda,sndb,sizeof(sndb));				// E(Kb,Ks||IDA)
	recv(sfda,&c,sizeof(c),0);
	p=c^ks;
	printf("The N2 received: %d\n",p);			
	c=(p+1)^ks;
	send(sfda,&c,sizeof(c),0);
	recv(sfda,&c,sizeof(c),0);
	printf("The message received from User B is %d\nDone!\n",c^ks);
	close(sfda);
}
