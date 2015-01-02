// FSDT.cpp : �������̨Ӧ�ó������ڵ㡣
//
// FSDT.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include"FSDT.h"
void FSDT()
{
	
	while(1)
	{
		printf("\t\t���������������������֮����������롪��������\n\n");
		printf("����������ţ�1-���������Կ 2-�鿴ȫ��������Կ 3-���� 4-���� 5-���� 6-����\n\n");
		char OpNum;	//������
		do
		{
			OpNum=_getch();
		}while(!(OpNum>='1'&&OpNum<='6'));
		switch(OpNum)
		{
		case '1':
			Create_Random_Key();
			break;
		case '2':
			Create_Total_Key();
			break;
		case '3':
			printf("���ܱ任��E(m)=(mk1+k0) mod 26\n\n");
			Cipher();
			break;
		case '4':
			printf("���ܱ任��D(c)=(c-k0)k1^-1 mod 26\n\n");
			Decipher();
			break;
		case '5':
			system("cls");
			break;
		case '6':
			return;
			break;
		default:
			break;
		}
	}
}

void Create_Total_Key()
{
	int i,j,k=0,K1Num=0,K1[MAXQ],q;
	FILE *fp;
	printf("��������Կ�ռ�Ԫ�ظ���q��1000���ڣ�:\n");
	while(1)
	{
		scanf("%d",&q);
		if (q>1000)
		{
			printf("��Կ�ռ�������������룡\n");
			continue;
		}
		break;
	}
	fp=fopen("Key.txt","w");
	for(i=1;i<q;i++)
	{
		if(1==GCD(i,q))
		{
			K1[K1Num++]=i;			//��¼����k1
		}
	}
	fprintf(fp,"��Կ��ʽ��[k1,k0]\n");
	for(i=0;i<q;i++)
	{
		for(j=0;j<K1Num;j++)
		{
			if(!(0==i&&1==K1[j]))
				fprintf(fp,"No.%d\t[%d,%d]\n",++k,K1[j],i);
		}
	}
	printf("ȫ��%d��������Կ�����ɵ�\"Key.txt\"�ļ��У�\n\n",k);
	fclose(fp);
}

void Create_Random_Key()
{
	int RandK1,RandK0;
	int i,q,K1Num=0,K1[MAXQ];
	srand((unsigned int)time(NULL));
	printf("��������Կ�ռ�Ԫ�ظ���q��1000���ڣ�:\n");
	while(1)
	{
		scanf("%d",&q);
		if (q>1000)
		{
			printf("��Կ�ռ�������������룡\n");
			continue;
		}
		break;
	}
	if(q<=1)
	{
		printf("û�п��õ���Կ��\n\n");
		fflush(stdin);
		return;
	}
	for(i=1;i<q;i++)
	{
		if(1==GCD(i,q))
		{
			K1[K1Num++]=i;			//��¼����k1
		}
	}
	do
	{
		RandK1=rand()%K1Num;
		RandK0=rand()%q;
	}while(0==RandK0&&1==K1[RandK1]);
	printf("�����Կ[k1,k0]��[%d,%d]\n\n",K1[RandK1],RandK0);
}

void Cipher()
{
	int k1,k0,i;
	char OpNum,ch;
	char FileName[255];
	FILE *fin,*fout;
	TextLink head=NULL,p=NULL,r=NULL;
	printf("�����������Կk1,k0,�Կհ��ַ��ָ���\n\n");
	while(1)
	{
		scanf("%d%d",&k1,&k0);
		if(1==GCD(k1,26)&&0!=k0&&k1>0&&k0>=0)
			break;
		else
			printf("���������Կ�����ã����������룡\n\n");
		fflush(stdin);
	}
	printf("ѡ���������뷽ʽ��1-�������� 2-���ļ�����\n\n");
	do
	{
		OpNum=_getch();
	}while(OpNum!='1'&&OpNum!='2');
	if('1'==OpNum)
	{
		printf("������Ҫ������ļ�����������չ����:\n");
		scanf("%s",FileName);
		printf("���������ģ���ctrl+z������\n");
	}
	else
	{
		while(1)
		{
			printf("�������ļ�����������չ������\n");
			scanf("%s",FileName);
			fin=fopen(FileName,"r");
			if(NULL==fin)
			{
				printf("���ļ�ʧ�ܣ������ԣ�\n\n");
				continue;
			}
			break;
		}
		printf("������Ҫ������ļ�����������չ����:\n");
		scanf("%s",FileName);
	}

	fout=fopen(FileName,"w");
	getchar();//�����س�
	while(1)
	{
		ch='1'==OpNum?getchar():fgetc(fin);
		if(EOF==ch)	break;
		if(ch>='a'&&ch<='z')
		{
			ch=((ch-'a')*k1+k0)%26+'a';			//��Сд����
			//ch=((ch-'a')*k1+k0)%26+'A';			//ȫת�ɴ�д
		}
		else if(ch>='A'&&ch<='Z')
		{
			ch=((ch-'A')*k1+k0)%26+'A';			//��Сд����
			//ch=((ch-'A')*k1+k0)%26+'a';			//ȫת��Сд
		}
		fputc(ch,fout);
	}
	fprintf(fout,"\n�����Ķ��ձ�\n");
	fprintf(fout,"\n���ģ�");
	for(i=0;i<26;i++)
	{
		fprintf(fout,"%c ",i+'a');
	}
	fprintf(fout,"\n���ģ�");
	for(i=0;i<26;i++)
	{
		fprintf(fout,"%c ",(i*k1+k0)%26+'A');
	}
	if('2'==OpNum)	fclose(fin);
	fclose(fout);
	printf("���ܺ�������������\"%s\"�ļ���\n\n",FileName);
}

void Decipher()
{
	int k1,k0,i;
	char OpNum,ch,FileName[255];
	FILE *fp;
	TextLink head=NULL,p=NULL,r=NULL;
	printf("ѡ���������뷽ʽ��1-�������� 2-���ļ�����\n\n");
	do
	{
		OpNum=_getch();
	}while(OpNum!='1'&&OpNum!='2');
	if('1'==OpNum)
	{
		printf("������Ҫ������ļ�����������չ����:\n");
		scanf("%s",FileName);
		printf("���������ģ���ctrl+z������\n");
	}
	else
	{
		while(1)
		{
			printf("�������ļ�����������չ������\n");
			scanf("%s",FileName);
			fp=fopen(FileName,"r");
			if(NULL==fp)
			{
				printf("���ļ�ʧ�ܣ������ԣ�\n\n");
				continue;
			}
			break;
		}
		printf("������Ҫ������ļ�����������չ����:\n");
		scanf("%s",FileName);
	}
	getchar();//�����س�
	while(1)
	{
		ch='1'==OpNum?getchar():fgetc(fp);
		if(EOF==ch) break;
		if(NULL==head)
		{
			head=(TextLink)malloc(sizeof(Text));
			head->c=ch;
			head->next=NULL;
			p=head;
		}
		else
		{
			p=(TextLink)malloc(sizeof(Text));
			p->c=ch;
			p->next=NULL;
			r->next=p;
		}
		r=p;
	}
	printf("�Ƿ���֪��Կ��Y/N\n");
	do
	{
		ch=getchar();
	}while(ch!='Y'&&ch!='y'&&ch!='N'&&ch!='n');
	if('2'==OpNum)	fclose(fp);
	fp=fopen(FileName,"w");
	if('Y'==ch||'y'==ch)		//��֪��Կ
	{
		printf("��������Կk1,k0,�Կհ��ַ��ָ���\n\n");
		scanf("%d%d",&k1,&k0);
		p=head;
		while(p)
		{
			if(p->c>='a'&&p->c<='z')
			{
				p->c=((p->c-'a')-k0+26)*Key1_R[k1]%26+'a';			//��Сд����
				//ch=((ch-'a')-k0+26)*Key1_R[k1]%26+'A';			//ȫת�ɴ�д
			}
			else if(p->c>='A'&&p->c<='Z')
			{
				p->c=((p->c-'A')-k0+26)*Key1_R[k1]%26+'A';			//��Сд����
				//ch=((ch-'A')-k0+26)*Key1_R[k1]%26+'a';			//ȫת��Сд
			}
			fputc(p->c,fp);
			p=p->next;
		}
		while(head)
		{
			p=head->next;
			free(head);
			head=p;
		}
		fprintf(fp,"\n�����Ķ��ձ�\n");
		fprintf(fp,"\n���ģ�");
		for(i=0;i<26;i++)
		{
			fprintf(fp,"%c ",i+'A');
		}
		fprintf(fp,"\n���ģ�");
		for(i=0;i<26;i++)
		{
			fprintf(fp,"%c ",(i-k0+26)*Key1_R[k1]%26+'a');
		}
		fclose(fp);
		printf("���ܺ�������������\"%s\"�ļ���\n\n",FileName);
	}
	else		//δ֪��Կ
	{
		int i,j,k=0;
		char temp;
		for(i=0;i<12;i++)
		{
			k1=Key1[i];
			for(j=0;j<26;j++)
			{
				k0=j;
				fprintf(fp,"���ܽ��%d:\n",++k);
				p=head;
				while(p)
				{
					temp=p->c;
					if(temp>='a'&&temp<='z')
					{
						temp=((temp-'a')-k0+26)*Key1_R[k1]%26+'a';			//��Сд����
						//temp=((temp-'a')-k0+26)*Key1_R[k1]%26+'A';			//ȫת�ɴ�д
					}
					else if(temp>='A'&&temp<='Z')
					{
						temp=((temp-'A')-k0+26)*Key1_R[k1]%26+'A';			//��Сд����
						//temp=((temp-'A')-k0+26)*Key1_R[k1]%26+'a';			//ȫת��Сд
					}
					fputc(temp,fp);
					p=p->next;
				}
				fputc('\n',fp);
			}
		}
		printf("ȫ�����ܽ���������\"%s\"�ļ���\n\n",FileName);
		fclose(fp);
	}
}

int GCD(int a,int b)
{
	int r;
	if(b==0)
		return a;
	do
	{
		r=a%b;
		a=b;
		b=r;
	}while(r!=0);
	return a;
}