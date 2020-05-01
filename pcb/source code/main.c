#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include.h"
#include "struct.h" 

int main() 
{
	char *filename = "..\\data\\winequality-white.csv";
	double s_rate = 0.6, l_rate = 0.0001;
	int i,j;
	int col_num = 12, row_num = 5000;
	int epoch = 100, k = 5, train_size, fold;
	double temp = 0;
	int *index, *count;
	double **data; 
	double *acc;
	acc = (double *)malloc(sizeof(double)*k);
	count = (int *)malloc(sizeof(int)*MAX_CLASS);
	memset(count,0,sizeof(int)*MAX_CLASS);

	data = csv2array(filename, col_num, row_num); //此处row_num大于真实row_num+1 , col_num必须是真实col_num 
	row_num = data[col_num][0];
	index = (int *)malloc(sizeof(int)*row_num);
	
	normalize_data(data,col_num);
	
	printf(" \n\n Multivariate Linear Regression : \n");
	 mlr_eva(l_rate, epoch, data, col_num, k);
	 
	//生成第一个随机索引数组 
	rand_index(row_num, 97, index);
	fold = row_num/k;
	train_size = fold*(k-1);
	printf(" \n Zero Rule: \n");
	temp = 0;
	//交叉检验 
	for(i=0;i<k;i++)
	{
		zero_rule(data,col_num,0,index, train_size,count);
		
		temp += rmse_metric(data, col_num, index, train_size);
		next_fold(fold, row_num, index);
	}
	temp /= k;
	printf("\n average rmse : %f \n",temp);
		
		
	free(index); 
	return 0;
}


	
