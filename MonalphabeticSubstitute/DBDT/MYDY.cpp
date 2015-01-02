#include"stdafx.h"

#include"MYDY.h"
void MYDY()
{
	
	while(1)
	{
		printf("\t\t——————单表代替体制之密钥短语密码——————\n\n");
		printf("请输入操作号：1-生成随机密钥 2-加密 3-解密 4-清屏 5-返回\n\n");
		char OpNum;	//操作号
		do
		{
			OpNum=_getch();
		}while(!(OpNum>='1'&&OpNum<='5'));
		switch(OpNum)
		{
		case '1':
			Create_Random_Key_M();
			break;
		case '2':
			Cipher_M();
			break;
		case '3':
			Decipher_M();
			break;
		case '4':
			system("cls");
			break;
		case '5':
			return;
			break;
		default:
			break;
		}
	}
}

void Create_Random_Key_M()
{
	int Choosed[26]={0},i;
	int Key[26],Lenth;
	srand((unsigned int)time(NULL));
	Lenth=rand()%26+1;//随机密钥长度
	printf("\n随机密钥短语：");
	
	for(i=0;i<Lenth;i++)
	{
		do
		{
			Key[i]=rand()%26;
		}while(Choosed[Key[i]]);
		printf("%c",Key[i]+'A');
		Choosed[Key[i]]=1;
	}
	printf("\n\n明密文对照表：\n");
	printf("\n明文：");
	for(i=0;i<26;i++)
	{
		printf("%c ",i+'a');
	}
	printf("\n密文：");
	for(i=0;i<Lenth;i++)
	{
		printf("%c ",Key[i]+'A');
	}
	for(i=0;i<26;i++)
	{
		if(!Choosed[i])
			printf("%c ",i+'A');
	}
	printf("\n\n");
}

void Cipher_M()
{
	char OpNum,ch,FileName[255],KeyTable[26]="";
	FILE *fin,*fout;
	int Choosed[26]={0},i=0,j=0;
	printf("请输入密钥短语：\n");
	while(1)
	{
		if('\n'==(ch=getchar()))
			break;
		if (ch>='a'&&ch<='z')
		{
			ch=ch-'a'+'A';//全部转换成大写
		}
		if(!(ch>='A'&&ch<='Z'))
		{
			printf("您输入的密钥短语有误，请重新输入！\n\n");
			fflush(stdin);
			for(j=0;j<26;j++)
				Choosed[j]=0;
			i=0;
			continue;
		}
		if(!Choosed[ch-'A'])
		{
			KeyTable[i++]=ch;
			Choosed[ch-'A']=1;
		}
	}
	for(j=0;j<26;j++)
	{
		if(!Choosed[j])
			KeyTable[i++]=j+'A';
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
			ch=KeyTable[ch-'a'];
		}
		else if(ch>='A'&&ch<='Z')
		{
			ch=KeyTable[ch-'A'];
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
		fprintf(fout,"%c ",KeyTable[i]);
	}
	if('2'==OpNum)	fclose(fin);
	fclose(fout);
	printf("加密后的密文已输出至\"%s\"文件中\n\n",FileName);
}

void Decipher_M()
{
	char OpNum,ch,FileName[255],KeyTable[26]="";
	FILE *fin,*fout;
	int Choosed[26]={0},i=0,j=0;
	printf("请输入密钥短语：\n");
	while(1)
	{
		if('\n'==(ch=getchar()))
			break;
		if (ch>='a'&&ch<='z')
		{
			ch=ch-'a'+'A';
		}
		if(!(ch>='A'&&ch<='Z'))
		{
			printf("您输入的密钥短语有误，请重新输入！\n\n");
			fflush(stdin);
			for(j=0;j<26;j++)
				Choosed[j]=0;
			i=0;
			continue;
		}
		if(!Choosed[ch-'A'])
		{
			Choosed[ch-'A']=1;
			KeyTable[ch-'A']='a'+i;
			i++;
		}
		
	}
	for(j=0;j<26;j++)
	{
		if(!Choosed[j])
			KeyTable[j]='a'+(i++);
	}
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
			ch=KeyTable[ch-'a'];
		}
		else if(ch>='A'&&ch<='Z')
		{
			ch=KeyTable[ch-'A'];
		}
		fputc(ch,fout);
	}
	fprintf(fout,"\n明密文对照表：\n");
	fprintf(fout,"\n密文：");
	for(i=0;i<26;i++)
	{
		fprintf(fout,"%c ",i+'A');
	}
	fprintf(fout,"\n明文：");
	for(i=0;i<26;i++)
	{
		fprintf(fout,"%c ",KeyTable[i]);
	}
	if('2'==OpNum)	fclose(fin);
	fclose(fout);
	printf("解密后的明文已输出至\"%s\"文件中\n\n",FileName);
}