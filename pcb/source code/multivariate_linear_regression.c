#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h> 
#include "include.h"
#include "struct.h"

 /******************************************
void mlr_eva(double l_rate, int epoch, double** data, int col_num, int k)

函数作用：
		多变量线性回归算法的顶层函数 
输入参数:
		double l_rate = 学习速率
		int epoch = 每折学习次数 
	 	double **data = 存有数据信息的二维数组 
	 	int col_num = 列数(精确的)
	 	int k = 折数 
返回值：
备注: 
	分别将mean 和 stdev存入data[row_num]和data[row_num+1] 
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
	//生成第一个随机索引数组 
	rand_index(row_num, 97, index);
	temp = 0;
	//交叉检验 
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

函数作用：
		对测试集数据进行预测 
输入参数:
	 	double **data = 存有数据信息的二维数组
		double l_rate = 学习速率
		int epoch = 每折学习次数  
	 	int col_num = 列数(精确的)
	 	int *index = 存放随机索引的数组 
		int train_size = 训练集容量 
	 	double *coe = 训练得到的用来预测的系数 
返回值：
备注: 
	预测值存入data空闲位置，详见includ.h信息索引表 
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

函数作用：
		通过随机梯度下降优化系数 
输入参数:
		double l_rate = 学习速率
		int epoch = 每折学习次数  
	 	double **data = 存有数据信息的二维数组
	 	int col_num = 列数(精确的)
	 	int *index = 存放随机索引的数组 
		int train_size = 训练集容量 
	 	double *coe = 训练得到的用来预测的系数 
返回值：
备注: 
******************************************/
void mlr_sgd(double l_rate, int epoch, double** data, int col_num, int *index, int train_size,double *coe)
{
	int row_num = data[col_num][0], i, j, k,l;
	int pre = col_num + 1, ans = col_num -1;
	double err, sum_err;
	
	//优化参数 
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

函数作用：
		对单行数据进行预测 
输入参数:
	 	double *coe = 训练得到的用来预测的系数 
	 	int row = 目标行行标 
	 	double **data = 存有数据信息的二维数组
	 	int col_num = 列数(精确的)
返回值：
		double yhat = 预测值 
备注: 
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
