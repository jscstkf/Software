// �û�����
// ���£�2014-07-10
//###########################################################################
//
// �ļ�:	USERS_Cpld.c
//
// ����:	���ڶ�дCPLD
//
// ����:	
//				
//########################################################################### 
#include "DSP2833x_Device.h"     
#include "DSP2833x_Examples.h"
#include "USERS_Cpld.h"

extern union  FLAG_SYSTEM_RUNERR 		FlagSysRunErr;
/*---------------------------------------------------------------------
����ԭ�ͣ�void ReadCPLDSTS(void)
�������ƣ���ȡ��·״̬
�������ܣ�ѡͨʹ��PORT2
��ڲ�������                  
���ڲ���������״ֵ̬
��    �ߣ�
��    �ڣ�
----------------------------------------------------------------------*/
unsigned int ReadCPLDSTS(void)
{   
	static Uint16 count = 0;
	Uint16 temp, temp1, temp2;

	do
	{
		temp1 = ((*(CS0AND1_ADDR + 2)) & 0xff);
		DelayUs(50);

		temp2 = ((*(CS0AND1_ADDR + 2)) & 0xff);
		DelayUs(50);

		count++;
		if (count >= 3)
		{
			count = 3;
			break;
		}
	}
	while (temp1 != temp2);

	if (count == 3)
	{
		temp = 0x5555;
	}
	else
	{
		temp = temp1;
	}

	count = 0;

    return (temp);
}

/*---------------------------------------------------------------------
����ԭ�ͣ�void ClrCPLDSTS(void)
�������ƣ��������
�������ܣ���˿�3д�����������������
��ڲ�������                  
���ڲ�������
��    �ߣ�
��    �ڣ�
----------------------------------------------------------------------*/
void ClrCPLDSTS(void)
{
	*(CS0AND1_ADDR + 3) = 0;
    DelayUs(50);
	*(CS0AND1_ADDR + 3) = 0;
	DelayUs(50);
	*(CS0AND1_ADDR + 3) = 0;
	DelayUs(50);
	*(CS0AND1_ADDR + 3) = 0;
	DelayUs(50);
	*(CS0AND1_ADDR + 3) = 0;
	DelayUs(50);
	*(CS0AND1_ADDR + 3) = 0;
	DelayUs(50);
	*(CS0AND1_ADDR + 3) = 0;
	DelayUs(50);
	*(CS0AND1_ADDR + 3) = 0;
	DelayUs(50);
	*(CS0AND1_ADDR + 3) = 0;
	DelayUs(50);
	*(CS0AND1_ADDR + 3) = 0;
}

