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
const int Key1[]={1,3,5,7,9,11,15,17,19,21,23,25};	//�˷���������Ŀ�����Կ����С��26����26���ص�������
const int Key1_R[]={0,1,0,9,0,21,0,15,0,3,0,19,0,0,0,7,0,23,0,11,0,5,0,17,0,25};//ÿ��Key1��Ӧ��ģ26����
int GCD(int a,int b);//�����Լ��
void Create_Total_Key();	//������qΪģ��ȫ��������Կ
void Create_Random_Key();	//������ɿ�����Կ
void Cipher();				//����
void Decipher();			//����
void FSDT();//��������������庯��
#endif