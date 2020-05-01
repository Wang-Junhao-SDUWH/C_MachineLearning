#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h> 
#include "include.h"
#include "struct.h"

 /******************************************
void bayes_top(double **data, int col_num,int k)

函数作用：
		朴素贝叶斯算法顶层函数 
输入参数:
	 	double **data = 存有数据信息的二维数组
	 	int col_num = 列数(精确的)
	 	int k = 折数 
返回值：
		double yhat = 预测值 
备注: 
		请自行用自然数替代字符串 
******************************************/
void bayes_top(double **data, int col_num,int k)
{
	double *acc,aver = 0;
	int *index, row_num = data[col_num][0], i, j;
	int fold = (row_num/k);
	int train_size = (k-1)*fold;
	index = (int *)malloc(sizeof(int)*row_num);
	acc = (double *)malloc(sizeof(double)*k);
	
	//生成第一个随机索引数组 
	rand_index(row_num, 2021, index);
	//交叉检验 
	for(i=0;i<k;i++)
	{
		naive_bayes(data, col_num, index, train_size);
		
		acc[i] = accuracy( data, col_num,index,train_size);;
		
		//生成下一个随机索引数组
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

函数作用：
		朴素贝叶斯算法次顶层函数 
输入参数:
	 	double **data = 存有数据信息的二维数组
	 	int col_num = 列数(精确的)
	 	int *index = 随机索引数组 
	 	int train_size = 训练集大小 
返回值：
备注: 
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
		m_s[i] = (double *)malloc(sizeof(double)*2*col_num);//第一个col_num存均值，第二个col_num存方差 
	}
	
	calc_ms(m_s,count,class_num,data,col_num,index,train_size,trans); 
	
	bayes_pre(data, col_num,index,train_size,class_num, count,m_s);
}

 /******************************************
void bayes_pre(double **data,int col_num, int *index,int train_size,int class_num,int *count,double **m_s)

函数作用：
		预测每一行数据最可能属于的种类 
输入参数:
	 	double **data = 存有数据信息的二维数组
	 	int col_num = 列数(精确的)
	 	int *index = 随机索引数组
		int train_size = 训练集大小 
		int class_num = 总的种类数 
		int *count = 用于存放各种类所含数据量的数组
		double **m_s = 保存每一个种类的均值与标准差的二维数组 
返回值：
备注: 
		预测值存入data空闲位置，详见includ.h信息索引表  
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

函数作用：
		计算给定均值与标准差下，正态分布值为x的概率 
输入参数:
		double x = 目标值 
		double mean = 均值
		double std = 方差 
返回值：
		double pro = 概率 
备注: 
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

函数作用：
		计算每个种类的均值与标准差 
输入参数:
		double **m_s = 保存每一个种类的均值与标准差的二维数组 
		int *count = 用于存放各种类所含数据量的数组
		int class_num = 总的种类数 
	 	double **data = 存有数据信息的二维数组
	 	int col_num = 列数(精确的)
	 	int *index = 随机索引数组
		int train_size = 训练集大小 
	 	int *trans = 用于存放 行标->种类 的映射的数组 
返回值：
备注: 
		m_s[i][j] : 第i个种类第j列的均值
		m_s[i][j+col_num] : 第i个种类第j列的标准差
		(j<col_num) 
******************************************/
void calc_ms(double **m_s, int* count, int class_num, double **data, int col_num,int *index, int train_size, int *trans)
{
	int row_num = data[col_num][0],i,j,k,l;
	
	for(j=0;j<col_num;j++)
	{
		for(k=0;k<class_num;k++)
			m_s[k][j] = 0;
		
		//计算均值 
		for(i=0;i<train_size;i++)
		{
			m_s[trans[index[i]]][j] += data[j][index[i]];
		}
		
		for(i=0;i<class_num;i++)
		{
			m_s[i][j] /= count[i];
		}
		
		//计算方差
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

函数作用：
		生成trans数组：将行标映射为种类
		生成count数组: 记录每一个种类所含的数据量
		计算k: 总的种类数 
输入参数:
		int *count = 用于存放各种类所含数据量的数组
	 	double **data = 存有数据信息的二维数组
	 	int col_num = 列数(精确的)
	 	int *index = 随机索引数组
		int train_size = 训练集大小 
	 	int *trans = 用于存放 行标->种类 的映射的数组 
返回值：
		int k = 总的种类数 
备注: 
******************************************/
int separate(int *count, double **data,int col_num,int *index, int train_size, int *trans)
{
	int row_num = data[col_num][0], kind = col_num-1, i = 0, k, l;
	
	//count[i]记录第i种数据的个数 
	while(i<train_size)
	{
		k = data[kind][index[i]];
		trans[index[i]] = k;
		
		count[k]++;
		i++;
	}
	
	//统计class数量
	k=0;
	for(i=0;i<MAX_CLASS;i++)
	{
		if(count[i] != 0)
			k++;
	 } 
	return k;
}
