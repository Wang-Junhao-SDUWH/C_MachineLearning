#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h> 
#include "include.h"
#include "struct.h"

/******************************************
void pcep_eva(double l_rate, int epoch, double** data, int col_num, int k)

�������ã�
		peceptron���㺯�� 
�������:
		double l_rate = ѧϰ����
		int epoch = ÿ��ѧϰ���� 
	 	double **data = ����������Ϣ�Ķ�ά����
	 	int col_num = ����(��ȷ��)
	 	int k = ���� 
����ֵ��
��ע: 
******************************************/
void pcep_top(double l_rate, int epoch, double** data, int col_num, int k)
{
	int *index, row_num = data[col_num][0], i, j;
	int fold = (row_num/k);
	int train_size = (k-1)*fold;
	double *acc, temp =0;
	acc = (double *)malloc(sizeof(double)*k);
	index = (int *)malloc(sizeof(int)*row_num);
	
	//���ɵ�һ������������� 
	rand_index(row_num, 97, index);
	//������� 
	for(i=0;i<k;i++)
	{
		pcep_pre(data, l_rate, epoch, col_num, index, train_size);
		
		acc[i] = accuracy( data, col_num,index,train_size);
		
		//������һ�������������
		next_fold(fold, row_num, index);
	}
	
	printf(" \n Perceptron: \n");
	for(i=0;i<k;i++)
	{
		temp += acc[i];
		printf("\n accuracy of fold[%d] : %f",i,acc[i]);
	}
	temp /= k;
	printf("\n average accuracy : %f \n",temp);
}

/******************************************
void pcep_pre(double **data, double l_rate, int epoch, int col_num, int *index,int train_size)

�������ã�
		pceptronԤ�⺯�� 
�������:
	 	double **data = ����������Ϣ�Ķ�ά����
		double l_rate = ѧϰ����
		int epoch = ÿ��ѧϰ���� 
	 	int col_num = ����(��ȷ��)
	 	int *index = �����������
		int train_size = ѵ������С 
����ֵ��
��ע: 
******************************************/
void pcep_pre(double **data, double l_rate, int epoch, int col_num, int *index,int train_size)
{
	double *weights;
	int row_num = data[col_num][0], i, j;
	int pre = col_num + 1;
	weights = (double *)malloc(sizeof(double)*(col_num+1));
	memset(weights,0,sizeof(double)*col_num);
	
	pcep_sgd(l_rate, epoch, data, col_num, index, train_size, weights);
	
	for(i=train_size;i<row_num;i++)
	{
		data[pre][index[i]] = weights[0];
		
		for(j=0;j<col_num-1;j++)
		{
			data[pre][index[i]] += weights[j+1]*data[j][index[i]];
		}
		
		if(data[pre][index[i]] >= 0)
			data[pre][index[i]] = 1;
		else
			data[pre][index[i]] = 0;
	}
}

/******************************************
void pcep_sgd(double l_rate, int epoch, double** data, int col_num, int *index, int train_size,double *weights)

�������ã�
		ͨ������ݶ��½��Ż�ϵ�� 
�������:
		double l_rate = ѧϰ����
		int epoch = ÿ��ѧϰ���� 
	 	double **data = ����������Ϣ�Ķ�ά����
	 	int col_num = ����(��ȷ��)
	 	int *index = �����������
		int train_size = ѵ������С 
		double *weights = ���ѵ���õ���ϵ�� 
����ֵ��
��ע: 
******************************************/
void pcep_sgd(double l_rate, int epoch, double** data, int col_num, int *index, int train_size,double *weights)
{
	int row_num = data[col_num][0], i, j, k,l;
	int pre = col_num + 1, ans = col_num -1;
	double err, sum_err;
	
	for(i=0;i<col_num;i++)
		printf("weights[%d] : %f",i,weights[i]);
	
	
	//�Ż����� 
	for(i=0;i<epoch;i++)
	{
		sum_err = 0;
		for(j=0;j<train_size;j++)
		{
			data[pre][index[j]] = pcep_row_pre(weights, index[j], data, col_num);
			
			err = data[pre][index[j]] - data[ans][index[j]];
			
			sum_err += err*err;
			weights[0] = weights[0] - l_rate*err;
			
			for(k=1;k<=col_num;k++)
			{
				weights[k] = weights[k] - l_rate*err*data[k-1][index[j]];
			}
		}
		
		printf("\n>>epoch = %d,	lrate = %f,	error = %.3f, train_size = %d\n", i, l_rate, sum_err,train_size);
	}
	
}

/******************************************
double pcep_row_pre(double *weights, int row, double **data, int col_num)

�������ã�
		�Ե��н���Ԥ��
�������:
		double *weights = ���ѵ���õ���ϵ�� 
		int row = Ŀ�����б� 
	 	double **data = ����������Ϣ�Ķ�ά����
	 	int col_num = ����(��ȷ��)
����ֵ��
		double = Ԥ��ֵ 
��ע: 
******************************************/
double pcep_row_pre(double *weights, int row, double **data, int col_num)
{
	int i;
	double activ;
	
	activ = weights[0];
	for(i=0;i < col_num - 1;i++)
	{
		activ += weights[i+1]*data[i][row];
	}
	
	if(activ >= 0)
		return 1;
	else
		return 0;
}
