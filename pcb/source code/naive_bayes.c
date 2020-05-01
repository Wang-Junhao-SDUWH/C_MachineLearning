#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h> 
#include "include.h"
#include "struct.h"

 /******************************************
void bayes_top(double **data, int col_num,int k)

�������ã�
		���ر�Ҷ˹�㷨���㺯�� 
�������:
	 	double **data = ����������Ϣ�Ķ�ά����
	 	int col_num = ����(��ȷ��)
	 	int k = ���� 
����ֵ��
		double yhat = Ԥ��ֵ 
��ע: 
		����������Ȼ������ַ��� 
******************************************/
void bayes_top(double **data, int col_num,int k)
{
	double *acc,aver = 0;
	int *index, row_num = data[col_num][0], i, j;
	int fold = (row_num/k);
	int train_size = (k-1)*fold;
	index = (int *)malloc(sizeof(int)*row_num);
	acc = (double *)malloc(sizeof(double)*k);
	
	//���ɵ�һ������������� 
	rand_index(row_num, 2021, index);
	//������� 
	for(i=0;i<k;i++)
	{
		naive_bayes(data, col_num, index, train_size);
		
		acc[i] = accuracy( data, col_num,index,train_size);;
		
		//������һ�������������
		next_fold(fold, row_num, index);
	}
	
	
	printf("\n Naive Bayes: \n");
	for(i=0;i<k;i++)
	{
		aver += acc[i];
		printf("\n accuracy of fold[%d] : %f",i,acc[i]);
	}
	aver /= k;
	printf("\n average accuracy : %f \n",aver);
}

 /******************************************
void bayes_top(double **data, int col_num,int k)

�������ã�
		���ر�Ҷ˹�㷨�ζ��㺯�� 
�������:
	 	double **data = ����������Ϣ�Ķ�ά����
	 	int col_num = ����(��ȷ��)
	 	int *index = ����������� 
	 	int train_size = ѵ������С 
����ֵ��
��ע: 
******************************************/
void naive_bayes(double **data, int col_num,int *index,int train_size)
{
	int *count, *trans, row_num = data[col_num][0], class_num, i, j;
	double **m_s;
	
	count = (int *)malloc(sizeof(int)*MAX_CLASS);
	trans = (int *)malloc(sizeof(int)*MAX_CLASS);
	
	for (i=0;i<MAX_CLASS;i++)
	{
		count[i] = 0;
		trans[i] = 0;
	}
	
	class_num = separate(count, data, col_num,index,train_size,trans);
	
	m_s = (double **)malloc(sizeof(double*)*(class_num+1));
	
	for(i=0;i<class_num;i++)
	{
		m_s[i] = (double *)malloc(sizeof(double)*2*col_num);//��һ��col_num���ֵ���ڶ���col_num�淽�� 
	}
	
	calc_ms(m_s,count,class_num,data,col_num,index,train_size,trans); 
	
	bayes_pre(data, col_num,index,train_size,class_num, count,m_s);
}

 /******************************************
void bayes_pre(double **data,int col_num, int *index,int train_size,int class_num,int *count,double **m_s)

�������ã�
		Ԥ��ÿһ��������������ڵ����� 
�������:
	 	double **data = ����������Ϣ�Ķ�ά����
	 	int col_num = ����(��ȷ��)
	 	int *index = �����������
		int train_size = ѵ������С 
		int class_num = �ܵ������� 
		int *count = ���ڴ�Ÿ���������������������
		double **m_s = ����ÿһ������ľ�ֵ���׼��Ķ�ά���� 
����ֵ��
��ע: 
		Ԥ��ֵ����data����λ�ã����includ.h��Ϣ������  
******************************************/
void bayes_pre(double **data,int col_num, int *index,int train_size,int class_num,int *count,double **m_s)
{
	double *prob, max = -1,max_i,temp;
	int row_num = data[col_num][0], i, j, k;
	
	prob = (double *)malloc(sizeof(double)*class_num);
	
	for(i=train_size;i<row_num;i++)
	{
		for(j=0;j<class_num;j++)
		{
			prob[j] = (double)count[j]/train_size;
			for(k=0;k<col_num-1;k++)
			{
				temp = calc_norm(data[k][index[i]], m_s[j][k], m_s[j][k+col_num]);
				prob[j] *= temp;
			}
		}
		
		max = -1;
		for(j=0;j<class_num;j++)
		{
			if(prob[j] > max)
			{
				max = prob[j];
				max_i = j;
			}
		}
		
		data[col_num+1][index[i]] = max_i;
	}
}

 /******************************************
void calc_ms(double **m_s, int* count, int class_num, double **data, int col_num,int *index, int train_size, int *trans)

�������ã�
		���������ֵ���׼���£���̬�ֲ�ֵΪx�ĸ��� 
�������:
		double x = Ŀ��ֵ 
		double mean = ��ֵ
		double std = ���� 
����ֵ��
		double pro = ���� 
��ע: 
******************************************/
double calc_norm(double x,double mean, double std)
{
	double pro = 0;
	
	pro = exp(- ( pow(x-mean,2) / (2*pow(std,2) )) );
	pro /= sqrt(2*pi)*std;
	
	return pro;
}


 /******************************************
void calc_ms(double **m_s, int* count, int class_num, double **data, int col_num,int *index, int train_size, int *trans)

�������ã�
		����ÿ������ľ�ֵ���׼�� 
�������:
		double **m_s = ����ÿһ������ľ�ֵ���׼��Ķ�ά���� 
		int *count = ���ڴ�Ÿ���������������������
		int class_num = �ܵ������� 
	 	double **data = ����������Ϣ�Ķ�ά����
	 	int col_num = ����(��ȷ��)
	 	int *index = �����������
		int train_size = ѵ������С 
	 	int *trans = ���ڴ�� �б�->���� ��ӳ������� 
����ֵ��
��ע: 
		m_s[i][j] : ��i�������j�еľ�ֵ
		m_s[i][j+col_num] : ��i�������j�еı�׼��
		(j<col_num) 
******************************************/
void calc_ms(double **m_s, int* count, int class_num, double **data, int col_num,int *index, int train_size, int *trans)
{
	int row_num = data[col_num][0],i,j,k,l;
	
	for(j=0;j<col_num;j++)
	{
		for(k=0;k<class_num;k++)
			m_s[k][j] = 0;
		
		//�����ֵ 
		for(i=0;i<train_size;i++)
		{
			m_s[trans[index[i]]][j] += data[j][index[i]];
		}
		
		for(i=0;i<class_num;i++)
		{
			m_s[i][j] /= count[i];
		}
		
		//���㷽��
		for(k=0;k<class_num;k++)
			m_s[k][j+col_num] = 0;
			
		for(i=0;i<train_size;i++)
		{
			m_s[trans[index[i]]][j+col_num] += (data[j][index[i]] - m_s[trans[index[i]]][j])*(data[j][index[i]] - m_s[trans[index[i]]][j]);
		}
		
		for(i=0;i<class_num;i++)
		{
			m_s[trans[index[i]]][col_num+j] /= (count[i] - 1);
			m_s[trans[index[i]]][col_num+j] = sqrt(m_s[trans[index[i]]][col_num+j]);
		}
		 
	}
}

 /******************************************
void bayes_top(double **data, int col_num,int k)

�������ã�
		����trans���飺���б�ӳ��Ϊ����
		����count����: ��¼ÿһ������������������
		����k: �ܵ������� 
�������:
		int *count = ���ڴ�Ÿ���������������������
	 	double **data = ����������Ϣ�Ķ�ά����
	 	int col_num = ����(��ȷ��)
	 	int *index = �����������
		int train_size = ѵ������С 
	 	int *trans = ���ڴ�� �б�->���� ��ӳ������� 
����ֵ��
		int k = �ܵ������� 
��ע: 
******************************************/
int separate(int *count, double **data,int col_num,int *index, int train_size, int *trans)
{
	int row_num = data[col_num][0], kind = col_num-1, i = 0, k, l;
	
	//count[i]��¼��i�����ݵĸ��� 
	while(i<train_size)
	{
		k = data[kind][index[i]];
		trans[index[i]] = k;
		
		count[k]++;
		i++;
	}
	
	//ͳ��class����
	k=0;
	for(i=0;i<MAX_CLASS;i++)
	{
		if(count[i] != 0)
			k++;
	 } 
	return k;
}
