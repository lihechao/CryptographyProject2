#include"stdafx.h"

#include"MYDY.h"
void MYDY()
{
	
	while(1)
	{
		printf("\t\t�����������������������֮��Կ�������롪����������\n\n");
		printf("����������ţ�1-���������Կ 2-���� 3-���� 4-���� 5-����\n\n");
		char OpNum;	//������
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
	Lenth=rand()%26+1;//�����Կ����
	printf("\n�����Կ���");
	
	for(i=0;i<Lenth;i++)
	{
		do
		{
			Key[i]=rand()%26;
		}while(Choosed[Key[i]]);
		printf("%c",Key[i]+'A');
		Choosed[Key[i]]=1;
	}
	printf("\n\n�����Ķ��ձ�\n");
	printf("\n���ģ�");
	for(i=0;i<26;i++)
	{
		printf("%c ",i+'a');
	}
	printf("\n���ģ�");
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
	printf("��������Կ���\n");
	while(1)
	{
		if('\n'==(ch=getchar()))
			break;
		if (ch>='a'&&ch<='z')
		{
			ch=ch-'a'+'A';//ȫ��ת���ɴ�д
		}
		if(!(ch>='A'&&ch<='Z'))
		{
			printf("���������Կ�����������������룡\n\n");
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
			ch=KeyTable[ch-'a'];
		}
		else if(ch>='A'&&ch<='Z')
		{
			ch=KeyTable[ch-'A'];
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
		fprintf(fout,"%c ",KeyTable[i]);
	}
	if('2'==OpNum)	fclose(fin);
	fclose(fout);
	printf("���ܺ�������������\"%s\"�ļ���\n\n",FileName);
}

void Decipher_M()
{
	char OpNum,ch,FileName[255],KeyTable[26]="";
	FILE *fin,*fout;
	int Choosed[26]={0},i=0,j=0;
	printf("��������Կ���\n");
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
			printf("���������Կ�����������������룡\n\n");
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
			ch=KeyTable[ch-'a'];
		}
		else if(ch>='A'&&ch<='Z')
		{
			ch=KeyTable[ch-'A'];
		}
		fputc(ch,fout);
	}
	fprintf(fout,"\n�����Ķ��ձ�\n");
	fprintf(fout,"\n���ģ�");
	for(i=0;i<26;i++)
	{
		fprintf(fout,"%c ",i+'A');
	}
	fprintf(fout,"\n���ģ�");
	for(i=0;i<26;i++)
	{
		fprintf(fout,"%c ",KeyTable[i]);
	}
	if('2'==OpNum)	fclose(fin);
	fclose(fout);
	printf("���ܺ�������������\"%s\"�ļ���\n\n",FileName);
}