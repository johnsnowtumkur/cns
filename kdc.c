/* KDC */
#include<stdio.h>
#include<netinet/in.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
void main()
{
	struct sockaddr_in usera;
	int sfda,nsfda,porta,clen;
	int ks,i,ka,kb;
	int rcv[3],snd[6];
	
	srand(time(NULL));
	clen = sizeof(usera);
	sfda=socket(AF_INET, SOCK_STREAM,0);
	
	printf("Enter the Master key of User A:  ");
	scanf("%d",&ka);
	printf("Enter the Master key of User B:  ");
	scanf("%d",&kb);
	printf("Enter the port number of User A: ");
	scanf("%d",&porta);
	bzero((char*)&usera,sizeof(usera));
	usera.sin_family = AF_INET;
	usera.sin_port = htons(porta);
	usera.sin_addr.s_addr = INADDR_ANY;
	
	printf("Setting Connection with User A...");
	bind(sfda,(struct sockaddr*)&usera,sizeof(usera));
	listen(sfda,1);
	nsfda=accept(sfda,(struct sockaddr*)&usera,&clen);
	close(sfda);

	recv(nsfda,rcv,sizeof(rcv),0);
	printf("\nIDA: %d \nIDB: %d\nNONCE: %d\n",rcv[0],rcv[1],rcv[2]);

	ks = rand()%1000;   		// Generate a random Session Key
	
	printf("Session Key: %d\n",ks);

	snd[0]=ks^ka;				// E(Ka,Ks)
	for(i=0;i<3;i++)
		snd[i+1]=rcv[i]^ka;     // E(Ka,IDA||IDB||N1)
	snd[4]=ks^kb;				// E(Kb,Ks)
	snd[5]=rcv[0]^kb;			// E(Kb,IDA)
	
	printf("Sending the message from KDC to User A\n");	
	send(nsfda,snd,sizeof(snd),0); // E(Ka,Ks||IDA||IDB||N1)||E(Kb,IDA)
	printf("Done!\n");
	close(nsfda);		
}
