// Hill.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<stdio.h>
#include<conio.h>
void Cipher();
void Decipher();
void InverseMatrix(int Matrix[][2],int Inverse[][2],int Value);
int GCD(int a,int b);
const int Reverse[]={0,1,0,9,0,21,0,15,0,3,0,19,0,0,0,7,0,23,0,11,0,5,0,17,0,25};//ÿ���±��Ӧ��ģ26����
int main()
{
	char OpNum;
	printf("\t\t��������������Hill����ӽ��ܹ��ߡ���������������\n\n");
	while(1)
	{
		printf("����������ţ�1-���� 2-���� 3-�˳�\n\n");
		do 
		{
			OpNum=_getch();
		} while (!(OpNum>='1'&&OpNum<='3'));
		switch(OpNum)
		{
		case'1':
			Cipher();
			break;
		case '2':
			Decipher();
			break;
		case '3':
			return 0;
			break;
		default:
			break;
		}
	}
	return 0;
}

void Cipher()
{
	char OpNum,ch=0,OutFileName[255]="";
	int i,j,Value;
	int Text[2];
	int Key[2][2]={0};
	FILE *fin,*fout;
	while(1)
	{
		printf("������2x2������Ϊ������Կ��\n");
		for(i=0;i<2;i++)
			for(j=0;j<2;j++)
			{
				scanf("%d",&Key[i][j]);
				Key[i][j]=(26+Key[i][j]%26)%26;	//ȷ����Ϊ����
			}
			Value=((Key[0][0]*Key[1][1]-Key[0][1]*Key[1][0])%26+26)%26;
			if(1!=GCD(26,Value))
			{
				printf("���������Կ������(������ʽ��26������)������������!\n\n");
				continue;
			}
			break;
	}
	while(1)
	{
		printf("������Ҫ���������ļ�����������չ����\n");
		scanf("%s",OutFileName);
		if(NULL==(fout=fopen(OutFileName,"w")))
		{
			printf("�����ļ�ʧ�ܣ������ԣ�\n");
			continue;
		}
		break;
	}
	printf("��ѡ���������뷽ʽ��1-�Ӽ������� 2-���ļ�����\n\n");
	do
	{
		OpNum=_getch();
	}while('1'!=OpNum&&'2'!=OpNum);
	if('1'==OpNum)
	{
		printf("���������ģ���ctrl+z����:\n\n");
	}
	else 
	{
		char FileName[25];
		printf("�������ļ�����������չ����:\n\n");
		scanf("%s",FileName);
		fin=fopen(FileName,"r");
	}
	getchar();	//�����س�
	i=0;
	while(1)
	{
		ch='1'==OpNum?getchar():fgetc(fin);//����һ���ַ�
		if(ch>='a'&&ch<='z'||ch>='A'&&ch<='Z')
		{
			Text[i++]=ch-(ch>='a'?'a':'A');
		}
		if (2==i)
		{
			fputc((Text[0]*Key[0][0]+Text[1]*Key[1][0])%26+'a',fout);
			fputc((Text[0]*Key[0][1]+Text[1]*Key[1][1])%26+'a',fout);
			i=0;
		}
		if(EOF==ch)	break;
	}
	if(1==i)
	{
		printf("���ĳ���Ϊ��������������һλ��\n");
		while(1)
		{
			Text[1]=getchar();
			if (!(Text[1]>='a'&&Text[1]<='z'||Text[1]>='A'&&Text[1]<='Z'))
			{
				printf("��������ַ��������������룡\n");
				continue;
			}
			break;
		}
		Text[1]-=(Text[1]>='a'?'a':'A');
		fputc((Text[0]*Key[0][0]+Text[1]*Key[1][0])%26+'a',fout);
		fputc((Text[0]*Key[0][1]+Text[1]*Key[1][1])%26+'a',fout);
	}
	if('2'==OpNum)	fclose(fin);
	fclose(fout);
	printf("���ܽ���������\"%s\"��\n\n",OutFileName);
}

void Decipher()
{
	char OpNum,ch=0,OutFileName[255]="";
	int i,j,Value;
	int Text[2];
	int Key[2][2]={0},KeyInverse[2][2]={0};
	FILE *fin,*fout;
	while(1)
	{
		printf("������2x2����ļ�����Կ��\n");
		for(i=0;i<2;i++)
			for(j=0;j<2;j++)
			{
				scanf("%d",&Key[i][j]);
				Key[i][j]=(26+Key[i][j]%26)%26;	//ȷ����Ϊ����
			}
			Value=((Key[0][0]*Key[1][1]-Key[0][1]*Key[1][0])%26+26)%26;
			if(1!=GCD(26,Value))
			{
				printf("���������Կ������(������ʽ��26������)������������!\n\n");
				continue;
			}
			break;
	}
	InverseMatrix(Key,KeyInverse,Value);
	while(1)
	{
		printf("������Ҫ���������ļ�����������չ����\n");
		scanf("%s",OutFileName);
		if(NULL==(fout=fopen(OutFileName,"w")))
		{
			printf("�����ļ�ʧ�ܣ������ԣ�\n");
			continue;
		}
		break;
	}
	printf("��ѡ���������뷽ʽ��1-�Ӽ������� 2-���ļ�����\n\n");
	do
	{
		OpNum=_getch();
	}while('1'!=OpNum&&'2'!=OpNum);
	if('1'==OpNum)
	{
		printf("���������ģ���ctrl+z����:\n\n");
	}
	else 
	{
		char FileName[25];
		printf("�������ļ�����������չ����:\n\n");
		scanf("%s",FileName);
		fin=fopen(FileName,"r");
	}
	getchar();	//�����س�
	i=0;
	while(1)
	{
		ch='1'==OpNum?getchar():fgetc(fin);//����һ���ַ�
		if(ch>='a'&&ch<='z'||ch>='A'&&ch<='Z')
		{
			Text[i++]=ch-(ch>='a'?'a':'A');
		}
		if (2==i)
		{
			fputc((Text[0]*KeyInverse[0][0]+Text[1]*KeyInverse[1][0])%26+'a',fout);
			fputc((Text[0]*KeyInverse[0][1]+Text[1]*KeyInverse[1][1])%26+'a',fout);
			i=0;
		}

		if(EOF==ch)	break;
		
	}
	if(1==i)
	{
		printf("���ĳ���Ϊ��������������һλ��\n");
		while(1)
		{
			Text[1]=getchar();
			if (!(Text[1]>='a'&&Text[1]<='z'||Text[1]>='A'&&Text[1]<='Z'))
			{
				printf("��������ַ��������������룡\n");
				continue;
			}
			break;
		}
		Text[1]-=(Text[1]>='a'?'a':'A');
		fputc((Text[0]*KeyInverse[0][0]+Text[1]*KeyInverse[1][0])%26+'a',fout);
		fputc((Text[0]*KeyInverse[0][1]+Text[1]*KeyInverse[1][1])%26+'a',fout);
	}
	if('2'==OpNum) fclose(fin);
	fclose(fout);
	printf("���ܽ���������\"%s\"��\n\n",OutFileName);
}

/*
�������ܣ���2x2����������
����˵����	Matrix[][2]��Ҫ����ľ���
			Inverse[][2]��Matrix�������
			Value��Matrix����ʽ��ֵ
*/
void InverseMatrix(int Matrix[][2],int Inverse[][2],int Value)
{
	Value=Reverse[Value];	//��Value���������26����
	Inverse[0][0]=(Matrix[1][1]*Value)%26;	
	Inverse[0][1]=((26-Matrix[0][1])*Value)%26;
	Inverse[1][0]=((26-Matrix[1][0])*Value)%26;
	Inverse[1][1]=(Matrix[0][0]*Value)%26;
}

int GCD(int a,int b)
{
	int r;
	if(0==b)
		return a;
	do
	{
		r=a%b;
		a=b;
		b=r;
	}while(r!=0);
	return a;
}