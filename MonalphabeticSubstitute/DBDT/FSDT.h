#ifndef FSDT_H
#define FSDT_H

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#define MAXQ 1000
typedef struct text
{
	char c;
	text* next;
}Text,*TextLink;
const int Key1[]={1,3,5,7,9,11,15,17,19,21,23,25};	//乘法代替密码的可用密钥，即小于26且与26互素的正整数
const int Key1_R[]={0,1,0,9,0,21,0,15,0,3,0,19,0,0,0,7,0,23,0,11,0,5,0,17,0,25};//每个Key1对应的模26的逆
int GCD(int a,int b);//求最大公约数
void Create_Total_Key();	//生成以q为模的全部可用密钥
void Create_Random_Key();	//随机生成可用密钥
void Cipher();				//加密
void Decipher();			//解密
void FSDT();//仿射代替密码主体函数
#endif