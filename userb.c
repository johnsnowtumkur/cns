/* USER B */
#include<stdio.h>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h>
void main()
{
	struct sockaddr_in usera;
	int sfda,idA,idB,nonce,nsfda;
	int clen;
	int porta, snd[3],rcv[3],sndb[2];
	int kb,ks,n2,c;
	
	clen=sizeof(usera);

	sfda= socket(AF_INET,SOCK_STREAM,0);

	printf("Enter the Master Key of User B: ");
	scanf("%d",&kb);
	printf("Enter the User A port: ");
	scanf("%d",&porta);
		
	sfda= socket(AF_INET,SOCK_STREAM,0);		// Create a socket to connect to User A
	
	bzero((char *)&usera,sizeof(usera));
	usera.sin_family= AF_INET;
	usera.sin_addr.s_addr=INADDR_ANY;
	usera.sin_port=htons(porta);
	
	bind(sfda, (struct sockaddr*)&usera,clen);
	listen(sfda,1);
	bzero((char*)&usera,sizeof(usera));	
	nsfda = accept(sfda,(struct sockaddr*)&usera,&clen);
	close(sfda);
	
	read(nsfda,sndb,sizeof(sndb));				// E(Kb,Ks||IDA)
	ks = sndb[0]^kb;							// Decrypting the Session Key
	printf("Session Key is : %d\nIDA is : %d\n",ks,sndb[1]^kb);
	
	printf("Enter the Nonce value: ");
	scanf("%d",&n2);
	c=n2^ks;									// E(Ks,N2)
	printf("Encrypted message sent is: %d\n",c);
	send(nsfda,&c,sizeof(c),0);					// E(Ks,N2)
	recv(nsfda,&c,sizeof(c),0);					// E(Ks,f(N2))
	c=c^ks;
	printf("The message received from user A is %d\n",c);
	if(c==n2+1){
		printf("User A Verified\n");
		printf("Enter the message to be sent to User A: ");
		scanf("%d",&c);
		c=c^ks;
		send(nsfda,&c,sizeof(c),0);
	}
	else printf("User A not verified\n");
	printf("Done!\n");
	close(nsfda);
}
