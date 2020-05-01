#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h> 
#include "include.h"
#include "struct.h"

 /******************************************
void zero_rule(double **data,int col_num,int isclassi, int *index, int train_size, int *count)

�������ã�
		�����Ԥ�� 
�������:
	 	double **data = ����������Ϣ�Ķ�ά����
	 	int col_num = ����(��ȷ��)
	 	int isclassi = ָʾ��������(==0:�������⣻!=0:�ع�����) 
	 	int *index = �����������
		int train_size = ѵ������С 
		int *count = ���ڴ�Ÿ���������������������
����ֵ��
��ע: 
		Ԥ��ֵ����data����λ�ã����includ.h��Ϣ������ 
******************************************/
void zero_rule(double **data,int col_num,int isclassi, int *index, int train_size, int *count)
{
	int row_num = data[col_num][0], ans = col_num - 1, pre = col_num + 1, i;
	int  class_num, trans[MAX],max = -1,max_i = -1; 
	double mean = 0;
	
	if(isclassi)
	{
		class_num = separate(count,data,col_num,index,train_size,trans);
		
		for(i=0;i<class_num;i++)
		{
			if(count[i]>max)
			{
				max = count[i];
				max_i = i; 
			}
		}
		
		for(i=train_size;i<row_num;i++)
		{
			data[pre][index[i]] = max_i;
		}
	}
	else
	{
		for(i=0;i<train_size;i++)
		{
			mean += data[ans][index[i]];
		}
		mean /= train_size;
		
		for(i=train_size;i<row_num;i++)
		{
			data[pre][index[i]] = mean;
		}
	}
}
