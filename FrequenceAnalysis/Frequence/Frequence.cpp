// Frequence.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
typedef struct text
{
	char word[30];
	text* next;
}Text,*TextLink;

typedef struct threeletter	//三个字母组成的单词
{
	char word[4];
	int times;
	threeletter* next;
}ThreeLetter,*ThreeLetterLink;

typedef struct twoletter	//两个字母组成的单词
{
	char word[3];
	int times;
	twoletter* next;
}TwoLetter,*TwoLetterLink;
typedef struct letter	
{
	char c;//字母
	int num;//数目
}Letter;
void Output(TextLink head,char ReplaceTable[],FILE *fout);
void SetReplaceTable(char ReplaceTable[],const char LetterOrder[],const char WordFreqOrder[]);
bool SearchWord(const char word[]);

int main(int argc, _TCHAR* argv[])
{
	const char WordFreqOrder[]="etaoinshrdlcumwfgypbvkjxqz";//英文字母统计规律频率由高到低
	const int Three[][3]={{1,2,3},{1,3,2},{2,1,3},{2,3,1},{3,1,2},{3,2,1}};//3的全排列
	int i,j,k,l,TotalNum=0;		//总字母数
	Letter LetterNum[26];
	char OpNum,ch,LetterOrder[26]={0};
	bool MiFlag[26]={0};//已被确定的密文标记
	char ReplaceTable[26]="";//明密文字母替换表Replace[i]记录了字母i+'a'要被映射到的明文字母
	char tempStr[30]="";//临时字符串，多次用到
	char MaxThree[4]="",SecondThree[4]="";//频率最高的三字单词和频率次高的三字单词
	char MaxTwo[3]="",SecondTwo[3]="";//频率最高的两字单词和频率次高的两字单词
	int AfterE[26]={0};//E后面的单词统计
	FILE *fout,*fin;
	TextLink head=NULL,p=NULL,r=NULL;
	ThreeLetterLink threeHead=NULL,tp=threeHead;
	TwoLetterLink twoHead=NULL,twop=twoHead;
	int RightCnt=0,cnt=0,MaxMatch=0;
	int MaxThreeNum=0,SecondThreeNum=0,MaxTwoNum=0,SecondTwoNum=0,MaxAfterENum=0,MaxHeadNum=0,MaxTailNum=0;
	char MaxAfterE,MaxHead,MaxTail;
	int HeadLetter[26]={0},TailLetter[26]={0};
	printf("\t\t——————单表代替频率攻击——————\n\n");
	for (i=0;i<26;i++)
	{
		LetterNum[i].c=i+'a';
		LetterNum[i].num=0;
	}
	printf("请选择密文输入方式：1-从键盘输入 2-从文件读入\n\n");
	do
	{
		OpNum=_getch();
	}while(OpNum!='1'&&OpNum!='2');
	if('1'==OpNum)
	{
		printf("请输入密文，以ctrl+z结束：\n");	
	}
	else
	{
		while(1)
		{
			char FileName[255]="";
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
	}
	fout=fopen("result.txt","w");
	i=0;
	while(1)
	{
		ch='1'==OpNum?getchar():fgetc(fin);
		if(EOF==ch) break;
		if (ch>='A'&&ch<='Z')
		{
			ch=ch-'A'+'a';//全转换成小写方便后续操作
		}
		if(ch>='a'&&ch<='z')
		{
			LetterNum[ch-'a'].num++;
			TotalNum++;
			tempStr[i++]=ch;
		}
		else
		{
			if (i>0)
			{
				tempStr[i]='\0';
				HeadLetter[tempStr[0]-'a']++;
				TailLetter[tempStr[i-1]-'a']++;
				if (3==i)//记录三个字母的单词
				{
					if(NULL==threeHead)
					{
						threeHead=(ThreeLetterLink)malloc(sizeof(ThreeLetter));
						strcpy(threeHead->word,tempStr);
						threeHead->times=1;
						threeHead->next=NULL;
					}
					else
					{
						ThreeLetterLink tp=NULL,tr=NULL;
						tp=threeHead;
						while(tp)
						{
							if (0==strcmp(tempStr,tp->word))
							{
								tp->times++;
								if (tp->times>MaxThreeNum)
								{
									MaxThreeNum=tp->times;
									strcpy(MaxThree,tempStr);
								}
								break;
							}
							tr=tp;
							tp=tp->next;
						}
						if (NULL==tp)
						{
							tp=(ThreeLetterLink)malloc(sizeof(ThreeLetter));
							strcpy(tp->word,tempStr);
							tp->times=1;
							tp->next=NULL;
							tr->next=tp;
						}
					}
				}
				if (2==i)//记录三个字母的单词
				{
					if(NULL==twoHead)
					{
						twoHead=(TwoLetterLink)malloc(sizeof(TwoLetter));
						strcpy(twoHead->word,tempStr);
						twoHead->times=1;
						twoHead->next=NULL;
					}
					else
					{
						TwoLetterLink tp=NULL,tr=NULL;
						tp=twoHead;
						while(tp)
						{
							if (0==strcmp(tempStr,tp->word))
							{
								tp->times++;
								if (tp->times>MaxTwoNum)
								{
									MaxTwoNum=tp->times;
									strcpy(MaxTwo,tempStr);
								}
								break;
							}
							tr=tp;
							tp=tp->next;
						}
						if (NULL==tp)
						{
							tp=(TwoLetterLink)malloc(sizeof(TwoLetter));
							strcpy(tp->word,tempStr);
							tp->times=1;
							tp->next=NULL;
							tr->next=tp;
						}
					}
				}
				i=0;
				if(NULL==head)
				{
					head=(TextLink)malloc(sizeof(Text));
					strcpy(head->word,tempStr);
					head->next=NULL;
					p=head;
				}
				else
				{
					p=(TextLink)malloc(sizeof(Text));
					strcpy(p->word,tempStr);
					p->next=NULL;
					r->next=p;
				}
				r=p;
			}
		}
	}
	tp=threeHead;
	while(tp)//找出频率次高的三字词
	{
		if (tp->times>SecondThreeNum&&strcmp(MaxThree,tp->word))
		{
			SecondThreeNum=tp->times;
			strcpy(SecondThree,tp->word);
		}
		tp=tp->next;
	}
	twop=twoHead;
	while(twop)//找出频率次高的双字词
	{
		if (twop->times>SecondTwoNum&&strcmp(MaxTwo,twop->word))
		{
			SecondTwoNum=twop->times;
			strcpy(SecondTwo,twop->word);
		}
		twop=twop->next;
	}
	MiFlag[MaxThree[0]-'a']=1;//确定the
	MiFlag[MaxThree[1]-'a']=1;
	MiFlag[MaxThree[2]-'a']=1;
	LetterOrder[1]=MaxThree[0];
	LetterOrder[7]=MaxThree[1];
	LetterOrder[0]=MaxThree[2];

	p=head;
	while(p)
	{
		for (i=0;p->word[i+1];i++)
		{
			if (LetterOrder[0]==p->word[i])
			{
				AfterE[p->word[i+1]-'a']++;//找e后面字母频率最高的
				if (AfterE[p->word[i+1]-'a']>MaxAfterENum&&!MiFlag[p->word[i+1]-'a'])
				{
					MaxAfterENum=AfterE[p->word[i+1]-'a'];
					MaxAfterE=p->word[i+1];
				}
			}
		}
		p=p->next;
	}
	MiFlag[MaxAfterE-'a']=1;
	LetterOrder[8]=MaxAfterE;//认为e后面频率最高的是r

	//频率次高的三字母单词可能是and 或者 for 或者 are

	if (LetterNum[SecondThree[0]-'a'].num>TotalNum/20)//频率次高的三字母单词首字母频率超过5%就当作是a而不是f
	{
		MiFlag[SecondThree[0]-'a']=1;
		LetterOrder[2]=SecondThree[0];
		if (SecondThree[2]==MaxThree[2])//认为频率次高三字母单词是"are"
		{
			MiFlag[SecondThree[1]-'a']=1;
			LetterOrder[8]=SecondThree[1];
		}
		else//认为频率次高三字母单词是"and"
		{
			MiFlag[SecondThree[1]-'a']=1;
			MiFlag[SecondThree[2]-'a']=1;
			LetterOrder[5]=SecondThree[1];
			LetterOrder[9]=SecondThree[2];
		}
	}
	else//否则当作for
	{
		MiFlag[SecondThree[0]-'a']=1;
		MiFlag[SecondThree[1]-'a']=1;
		MiFlag[SecondThree[2]-'a']=1;
		LetterOrder[15]=SecondThree[0];
		LetterOrder[3]=SecondThree[1];
		LetterOrder[8]=SecondThree[2];
	}
	//频率最高的双字母单词可能是to或者of或者in
	if (MaxTwo[0]==MaxThree[0]&&0==LetterOrder[3])//现已知MaxThree是"the"，所以如果MaxTwo的首字母与它相同则MaxTwo为"to"
	{
		MiFlag[MaxTwo[1]-'a']=1;
		LetterOrder[3]=MaxTwo[1];
	}
	else//否则的话根据第二个字母判断，因为字母f与n的频率应该相差较大
	{
		if (0==LetterOrder[5]&&LetterNum[MaxTwo[1]-'a'].num>=TotalNum/20)//第二个字母频率超过%5就认为是n
		{
			MiFlag[MaxTwo[0]-'a']=1;
			MiFlag[MaxTwo[1]-'a']=1;
			LetterOrder[4]=MaxTwo[0];
			LetterOrder[5]=MaxTwo[1];
		}
		else if(0==LetterOrder[3]&&0==LetterOrder[15])//否则认为是f
		{
			MiFlag[MaxTwo[0]-'a']=1;
			MiFlag[MaxTwo[1]-'a']=1;
			LetterOrder[3]=MaxTwo[0];
			LetterOrder[15]=MaxTwo[1];
		}
	}
	//频率次高的双字母单词可能是to或者of或者in
	if (0==LetterOrder[3]&&SecondTwo[0]==MaxThree[0])//现已知MaxThree是"the"，所以如果MaxTwo的首字母与它相同则MaxTwo为"to"
	{
		MiFlag[SecondTwo[1]-'a']=1;
		LetterOrder[3]=SecondTwo[1];
	}
	else//否则的话根据第二个字母判断，因为字母f与n的频率应该相差较大
	{
		if (0==LetterOrder[4]&&0==LetterOrder[5]&&LetterNum[SecondTwo[1]-'a'].num>=TotalNum/20)//第二个字母频率超过%5就认为是n
		{
			MiFlag[SecondTwo[0]-'a']=1;
			MiFlag[SecondTwo[1]-'a']=1;
			LetterOrder[4]=SecondTwo[0];
			LetterOrder[15]=SecondTwo[1];
		}
		else if(0==LetterOrder[3]&&0==LetterOrder[15])//否则认为是f
		{
			MiFlag[SecondTwo[0]-'a']=1;
			MiFlag[SecondTwo[1]-'a']=1;
			LetterOrder[3]=SecondTwo[0];
			LetterOrder[15]=SecondTwo[1];
		}
	}
	for (i=0;i<26;i++)
	{
		if (!MiFlag[i]&&LetterNum[i].num>TotalNum/20)//找频率最高的首尾字母中频率大于5%的
		{
			if (HeadLetter[i]>MaxHeadNum)
			{
				MaxHeadNum=HeadLetter[i];
				MaxHead=i+'a';
			}
			if (TailLetter[i]>MaxTailNum)
			{
				MaxTailNum=TailLetter[i];
				MaxTail=i+'a';
			}
		}	
	}
	if (MaxTail==MaxHead)//频率最高的首尾字母相同，则认为是s
	{
		MiFlag[MaxTail-'a']=1;
		LetterOrder[6]=MaxTail;
	}
	//以上工作基本确定了大概率和较大概率字母的对应，之后只需对较低概率字母集内进行代换
	for(i=0;i<25;i++)
	{
		for(j=0;j<25-i;j++)//泡排序
		{
			if(LetterNum[j].num<LetterNum[j+1].num)
			{
				Letter temp;
				temp=LetterNum[j];					//按字母频率由高到低排列字母，以对应到字母频率表
				LetterNum[j]=LetterNum[j+1];
				LetterNum[j+1]=temp;
			}
		}
	}
	printf("共有%d个字母\n",TotalNum);
	printf("各个字母频率如下：\n");
	for (i=0;i<26;i++)
	{
		printf("%c:%.8lf\t",LetterNum[i].c,(double)LetterNum[i].num/TotalNum);
	}
	printf("\n正在解密，请稍等……");
	for (i=0,j=0;i<26,j<26;)
	{
		while(LetterOrder[i]&&i<26)
			i++;
		while(MiFlag[LetterNum[j].c-'a']&&j<26)
			j++;
		LetterOrder[i]=LetterNum[j].c;
		MiFlag[LetterNum[j].c-'a']=1;
	}
	for (i=9;i<25;i++)
	{
		tempStr[i]=LetterOrder[i];//记录下初始时LetterOrder第十个字母及后面的字母
	}
	for(i=0;i<2;i++)
	{
		for (j=0;j<2;j++)
		{
			for (k=0;k<6;k++)
			{
				for (l=0;l<6;l++)
				{
					char temp[30]="";
					int index=0,WordNum=0,RightCnt=0;
					LetterOrder[9]=tempStr[9+i];
					LetterOrder[10]=tempStr[10-i];

					LetterOrder[11]=tempStr[11+j];
					LetterOrder[12]=tempStr[12-j];

					LetterOrder[13]=tempStr[Three[k][0]+12];
					LetterOrder[14]=tempStr[Three[k][1]+12];
					LetterOrder[15]=tempStr[Three[k][2]+12];

					LetterOrder[16]=tempStr[Three[l][0]+15];
					LetterOrder[17]=tempStr[Three[l][1]+15];
					LetterOrder[18]=tempStr[Three[l][2]+15];
					SetReplaceTable(ReplaceTable,LetterOrder,WordFreqOrder);
					p=head;
					while(p&&WordNum<100)//查找100个单词
					{
						if (strlen(p->word)<4)//跳过长度小于4的单词
						{
							p=p->next;
							continue;
						}
						for (index=0;p->word[index];index++)
						{
							temp[index]=ReplaceTable[p->word[index]-'a'];
						}
						temp[index]='\0';
						if (SearchWord(temp))
						{
							RightCnt++;
						}
						WordNum++;
						p=p->next;
					}
					if (RightCnt>MaxMatch)
					{
						fprintf(fout,"可能结果%d：\n",++cnt);
						Output(head,ReplaceTable,fout);
						fprintf(fout,"\n");
						MaxMatch=RightCnt;
					}					
				}
			}
		}
	}	
	printf("\n可能的结果已输出至\"result.txt\"文件中\n\n");
	if('2'==OpNum)	fclose(fin); 
	fclose(fout);
	while(head)//销毁链表
	{
		p=head;
		head=head->next;
		free(p);
	}
	while(twoHead)
	{
		twop=twoHead;
		twoHead=twoHead->next;
		free(twop);
	}
	while(threeHead)
	{
		tp=threeHead;
		threeHead=threeHead->next;
		free(tp);
	}
	system("pause");
	return 0;
}

void Output(TextLink head,char ReplaceTable[],FILE *fout)
{
	int i;
	TextLink p=head;
	while(p)
	{
		for (i=0;p->word[i];i++)
		{
			fputc(ReplaceTable[p->word[i]-'a'],fout);
		}
		fputc(' ',fout);
		p=p->next;
	}
	fputc('\n',fout);
}

//根据字母顺序设置替换表
void SetReplaceTable(char ReplaceTable[],const char LetterOrder[],const char WordFreqOrder[])
{
	int i;
	for (i=0;i<26;i++)
	{
		ReplaceTable[LetterOrder[i]-'a']=WordFreqOrder[i];
	}
}
bool SearchWord(const char word[])
{
	FILE *fin;
	char FileName[10]="dic-*.txt";
	char Dic[5000][30]={0};
	int low,high,mid,i=0;
	FileName[4]=word[0];//确定要查找的文件名
	fin=fopen(FileName,"r");
	while(EOF!=fscanf(fin,"%s",Dic[i]))
		i++;
	low=0;
	high=i;
	while(low<=high)
	{
		mid=(low+high)/2;
		if (0==strcmp(Dic[mid],word))
		{
			fclose(fin);
			return 1;
		}
		else if (strcmp(Dic[mid],word)>0)
			high=mid-1;
		else
			low=mid+1;
	}
	fclose(fin);
	return 0;
}
