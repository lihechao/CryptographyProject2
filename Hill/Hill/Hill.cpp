// Hill.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<stdio.h>
#include<conio.h>
void Cipher();
void Decipher();
void InverseMatrix(int Matrix[][2],int Inverse[][2],int Value);
int GCD(int a,int b);
const int Reverse[]={0,1,0,9,0,21,0,15,0,3,0,19,0,0,0,7,0,23,0,11,0,5,0,17,0,25};//每个下标对应的模26的逆
int main()
{
	char OpNum;
	printf("\t\t———————Hill密码加解密工具————————\n\n");
	while(1)
	{
		printf("请输入操作号：1-加密 2-解密 3-退出\n\n");
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
		printf("请输入2x2矩阵作为加密密钥：\n");
		for(i=0;i<2;i++)
			for(j=0;j<2;j++)
			{
				scanf("%d",&Key[i][j]);
				Key[i][j]=(26+Key[i][j]%26)%26;	//确保都为正数
			}
			Value=((Key[0][0]*Key[1][1]-Key[0][1]*Key[1][0])%26+26)%26;
			if(1!=GCD(26,Value))
			{
				printf("您输入的密钥不可用(其行列式与26不互质)，请重新输入!\n\n");
				continue;
			}
			break;
	}
	while(1)
	{
		printf("请输入要输出结果的文件名（包括扩展名）\n");
		scanf("%s",OutFileName);
		if(NULL==(fout=fopen(OutFileName,"w")))
		{
			printf("创建文件失败，请重试！\n");
			continue;
		}
		break;
	}
	printf("请选择明文输入方式：1-从键盘输入 2-从文件读入\n\n");
	do
	{
		OpNum=_getch();
	}while('1'!=OpNum&&'2'!=OpNum);
	if('1'==OpNum)
	{
		printf("请输入明文，以ctrl+z结束:\n\n");
	}
	else 
	{
		char FileName[25];
		printf("请输入文件名（包括扩展名）:\n\n");
		scanf("%s",FileName);
		fin=fopen(FileName,"r");
	}
	getchar();	//跳过回车
	i=0;
	while(1)
	{
		ch='1'==OpNum?getchar():fgetc(fin);//读入一个字符
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
		printf("明文长度为奇数，请再输入一位：\n");
		while(1)
		{
			Text[1]=getchar();
			if (!(Text[1]>='a'&&Text[1]<='z'||Text[1]>='A'&&Text[1]<='Z'))
			{
				printf("您输入的字符有误，请重新输入！\n");
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
	printf("加密结果已输出至\"%s\"中\n\n",OutFileName);
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
		printf("请输入2x2矩阵的加密密钥：\n");
		for(i=0;i<2;i++)
			for(j=0;j<2;j++)
			{
				scanf("%d",&Key[i][j]);
				Key[i][j]=(26+Key[i][j]%26)%26;	//确保都为正数
			}
			Value=((Key[0][0]*Key[1][1]-Key[0][1]*Key[1][0])%26+26)%26;
			if(1!=GCD(26,Value))
			{
				printf("您输入的密钥不可用(其行列式与26不互质)，请重新输入!\n\n");
				continue;
			}
			break;
	}
	InverseMatrix(Key,KeyInverse,Value);
	while(1)
	{
		printf("请输入要输出结果的文件名（包括扩展名）\n");
		scanf("%s",OutFileName);
		if(NULL==(fout=fopen(OutFileName,"w")))
		{
			printf("创建文件失败，请重试！\n");
			continue;
		}
		break;
	}
	printf("请选择密文输入方式：1-从键盘输入 2-从文件读入\n\n");
	do
	{
		OpNum=_getch();
	}while('1'!=OpNum&&'2'!=OpNum);
	if('1'==OpNum)
	{
		printf("请输入密文，以ctrl+z结束:\n\n");
	}
	else 
	{
		char FileName[25];
		printf("请输入文件名（包括扩展名）:\n\n");
		scanf("%s",FileName);
		fin=fopen(FileName,"r");
	}
	getchar();	//跳过回车
	i=0;
	while(1)
	{
		ch='1'==OpNum?getchar():fgetc(fin);//读入一个字符
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
		printf("密文长度为奇数，请再输入一位：\n");
		while(1)
		{
			Text[1]=getchar();
			if (!(Text[1]>='a'&&Text[1]<='z'||Text[1]>='A'&&Text[1]<='Z'))
			{
				printf("您输入的字符有误，请重新输入！\n");
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
	printf("解密结果已输出至\"%s\"中\n\n",OutFileName);
}

/*
函数功能：求2x2矩阵的逆矩阵
参数说明：	Matrix[][2]：要求逆的矩阵
			Inverse[][2]：Matrix的逆矩阵
			Value：Matrix行列式的值
*/
void InverseMatrix(int Matrix[][2],int Inverse[][2],int Value)
{
	Value=Reverse[Value];	//将Value变成它关于26的逆
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