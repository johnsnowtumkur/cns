#include<stdio.h>
#include<string.h>
#include<ctype.h>
char key[26]={'g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','a','b','c','d','e','f'};
float sf2[28]={8.167,1.492,2.782,4.253,12.702,2.228,2.015,6.094,6.996,0.153,0.773,4.025,2.406,6.749,7.507,1.929,0.095,5.987,6.327,9.056,2.758,0.978,2.360,0.150,1.974,0,074};

int cf2[26];
void analysis();
int max1();
int max2();

int main()
{
	FILE *fp1,*fp2;
	int i,j;
	char c1,c2;
	fp1=fopen("plain.txt","r");
	fp2=fopen("cipher.txt","w");
	while((c1=fgetc(fp1))!=EOF)
	{
		if(isalpha(c1))
		{
			c2=key[tolower(c1)-'a'];
		}
		fputc(c2,fp2);
	}
		fclose(fp1);
		fclose(fp2);
		analysis();
		return 0;
}

void analysis()
{
	int i,j;
	char c;
	int ch1,ch2;
	FILE *fp;
	fp=fopen("cipher.txt","r");
	while((c=fgetc(fp))!=EOF)
	{
		if(isalpha(c))
			cf2[tolower(c)-'a']++;
	}
	for(i=0;i<26;i++)
	{
		ch1=max1()+'a';
		ch2=max2()+'a';
		printf("\n %c is replaced with %c",ch1,ch2);
	}
	fclose(fp);
}
int max1()
{
	float max=0;
	int i,index=0;
	max=sf2[0];
	for(i=0;i<26;i++)
	{
		if(sf2[i]>max)
		{
			index=i;
			max=sf2[i];
		}
	}
	sf2[index]=0;
	return index;
}
int max2()
{
	float max=0;
	int i,index=0;
	max=cf2[0];
	for(i=0;i<26;i++)
	{
		if(cf2[i]>max)
		{
			index=i;
			max=cf2[i];
		}
	}
	cf2[index]=0;
	return index;
}
