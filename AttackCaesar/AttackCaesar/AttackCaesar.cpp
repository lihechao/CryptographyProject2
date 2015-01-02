// AttackCaesar.cpp : 定义控制台应用程序的入口点。
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
	printf("\t\t——————加法密码频率攻击——————\n\n");
	while(1)
	{
		printf("请选择密文输入方式：1-从键盘输入 2-从文件读入\n\n");	
		do
		{
			OpNum=_getch();
		}while('1'!=OpNum&&'2'!=OpNum&&'3'!=OpNum);
		if('1'==OpNum)
		{
			printf("请输入密文，回车后以ctrl+z结束：\n");
		}
		else
		{
			while(1)
			{
				printf("\n请输入文件名（包括扩展名）：");
				scanf("%s",FileName);
				printf("\n");
				if(NULL==(fin=fopen(FileName,"r")))
				{
					printf("打开文件%s失败，请重试！\n",FileName);
					continue;
				}
				break;
			}
		}
		while(1)
		{
			ch='1'==OpNum?getchar():fgetc(fin);
			if(EOF==ch)	break;
			if(ch>='A'&&ch<='Z')//全部转成小写便于后续处理
				ch='a'+ch-'A';
			if (ch>='a'&&ch<='z')
			{
				if ((++LetterNum[ch-'a'])>Max)//找频率最高字母
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
			if (4==(MaxLetter-'a'+i)%26)//4是因为’e'-'a'=4
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
		while(head)	//销毁链表
		{
			p=head;
			head=head->next;
			free(p);
		}
		printf("所有可能结果已输出至\"result.txt\"文件中。\n\n");
		fclose(fout);
	}
	return 0;
}

