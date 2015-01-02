
#include "stdafx.h"

#include"FSDT.h"
#include"MYDY.h"
int main(int argc, _TCHAR* argv[])
{
	
	while(1)
	{
		printf("\t\t¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ªµ¥±í´úÌæÌåÖÆ¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª\n\n");
		printf("ÇëÊäÈë²Ù×÷ºÅ£º1-·ÂÉä´úÌæÃÜÂë 2-ÃÜÔ¿¶ÌÓïÃÜÂë 3-ÍË³ö\n\n");
		char OpNum;	//²Ù×÷ºÅ
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

