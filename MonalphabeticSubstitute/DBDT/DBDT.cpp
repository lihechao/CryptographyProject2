
#include "stdafx.h"

#include"FSDT.h"
#include"MYDY.h"
int main(int argc, _TCHAR* argv[])
{
	
	while(1)
	{
		printf("\t\t��������������������������ơ���������������\n\n");
		printf("����������ţ�1-����������� 2-��Կ�������� 3-�˳�\n\n");
		char OpNum;	//������
		do
		{
			OpNum=_getch();
		}while(!(OpNum>='1'&&OpNum<='3'));
		switch(OpNum)
		{
		case '1':
			FSDT();
			break;
		case '2':
			MYDY();
			break;
		case '3':
			exit(0);
			break;
		default:
			break;
		}
	}
	return 0;
}

