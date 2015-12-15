#include<stdio.h>
#include<string.h>
void main()
{
	int l1,i,d,j,d1;
	printf("\n enter length of key:\n");
	scanf("%d",&l1);
	int sequence[l1];
	printf("enter seq ky:\n");
	for(i=0;i<l1;++i)
	{
		scanf("%d",&sequence[i]);
	}
	int order[l1];
	for(i=1;i<=l1;++i)
	{
		for(j=0;j<l1;++j)
		{
			if(sequence[j]==i)
				order[i-1]=j;
		}
	}
	printf("enter depth\n");
	scanf("%d",&d);
	d1=d;
	int l2,len;
	char p[100];
	printf("enter string without spaces\n");
	scanf("%s",p);
	l2=strlen(p);
	if(l2%l1!=0)
	{
		while(l2%l1!=0)
			p[l2++]='x';
		p[l2]='\0';
		printf("bogus char used:%c\n",'x');
		printf("final ip:%s",p);
	}
	int r=l2/l1;
	char p1[r][l1];
	int count=0,k=1;
	printf("\n encryption\n");
	while(d>0)
	{
		count=0;
		printf("depth:%d\n",k);
		k=k+1;
		for(i=0;i<r;i++)
		{
			for(j=0;j<l1;j++)
			{
				p1[i][j]=p[count];
				count=count+1;
			}
		}
		for(i=0;i<r;i++)
		{
			for(j=0;j<l1;j++)
			{
				printf("%c",p1[i][j]);
			}
			printf("\n");
		}
		count=0;
		for(i=0;i<l1;++i)
		{
			for(j=0;j<r;++j)
			{
				p[count]=p1[j][order[i]];
				count=count+1;
			}
		}
		printf("\n ciphertext:\n");
		for(i=0;i<l2;i++)
			printf("%c",p[i]);
		printf("\n\n");
		d=d-1;
	}
	int k1=1;
	printf("decryption\n");
		while(d1>0)
	{
		count=0;
		printf("depth:%d\n",k1);
		k1=k1+1;
		for(i=0;i<l1;i++)
		{
			for(j=0;j<r;j++)
			{
				p1[j][order[i]]=p[count];
				count=count+1;
			}
		}
		for(i=0;i<r;i++)
		{
			for(j=0;j<l1;j++)
			{
				printf("%c",p1[i][j]);
			}
			printf("\n");
		}
		count=0;
		for(i=0;i<r;i++)
		{
			for(j=0;j<l1;j++)
			{
				p[count]=p1[i][j];
				count=count+1;
			}
		}
		printf("\n plaintext:\n");
		for(i=0;i<l2;i++)
			printf("%c",p[i]);
		printf("\n\n");
		d1=d1-1;
	}
}
