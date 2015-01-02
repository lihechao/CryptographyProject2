// FSDT.cpp : 定义控制台应用程序的入口点。
//
// FSDT.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"FSDT.h"
void FSDT()
{
	
	while(1)
	{
		printf("\t\t—————单表代替体制之仿射代替密码—————\n\n");
		printf("请输入操作号：1-生成随机密钥 2-查看全部可用密钥 3-加密 4-解密 5-清屏 6-返回\n\n");
		char OpNum;	//操作号
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
			printf("加密变换：E(m)=(mk1+k0) mod 26\n\n");
			Cipher();
			break;
		case '4':
			printf("解密变换：D(c)=(c-k0)k1^-1 mod 26\n\n");
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
	printf("请输入密钥空间元素个数q（1000以内）:\n");
	while(1)
	{
		scanf("%d",&q);
		if (q>1000)
		{
			printf("密钥空间过大！请重新输入！\n");
			continue;
		}
		break;
	}
	fp=fopen("Key.txt","w");
	for(i=1;i<q;i++)
	{
		if(1==GCD(i,q))
		{
			K1[K1Num++]=i;			//记录可用k1
		}
	}
	fprintf(fp,"密钥格式：[k1,k0]\n");
	for(i=0;i<q;i++)
	{
		for(j=0;j<K1Num;j++)
		{
			if(!(0==i&&1==K1[j]))
				fprintf(fp,"No.%d\t[%d,%d]\n",++k,K1[j],i);
		}
	}
	printf("全部%d个可用密钥已生成到\"Key.txt\"文件中：\n\n",k);
	fclose(fp);
}

void Create_Random_Key()
{
	int RandK1,RandK0;
	int i,q,K1Num=0,K1[MAXQ];
	srand((unsigned int)time(NULL));
	printf("请输入密钥空间元素个数q（1000以内）:\n");
	while(1)
	{
		scanf("%d",&q);
		if (q>1000)
		{
			printf("密钥空间过大！请重新输入！\n");
			continue;
		}
		break;
	}
	if(q<=1)
	{
		printf("没有可用的密钥！\n\n");
		fflush(stdin);
		return;
	}
	for(i=1;i<q;i++)
	{
		if(1==GCD(i,q))
		{
			K1[K1Num++]=i;			//记录可用k1
		}
	}
	do
	{
		RandK1=rand()%K1Num;
		RandK0=rand()%q;
	}while(0==RandK0&&1==K1[RandK1]);
	printf("随机密钥[k1,k0]：[%d,%d]\n\n",K1[RandK1],RandK0);
}

void Cipher()
{
	int k1,k0,i;
	char OpNum,ch;
	char FileName[255];
	FILE *fin,*fout;
	TextLink head=NULL,p=NULL,r=NULL;
	printf("请输入加密密钥k1,k0,以空白字符分隔：\n\n");
	while(1)
	{
		scanf("%d%d",&k1,&k0);
		if(1==GCD(k1,26)&&0!=k0&&k1>0&&k0>=0)
			break;
		else
			printf("您输入的密钥不可用，请重新输入！\n\n");
		fflush(stdin);
	}
	printf("选择明文输入方式：1-键盘输入 2-从文件读入\n\n");
	do
	{
		OpNum=_getch();
	}while(OpNum!='1'&&OpNum!='2');
	if('1'==OpNum)
	{
		printf("请输入要输出的文件名（包括扩展名）:\n");
		scanf("%s",FileName);
		printf("请输入明文，以ctrl+z结束：\n");
	}
	else
	{
		while(1)
		{
			printf("请输入文件名（包含扩展名）：\n");
			scanf("%s",FileName);
			fin=fopen(FileName,"r");
			if(NULL==fin)
			{
				printf("打开文件失败，请重试！\n\n");
				continue;
			}
			break;
		}
		printf("请输入要输出的文件名（包括扩展名）:\n");
		scanf("%s",FileName);
	}

	fout=fopen(FileName,"w");
	getchar();//跳过回车
	while(1)
	{
		ch='1'==OpNum?getchar():fgetc(fin);
		if(EOF==ch)	break;
		if(ch>='a'&&ch<='z')
		{
			ch=((ch-'a')*k1+k0)%26+'a';			//大小写不变
			//ch=((ch-'a')*k1+k0)%26+'A';			//全转成大写
		}
		else if(ch>='A'&&ch<='Z')
		{
			ch=((ch-'A')*k1+k0)%26+'A';			//大小写不变
			//ch=((ch-'A')*k1+k0)%26+'a';			//全转成小写
		}
		fputc(ch,fout);
	}
	fprintf(fout,"\n明密文对照表：\n");
	fprintf(fout,"\n明文：");
	for(i=0;i<26;i++)
	{
		fprintf(fout,"%c ",i+'a');
	}
	fprintf(fout,"\n密文：");
	for(i=0;i<26;i++)
	{
		fprintf(fout,"%c ",(i*k1+k0)%26+'A');
	}
	if('2'==OpNum)	fclose(fin);
	fclose(fout);
	printf("加密后的密文已输出至\"%s\"文件中\n\n",FileName);
}

void Decipher()
{
	int k1,k0,i;
	char OpNum,ch,FileName[255];
	FILE *fp;
	TextLink head=NULL,p=NULL,r=NULL;
	printf("选择密文输入方式：1-键盘输入 2-从文件读入\n\n");
	do
	{
		OpNum=_getch();
	}while(OpNum!='1'&&OpNum!='2');
	if('1'==OpNum)
	{
		printf("请输入要输出的文件名（包括扩展名）:\n");
		scanf("%s",FileName);
		printf("请输入密文，以ctrl+z结束：\n");
	}
	else
	{
		while(1)
		{
			printf("请输入文件名（包含扩展名）：\n");
			scanf("%s",FileName);
			fp=fopen(FileName,"r");
			if(NULL==fp)
			{
				printf("打开文件失败，请重试！\n\n");
				continue;
			}
			break;
		}
		printf("请输入要输出的文件名（包括扩展名）:\n");
		scanf("%s",FileName);
	}
	getchar();//跳过回车
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
	printf("是否已知密钥？Y/N\n");
	do
	{
		ch=getchar();
	}while(ch!='Y'&&ch!='y'&&ch!='N'&&ch!='n');
	if('2'==OpNum)	fclose(fp);
	fp=fopen(FileName,"w");
	if('Y'==ch||'y'==ch)		//已知密钥
	{
		printf("请输入密钥k1,k0,以空白字符分隔：\n\n");
		scanf("%d%d",&k1,&k0);
		p=head;
		while(p)
		{
			if(p->c>='a'&&p->c<='z')
			{
				p->c=((p->c-'a')-k0+26)*Key1_R[k1]%26+'a';			//大小写不变
				//ch=((ch-'a')-k0+26)*Key1_R[k1]%26+'A';			//全转成大写
			}
			else if(p->c>='A'&&p->c<='Z')
			{
				p->c=((p->c-'A')-k0+26)*Key1_R[k1]%26+'A';			//大小写不变
				//ch=((ch-'A')-k0+26)*Key1_R[k1]%26+'a';			//全转成小写
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
		fprintf(fp,"\n明密文对照表：\n");
		fprintf(fp,"\n密文：");
		for(i=0;i<26;i++)
		{
			fprintf(fp,"%c ",i+'A');
		}
		fprintf(fp,"\n明文：");
		for(i=0;i<26;i++)
		{
			fprintf(fp,"%c ",(i-k0+26)*Key1_R[k1]%26+'a');
		}
		fclose(fp);
		printf("解密后的明文已输出至\"%s\"文件中\n\n",FileName);
	}
	else		//未知密钥
	{
		int i,j,k=0;
		char temp;
		for(i=0;i<12;i++)
		{
			k1=Key1[i];
			for(j=0;j<26;j++)
			{
				k0=j;
				fprintf(fp,"可能结果%d:\n",++k);
				p=head;
				while(p)
				{
					temp=p->c;
					if(temp>='a'&&temp<='z')
					{
						temp=((temp-'a')-k0+26)*Key1_R[k1]%26+'a';			//大小写不变
						//temp=((temp-'a')-k0+26)*Key1_R[k1]%26+'A';			//全转成大写
					}
					else if(temp>='A'&&temp<='Z')
					{
						temp=((temp-'A')-k0+26)*Key1_R[k1]%26+'A';			//大小写不变
						//temp=((temp-'A')-k0+26)*Key1_R[k1]%26+'a';			//全转成小写
					}
					fputc(temp,fp);
					p=p->next;
				}
				fputc('\n',fp);
			}
		}
		printf("全部可能结果已输出到\"%s\"文件中\n\n",FileName);
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