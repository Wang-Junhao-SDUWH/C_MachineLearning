#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h> 
#include "include.h"
#include "struct.h"

 /******************************************
void mlr_eva(double l_rate, int epoch, double** data, int col_num, int k)

�������ã�
		��������Իع��㷨�Ķ��㺯�� 
�������:
		double l_rate = ѧϰ����
		int epoch = ÿ��ѧϰ���� 
	 	double **data = ����������Ϣ�Ķ�ά���� 
	 	int col_num = ����(��ȷ��)
	 	int k = ���� 
����ֵ��
��ע: 
	�ֱ�mean �� stdev����data[row_num]��data[row_num+1] 
******************************************/
void mlr_eva(double l_rate, int epoch, double** data, int col_num, int k)
{
	int *index, row_num = data[col_num][0], i, j;
	int fold = (int)(row_num/k);
	int train_size = (k-1)*fold;
	double *coe, temp;
	coe = (double *)malloc(sizeof(double)*(col_num));
	memset(coe,0,sizeof(double)*(col_num));
	
	index = (int *)malloc(sizeof(int)*row_num);
	//���ɵ�һ������������� 
	rand_index(row_num, 97, index);
	temp = 0;
	//������� 
	for(i=0;i<k;i++)
	{
		mlr_pre(data, l_rate, epoch, col_num, index, train_size,coe);
		
		temp += rmse_metric(data, col_num, index, train_size);
		next_fold(fold, row_num, index);
	}
	temp /= k;
	printf("\n average rmse : %f \n",temp);
}

 /******************************************
void mlr_pre(double **data, double l_rate, int epoch, int col_num, int *index,int train_size, double *coe)

�������ã�
		�Բ��Լ����ݽ���Ԥ�� 
�������:
	 	double **data = ����������Ϣ�Ķ�ά����
		double l_rate = ѧϰ����
		int epoch = ÿ��ѧϰ����  
	 	int col_num = ����(��ȷ��)
	 	int *index = ���������������� 
		int train_size = ѵ�������� 
	 	double *coe = ѵ���õ�������Ԥ���ϵ�� 
����ֵ��
��ע: 
	Ԥ��ֵ����data����λ�ã����includ.h��Ϣ������ 
******************************************/
void mlr_pre(double **data, double l_rate, int epoch, int col_num, int *index,int train_size, double *coe)
{
	int row_num = data[col_num][0], i, j;
	int pre = col_num + 1;
	
	mlr_sgd(l_rate, epoch, data, col_num, index, train_size, coe);
	
	for(i=train_size;i<row_num;i++)
	{
		data[pre][index[i]] = coe[0];
		
		for(j=0;j<col_num-1;j++)
		{
			data[pre][index[i]] += coe[j+1]*data[j][index[i]];
		}
	}
	
}

 /******************************************
void mlr_sgd(double l_rate, int epoch, double** data, int col_num, int *index, int train_size,double *coe)

�������ã�
		ͨ������ݶ��½��Ż�ϵ�� 
�������:
		double l_rate = ѧϰ����
		int epoch = ÿ��ѧϰ����  
	 	double **data = ����������Ϣ�Ķ�ά����
	 	int col_num = ����(��ȷ��)
	 	int *index = ���������������� 
		int train_size = ѵ�������� 
	 	double *coe = ѵ���õ�������Ԥ���ϵ�� 
����ֵ��
��ע: 
******************************************/
void mlr_sgd(double l_rate, int epoch, double** data, int col_num, int *index, int train_size,double *coe)
{
	int row_num = data[col_num][0], i, j, k,l;
	int pre = col_num + 1, ans = col_num -1;
	double err, sum_err;
	
	//�Ż����� 
	for(i=0;i<epoch;i++)
	{
		sum_err = 0;
		for(j=0;j<train_size;j++)
		{
			data[pre][index[j]] = mlr_row_pre(coe, index[j], data, col_num);
			
			err = data[pre][index[j]] - data[ans][index[j]];
			sum_err += err*err;
			coe[0] = coe[0] - l_rate*err;
			
			for(k=1;k<col_num;k++)
			{
				coe[k] = coe[k] - l_rate*err*data[k-1][index[j]];
			}
		}
		
	}
}

 /******************************************
double mlr_row_pre(double *coe, int row, double **data, int col_num)

�������ã�
		�Ե������ݽ���Ԥ�� 
�������:
	 	double *coe = ѵ���õ�������Ԥ���ϵ�� 
	 	int row = Ŀ�����б� 
	 	double **data = ����������Ϣ�Ķ�ά����
	 	int col_num = ����(��ȷ��)
����ֵ��
		double yhat = Ԥ��ֵ 
��ע: 
******************************************/
double mlr_row_pre(double *coe, int row, double **data, int col_num)
{
	int i;
	double yhat;
	
	yhat = coe[0];
	
	for(i=0;i < col_num - 1;i++)
	{
		yhat += coe[i+1]*data[i][row];
	}
	
	return yhat;
}
