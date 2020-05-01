#include "validate.h"

static SELECTION result[QUEST_NUM];
static long unsigned int val_countS, val_countNS, val_countTotal;

/*********************************************************************
Function       :VAL_Init
Description    :��֤��ģ���ʼ��
Parameters     :none
Returns        :none
Create&Verlog  :Wu Junyi  Date:   2019-01-12    Version:   01 init
**********************************************************************/
void VAL_Init(void)
{
	/*��ʼ����������*/
	val_countS = 0;        /*�ϸ������*/
	val_countNS = 0;       /*���ϸ������*/
	val_countTotal = 0;    /*��������*/

	/*ͨ������ķ�ʽ�趨�����ѡ��*/
	//TBD
}

/*********************************************************************
Function       :VAL_Validate
Description    :ִ����֤����ӡ
Parameters     :const SELECTION* result, PRINT_SW print
Returns        :none
Create&Verlog  :Wu Junyi  Date:   2019-01-12    Version:   01 init
**********************************************************************/
void VAL_Validate(const SELECTION* result, PRINT_SW print)
{
	VAL_RESULT valResult[QUEST_NUM];
	int qCount_S = 0, qCount_NS = 0;

	/* ִ��������Ŀ����֤�� */
	for (int Index = QUEST_1; Index < QUEST_NUM; Index++)
	{
		valResult[Index] = val_Pf[Index](result);
		if (PASS == valResult[Index])
		{
			qCount_S++;
		}
		else if (NOT_STRICT == valResult[Index])
		{
			qCount_NS++;
		}
		else
		{
			/* do nothing */
		}
	}

	/*�ж��Ƿ��ϸ���Ч*/
	if ((qCount_S == QUEST_NUM) && (qCount_S + qCount_NS == QUEST_NUM))
	{
		val_countS++;

		if (PRINT_ON == print)
		{
			printf("-----------------------------------------\n");
			printf("��Ŀ���: 1,2,3,4,5,6,7,8,9,X\n");
			printf(" �ϸ�� : ");
			for (int i = QUEST_1; i < QUEST_NUM; i++)
			{
				printf("%c,", ASCII_BIAS + result[i]);
			}
			printf("\b \n-----------------------------------------\n");
		}
		else
		{
			/* do nothing */
		}
	}
	/* ���ϸ�� */
	else if ((qCount_NS <= QUEST_BIAS) && (qCount_S + qCount_NS == QUEST_NUM))
	{
		val_countNS++;

		if (PRINT_ON == print)
		{
			printf("-----------------------------------------\n");
			printf("��Ŀ���: 1,2,3,4,5,6,7,8,9,X\n");
			printf("���ϸ��: ");
			for (int i = QUEST_1; i < QUEST_NUM; i++)
			{
				printf("%c,", ASCII_BIAS + result[i]);
			}
			printf("\b \n");

			printf("�������: ");
			for (int i = QUEST_1; i < QUEST_NUM; i++)
			{
				switch (valResult[i])
				{
				case PASS:
					printf("P,");
					break;
				case FAIL:
					printf("F,");
					break;
				case NOT_STRICT:
					printf("N,");
					break;
				default:
					printf("-,");
				}	
			}
			printf("\b \n-----------------------------------------\n");
		}
		else
		{
			/* do nothing */
		}
	}
	else
	{
		/* do nothing */
	}
	val_countTotal++;
}

/*********************************************************************
Function       :VAL_GetCountNumber
Description    :��ȡͳ����ֵ
Parameters     :COUNT_TYPE CountType
Returns        :long unsigned int 
Create&Verlog  :Wu Junyi  Date:   2019-01-12    Version:   01 init
**********************************************************************/
long unsigned int VAL_GetCountNumber(COUNT_TYPE CountType)
{
	long unsigned int Value;
	
	switch (CountType)
	{
		case COUNT_S:
			Value = val_countS;
			break;
		case COUNT_NS:
			Value = val_countNS;
			break;
		case COUNT_TOTAL:
			Value = val_countTotal;
			break;
		default:
			Value = 0;
	}
	return(Value);
}


/*********************************************************************
Function       :val_Question1
Description    :��֤����1
Parameters     :const SELECTION* result
Returns        :bool
Create&Verlog  :Wu Junyi  Date:   2019-01-11    Version:   01 init
**********************************************************************/
VAL_RESULT val_Question1(const SELECTION* result)
{
	if (result[QUEST_1] < ANSWER_NUM)
	{
		return(PASS);
	}
	else
	{
		return(FAIL);
	}	
}

/*********************************************************************
Function       :val_Question2
Description    :��֤����2
Parameters     :const SELECTION* result
Returns        :bool
Create&Verlog  :Wu Junyi  Date:   2019-01-11    Version:   01 init
**********************************************************************/
VAL_RESULT val_Question2(const SELECTION* result)
{
	SELECTION qSelection[ANSWER_NUM] = { C, D, A, B };
	
	if (result[QUEST_5] == qSelection[result[QUEST_2]])
	{
		return(PASS);
	}
	else
	{
		return(FAIL);
	}
}

/*********************************************************************
Function       :val_Question3
Description    :��֤����3
Parameters     :const SELECTION* result
Returns        :bool
Create&Verlog  :Wu Junyi  Date:   2019-01-11    Version:   01 init
**********************************************************************/
VAL_RESULT val_Question3(const SELECTION* result)
{
	/* �����ǵ�ѡ�⣬���ѡ��ֲ�����Ϊ������ͬ��һ��������������ͬ */
	QUEST_INDEX qContext[ANSWER_NUM] = { QUEST_3, QUEST_6, QUEST_2, QUEST_4 };
	SELECTION sameResult = ANSWER_NUM;
	VAL_RESULT funResult = PASS;

	/* �Ƚϳ���ѡ������������ѡ��ֵ�Ƿ�һ�� */
	for (int Index = A; Index < ANSWER_NUM; Index++)
	{
		if (Index != result[QUEST_3])
		{
			if (sameResult < ANSWER_NUM)
			{
				/* �Ƚ�ֵ�Ƿ�һ�� */
				if (sameResult == result[qContext[Index]])
				{
					 /* do noting */
				}
				else
				{
					funResult = FAIL;
					break;
				}
			}
			else
			{
				sameResult = result[qContext[Index]];  /* д���׼ֵ */
			}
		}
		else
		{
			 /* do nothing */
		}
	}

	 /* ��鱻ѡ���Ƿ�����������ֵ��ͬ*/
	if (PASS == funResult)
	{
		if (sameResult != result[qContext[result[QUEST_3]]])
		{
			 /* do nothing */
		}
		else
		{
			funResult = FAIL;
		}
	}
	return(funResult);
}

/*********************************************************************
Function       :val_Question4
Description    :��֤����4
Parameters     :const SELECTION* result
Returns        :bool
Create&Verlog  :Wu Junyi  Date:   2019-01-11    Version:   01 init
**********************************************************************/
VAL_RESULT val_Question4(const SELECTION* result)
{
	QUEST_INDEX qContext[ANSWER_NUM][2] = { {QUEST_1,QUEST_5},{QUEST_2,QUEST_7},{QUEST_1,QUEST_9},{QUEST_6,QUEST_10} };
	VAL_RESULT funResult = PASS;

	for (int Index = A; Index < ANSWER_NUM; Index++)
	{
		if (Index != result[QUEST_4]) /* �Ǳ�ѡ�� */
		{
			if (result[qContext[Index][0]] != result[qContext[Index][1]])
			{
				 /* do nothing */
			}
			else
			{
				funResult = NOT_STRICT;
			}
		}
		else /* �Ǳ�ѡ�� */
		{
			if (result[qContext[Index][0]] == result[qContext[Index][1]])
			{
				 /* do nothing */
			}
			else
			{
				funResult = FAIL;
				break;
			}
		}
	}
	return (funResult);
}

/*********************************************************************
Function       :val_Question5
Description    :��֤����5
Parameters     :const SELECTION* result
Returns        :bool
Create&Verlog  :Wu Junyi  Date:   2019-01-11    Version:   01 init
**********************************************************************/
VAL_RESULT val_Question5(const SELECTION* result)
{
	QUEST_INDEX qContext[ANSWER_NUM] = {QUEST_8, QUEST_4, QUEST_9, QUEST_7};
	VAL_RESULT funResult = PASS;

	for (int Index = A; Index < ANSWER_NUM; Index++)
	{
		 /* ����ѡ���������ѡ��ӦΪ�� */
		if (Index != result[QUEST_5]) /* �Ǳ�ѡ�� */
		{
			 /* �ж��Ƿ�Ϊ�� */
			if (result[qContext[Index]] != Index) /* �Ǽ� */
			{
				 /* do nothing */
			}
			else
			{
				funResult = NOT_STRICT;
			}
		}
		else /* ��ѡ�� */
		{
			 /* �ж��Ƿ�Ϊ�� */
			if (result[qContext[Index]] == Index) /* ���� */
			{
				 /* do nothing */
			}
			else
			{
				funResult = FAIL;
				break;
			}
		}
	}
	return (funResult);
}

/*********************************************************************
Function       :val_Question6
Description    :��֤����6
Parameters     :const SELECTION* result
Returns        :bool
Create&Verlog  :Wu Junyi  Date:   2019-01-11    Version:   01 init
**********************************************************************/
VAL_RESULT val_Question6(const SELECTION* result)
{
	QUEST_INDEX qContext[ANSWER_NUM][2] = { {QUEST_2,QUEST_4},{QUEST_1,QUEST_6},{QUEST_3,QUEST_10},{QUEST_5,QUEST_9} };
	VAL_RESULT funResult = PASS;

	for (int index = A; index < ANSWER_NUM; index++)
	{
		if (index != result[QUEST_6]) /* ���Ǳ�ѡ�� */
		{
			if ((index != result[qContext[index][0]])
				|| index != result[qContext[index][1]])
			{
				 /* do nothing */
			}
			else
			{
				funResult = NOT_STRICT;
			}
		}
		else /* �Ǳ�ѡ�� */
		{
			if ((index != result[qContext[index][0]])
				&& index != result[qContext[index][1]])
			{
				 /* do nothing */
			}
			else
			{
				funResult = FAIL;
				break;
			}
		}
	}
	return(funResult);
}

/*********************************************************************
Function       :val_Question7
Description    :��֤����7
Parameters     :const SELECTION* result
Returns        :bool
Create&Verlog  :Wu Junyi  Date:   2019-01-11    Version:   01 init
**********************************************************************/
VAL_RESULT val_Question7(const SELECTION* result)
{
	int min = INIT_MIN;
	int selectedCount[ANSWER_NUM] = { 0,0,0,0 };
	SELECTION qSelection[ANSWER_NUM] = {C,B,A,D};
	VAL_RESULT funResult = PASS;
	
	 /* ͳ�Ʊ�ѡ���� */
	for (int index = QUEST_1; index < QUEST_NUM; index++)
	{
		selectedCount[result[index]]++;
	}

	 /* �ҵ���С�����ж��Ƿ�Ψһ */
	for (int index = A; index < ANSWER_NUM; index++)
	{
		/* ����С�� */
		if (selectedCount[index] < min)
		{
			min = selectedCount[index];
		}
		/* Ψһ����֤ */
		else if(selectedCount[index] == min)
		{
			funResult = NOT_STRICT;
		}
		else
		{
			 /* do nothing */
		}
	}

	if (selectedCount[qSelection[result[QUEST_7]]] == min)
	{
		/* do nothing */
	}
	else
	{
		funResult = FAIL;
	}
	return(funResult);
}

/*********************************************************************
Function       :val_Question8
Description    :��֤����8
Parameters     :const SELECTION* result
Returns        :bool
Create&Verlog  :Wu Junyi  Date:   2019-01-11    Version:   01 init
**********************************************************************/
VAL_RESULT val_Question8(const SELECTION* result)
{
	QUEST_INDEX qContext[ANSWER_NUM] = { QUEST_7,QUEST_5,QUEST_2,QUEST_10 };
	unsigned char base,temp;
	VAL_RESULT funResult = PASS;
	
	base = 1 << (result[QUEST_1]);
	base = (base << 1) | (base >> 1) | base;
	base = base & 0x0F;

	for (int index = A; index < ANSWER_NUM; index++)
	{	
		temp = 1 << result[qContext[index]];
		 /* �ж��Ƿ����� */
		if ((temp & base) == 0) /* ������ʱ */
		{
			 /* �ж��Ƿ�Ϊ��ѡѡ�� */
			if (index != result[QUEST_8]) /* ���Ǳ�ѡ�� */
			{
				funResult = NOT_STRICT;
			}
			else /* �Ǳ�ѡ�� */
			{
				 /* do nothing */
			}
		}
		else /* ����ʱ */
		{
			 /* �ж��Ƿ�Ϊ��ѡѡ�� */
			if (index != result[QUEST_8]) /* ���Ǳ�ѡ�� */
			{
				 /* do nothing */
			}
			else /* �Ǳ�ѡ�� */
			{
				funResult = FAIL;
				break;
			}
		}
	}
	return(funResult);
}


/*********************************************************************
Function       :val_Question9
Description    :��֤����9
Parameters     :const SELECTION* result
Returns        :bool
Create&Verlog  :Wu Junyi  Date:   2019-01-11    Version:   01 init
**********************************************************************/
VAL_RESULT val_Question9(const SELECTION* result)
{
	QUEST_INDEX qContext[ANSWER_NUM] = { QUEST_6,QUEST_10,QUEST_2,QUEST_9 };
	VAL_RESULT funResult = PASS;

	 /* �жϵ�һ�������Ƿ�Ϊ�� */
	if (result[QUEST_1] == result[QUEST_6]) /* Ϊ�棬��ô�ڶ���ӦΪ�� */
	{
		 /* ���ǵ�ѡ�⣬ֻ�б�ѡ��Ϊ�٣�����Ϊ�� */
		for (int index = A; index < ANSWER_NUM; index++)
		{
			if (index == result[QUEST_9]) /* �Ǳ�ѡ�� */
			{
				if (result[qContext[index]] == result[QUEST_5]) /* Ϊ�� */
				{
					funResult = FAIL;
					break;
				}
				else
				{
					 /* do nothing */
				}
			}
			else /* ���Ǳ�ѡ�� */
			{
				if (result[qContext[index]] == result[QUEST_5]) /* Ϊ�� */
				{
					 /* do nothing */
				}
				else
				{
					funResult = NOT_STRICT;
				}
			}
		}
	}
	else /* Ϊ�٣���ô�ڶ���ӦΪ�� */
	{
		 /* ���ǵ�ѡ�⣬ֻ�б�ѡ��Ϊ�棬����Ϊ�� */
		for (int index = A; index < ANSWER_NUM; index++)
		{
			if (index == result[QUEST_9]) /* �Ǳ�ѡ�� */
			{
				if (result[qContext[index]] == result[QUEST_5]) /* Ϊ�� */
				{
					 /* do nothing */
				}
				else
				{
					funResult = FAIL;
					break;
				}
			}
			else /* ���Ǳ�ѡ�� */
			{
				if (result[qContext[index]] == result[QUEST_5]) /* Ϊ�� */
				{
					funResult = NOT_STRICT;
				}
				else
				{
					 /* do nothing */
				}
			}
		}
	}
	return(funResult);
}

/*********************************************************************
Function       :val_Question10
Description    :��֤����10
Parameters     :const SELECTION* result
Returns        :bool
Create&Verlog  :Wu Junyi  Date:   2019-01-11    Version:   01 init
**********************************************************************/
VAL_RESULT val_Question10(const SELECTION* result)
{
	int qContext[ANSWER_NUM] = { 3, 2, 4, 1 };
	int selectedCount[ANSWER_NUM] = { 0,0,0,0 };
	int max=0,min= INIT_MIN;

	 /* ͳ�Ʊ�ѡ���� */
	for (int index = QUEST_1; index < QUEST_NUM; index++)
	{
		selectedCount[result[index]]++;
	}

	for (int index = A; index < ANSWER_NUM; index++)
	{
		if (selectedCount[index] > max)
		{
			max = selectedCount[index];
		}
		else
		{
			 /* do nothing */
		}

		if (selectedCount[index] < min)
		{
			min = selectedCount[index];
		}
		else
		{
			 /* do nothing */
		}
	}
	/* �жϲ�ֵ�Ƿ����ѡ�� */
	if ((max - min) == qContext[result[QUEST_10]])
	{
		return (PASS);
	}
	else
	{
		return(FAIL);
	}
}