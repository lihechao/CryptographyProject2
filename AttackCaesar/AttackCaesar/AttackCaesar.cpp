// AttackCaesar.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include<conio.h>
#include<stdlib.h>
typedef struct text
{
	char c;
	text* next;
}Text,*TextLink;

int main(int argc, _TCHAR* argv[])
{
	int i,LetterNum[26]={0},Max=0;
	char OpNum,ch,MaxLetter,FileName[255];
	FILE *fin,*fout;
	TextLink head=NULL,p,r;
	printf("\t\t�������������ӷ�����Ƶ�ʹ���������������\n\n");
	while(1)
	{
		printf("��ѡ���������뷽ʽ��1-�Ӽ������� 2-���ļ�����\n\n");	
		do
		{
			OpNum=_getch();
		}while('1'!=OpNum&&'2'!=OpNum&&'3'!=OpNum);
		if('1'==OpNum)
		{
			printf("���������ģ��س�����ctrl+z������\n");
		}
		else
		{
			while(1)
			{
				printf("\n�������ļ�����������չ������");
				scanf("%s",FileName);
				printf("\n");
				if(NULL==(fin=fopen(FileName,"r")))
				{
					printf("���ļ�%sʧ�ܣ������ԣ�\n",FileName);
					continue;
				}
				break;
			}
		}
		while(1)
		{
			ch='1'==OpNum?getchar():fgetc(fin);
			if(EOF==ch)	break;
			if(ch>='A'&&ch<='Z')//ȫ��ת��Сд���ں�������
				ch='a'+ch-'A';
			if (ch>='a'&&ch<='z')
			{
				if ((++LetterNum[ch-'a'])>Max)//��Ƶ�������ĸ
				{
					Max=LetterNum[ch-'a'];
					MaxLetter=ch;
				}
			}
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
		fout=fopen("result.txt","w");
		for(i=1;i<26;i++)
		{
			if (4==(MaxLetter-'a'+i)%26)//4����Ϊ��e'-'a'=4
			{
				p=head;
				while(p)
				{
					fputc(p->c>='a'&&p->c<='z'?(p->c+i-'a')%26+'a':p->c,fout);
					p=p->next;
				}
				fputc('\n',fout);
				break;
			}
		}
		while(head)	//��������
		{
			p=head;
			head=head->next;
			free(p);
		}
		printf("���п��ܽ���������\"result.txt\"�ļ��С�\n\n");
		fclose(fout);
	}
	return 0;
}

