#include "generate.h"
#include "validate.h"

/*********************************************************************
Function       :main 
Description    :������
Parameters     :none
Returns        :int
Create&Verlog  :Wu Junyi  Date:   2019-01-12    Version:   01 init
**********************************************************************/
int main(void)
{
	/* ģ���ʼ�� */
	GEN_Init();
	VAL_Init();

	/* ���� */
	printf("��ʼ����...\n\n����˵��: P = PASS, F = FAIL , N = NOT SRTICT \n\n");
	do
	{
		VAL_Validate(GEN_GetSequence(),PRINT_ON);	
	} while (GEN_Next());

	/* ��ӡͳ�ƽ�� */
	printf("\n���ͳ�ƣ�\n\n1.�ϸ��  %10lu ��\n2.���ϸ��%10lu ��\n3.���Ƽ���%10lu ��\n\n",VAL_GetCountNumber(COUNT_S), VAL_GetCountNumber(COUNT_NS), VAL_GetCountNumber(COUNT_TOTAL));
	system("pause");

	return(0);
}

