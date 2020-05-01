#include <stdio.h>
#include <math.h>
#include <stdlib.h> 
#include "include.h"
#include "struct.h"


/******************************************
void normalize_data(double** data, int col_num)

�������ã�
		�淶������ 
�������:
	 	double **data = ����������Ϣ�Ķ�ά���� 
	 	int col_num = ����(��ȷ��)
����ֵ��
��ע: 
******************************************/
void normalize_data(double** data, int col_num)
{
	int i, j, row_num = data[col_num][0] - 1;
	double f_min = MIN, f_max = MAX;
	
	printf("\n row_num : %d \n",row_num);
	 
	printf("start to find the min & max\n");
	
	for(i = 0;i < col_num;i++)
	{
		f_min = MAX;
		f_max = MIN;
		for(j = 0;j < row_num ; j++)
		{
			if(data[i][j] < f_min)
				f_min = data[i][j]; 
			if(data[i][j] > f_max)
				f_max = data[i][j];
		}
		printf("round %d min:%f  max:%f\n",i,f_min,f_max);
		//�������ÿռ� 
		data[i][row_num] = f_min;
		data[i][row_num+1] = f_max-f_min;
		
	 } 
	
	
	for(j = 0;j < col_num;j++)
	{	
		for(i = 0; i < row_num - 1;i++)
		{
			data[j][i] = (data[j][i] - data[j][row_num])/data[j][row_num+1];
		}
	 } 
	 
 } 
  
/******************************************
void standardize_data(double** data, int col_num)

�������ã�
		��׼������ 
�������:
	 	double **data = ����������Ϣ�Ķ�ά���� 
	 	int col_num = ����(��ȷ��)
����ֵ��
��ע: 
******************************************/
void standardize_data(double** data, int col_num)
{
	int row_num = data[col_num][0], i, j;
	int m = row_num, s = row_num + 1; 
	
	//�����ֵ�뷽�� 
	mean_stdev(data,col_num);
	//��׼�� 
	for(i = 0;i<col_num;i++)
	{
		for(j = 0;j < row_num;j++)
		{
			data[i][j] = (data[i][j] - data[i][m])/data[i][s];
		}
	}
 } 


 /******************************************
void mean_stdev(double** data,int col_num)

�������ã�
		������ƽ��ֵ���з��� 
�������:
	 	double **data = ����������Ϣ�Ķ�ά���� 
	 	int col_num = ����(��ȷ��)
����ֵ��
��ע: 
	�ֱ�mean �� stdev����data[row_num]��data[row_num+1] 
******************************************/
void mean_stdev(double** data,int col_num)
{
	int row_num = (int)data[col_num][0], i, j;
	int m = row_num, s = row_num + 1; 
	
	//�����ֵ 
	for(i = 0;i<col_num;i++)
	{
		data[i][m] = 0;
		for(j = 0;j<row_num;j++)
		{
			data[i][m] += data[i][j];
		}
		data[i][m] /= row_num;
	}
	
	//�����׼�� 
	for(i = 0;i<col_num;i++)
	{
		data[i][s] = 0;
		for(j = 0;j<row_num;j++)
		{
			data[i][s] += (data[i][j] - data[i][m])*(data[i][j] - data[i][m]);
		}
		data[i][s] /= (row_num-1);
		data[i][s] = sqrt(data[i][s]);
	}
	
}
