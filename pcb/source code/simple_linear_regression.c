#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "include.h"
#include "struct.h"

/******************************************
void linear_pre(double **data, int t_col, int col_num, int* index, int train_size)

函数作用：
		简单线性回归预测函数 
输入参数:
	 	double **data = 存有数据信息的二维数组
	 	int t_col = 目标列列标 
	 	int col_num = 列数(精确的)
	 	int *index = 随机索引数组 
		int train_size = 训练集大小 
返回值：
备注: 
******************************************/
void linear_pre(double **data, int t_col, int col_num, int* index, int train_size)
{
	double coe[2];
	int i,row_num = data[col_num][0], pre = col_num + 1, ans = col_num -1;
	linear_calc(t_col, data,col_num,index,train_size, coe);
	
	printf("\n  a、b: %f, %f \n",coe[0],coe[1]);
	for(i=train_size;i<row_num;i++)
	{
		data[pre][index[i]] = coe[0]*data[t_col][index[i]] + coe[1];
	}	
	
}


 
/******************************************
void linear_calc(int t_col, double** data, int col_num, int* index,int train_size,double *ab)

函数作用：
		计算简单线性回归用来预测的系数 
输入参数:
	 	int t_col = 目标列列标 
	 	double **data = 存有数据信息的二维数组
	 	int col_num = 列数(精确的)
	 	int *index = 随机索引数组 
		int train_size = 训练集大小 
		double *ab = 存放系数的数组 
返回值：
备注: 
******************************************/

void linear_calc(int t_col, double** data, int col_num, int* index,int train_size,double *ab)
{
	int row_num = data[col_num][0], i, j;
	int c = row_num + 2, m = row_num, s = row_num + 1;
	
	
	//计算均值 
	for(i = 0;i<col_num;i++)
	{
		data[i][m] = 0;
		for(j = 0;j<train_size;j++)
		{
			data[i][m] += data[i][index[j]];
		}
		data[i][m] /= train_size;
	}
	
	//计算方差 
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
	
	//计算协方差 
	data[t_col][c] = 0;
	for(j = 0;j<train_size;j++)
	{
		data[t_col][c] += (data[t_col][index[j]]-data[t_col][m])*(data[col_num-1][index[j]]-data[col_num-1][m]);
	}
	
	//计算每一列的系数
	ab[0] = data[t_col][c] / ((data[t_col][s])*(data[t_col][s])*(train_size-1));
	ab[1] = data[col_num-1][m] - ab[0]*data[t_col][m];
}


