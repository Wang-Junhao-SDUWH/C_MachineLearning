#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h> 
#include "include.h"
#include "struct.h"

 /******************************************
void zero_rule(double **data,int col_num,int isclassi, int *index, int train_size, int *count)

函数作用：
		零规则预测 
输入参数:
	 	double **data = 存有数据信息的二维数组
	 	int col_num = 列数(精确的)
	 	int isclassi = 指示问题类型(==0:分类问题；!=0:回归问题) 
	 	int *index = 随机索引数组
		int train_size = 训练集大小 
		int *count = 用于存放各种类所含数据量的数组
返回值：
备注: 
		预测值存入data空闲位置，详见includ.h信息索引表 
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
