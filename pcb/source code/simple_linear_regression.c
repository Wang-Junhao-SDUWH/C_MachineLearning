#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "include.h"
#include "struct.h"

/******************************************
void linear_pre(double **data, int t_col, int col_num, int* index, int train_size)

�������ã�
		�����Իع�Ԥ�⺯�� 
�������:
	 	double **data = ����������Ϣ�Ķ�ά����
	 	int t_col = Ŀ�����б� 
	 	int col_num = ����(��ȷ��)
	 	int *index = ����������� 
		int train_size = ѵ������С 
����ֵ��
��ע: 
******************************************/
void linear_pre(double **data, int t_col, int col_num, int* index, int train_size)
{
	double coe[2];
	int i,row_num = data[col_num][0], pre = col_num + 1, ans = col_num -1;
	linear_calc(t_col, data,col_num,index,train_size, coe);
	
	printf("\n  a��b: %f, %f \n",coe[0],coe[1]);
	for(i=train_size;i<row_num;i++)
	{
		data[pre][index[i]] = coe[0]*data[t_col][index[i]] + coe[1];
	}	
	
}


 
/******************************************
void linear_calc(int t_col, double** data, int col_num, int* index,int train_size,double *ab)

�������ã�
		��������Իع�����Ԥ���ϵ�� 
�������:
	 	int t_col = Ŀ�����б� 
	 	double **data = ����������Ϣ�Ķ�ά����
	 	int col_num = ����(��ȷ��)
	 	int *index = ����������� 
		int train_size = ѵ������С 
		double *ab = ���ϵ�������� 
����ֵ��
��ע: 
******************************************/

void linear_calc(int t_col, double** data, int col_num, int* index,int train_size,double *ab)
{
	int row_num = data[col_num][0], i, j;
	int c = row_num + 2, m = row_num, s = row_num + 1;
	
	
	//�����ֵ 
	for(i = 0;i<col_num;i++)
	{
		data[i][m] = 0;
		for(j = 0;j<train_size;j++)
		{
			data[i][m] += data[i][index[j]];
		}
		data[i][m] /= train_size;
	}
	
	//���㷽�� 
	for(i = 0;i<col_num;i++)
	{
		data[i][s] = 0;
		for(j = 0;j<train_size;j++)
		{
			data[i][s] += (data[i][index[j]] - data[i][m])*(data[i][index[j]] - data[i][m]);
		}
		data[i][s] /= (train_size-1);
		data[i][s] = sqrt(data[i][s]);
	}
	
	//����Э���� 
	data[t_col][c] = 0;
	for(j = 0;j<train_size;j++)
	{
		data[t_col][c] += (data[t_col][index[j]]-data[t_col][m])*(data[col_num-1][index[j]]-data[col_num-1][m]);
	}
	
	//����ÿһ�е�ϵ��
	ab[0] = data[t_col][c] / ((data[t_col][s])*(data[t_col][s])*(train_size-1));
	ab[1] = data[col_num-1][m] - ab[0]*data[t_col][m];
}


