 #include <stdio.h>
 #include <stdlib.h>
 #include <time.h> 
 #include <string.h>
 #include <math.h>
 #include "include.h"
 #include "struct.h" 
 
/******************************************
void rand_index(int total, int seed, int *index)

函数作用：
		生成随机索引数组(打乱下标) 
输入参数:
	 	int total = 数据的行数 
	 	int seed = 用来生成随机数的整数种子
		int *index = 存放随机索引的数组 
返回值：
备注:  
******************************************/
void rand_index(int total, int seed, int *index)
{
	int temp, i, j, a=total*3;

	//初始化一个自然数数组 
	for(i = 0;i<total;i++)
		index[i] = i;
		
	//打乱顺序 
	srand(seed);
	while(a--)
	{
		i = rand()%total;
		j = rand()%total;
		temp = index[i];
		index[i] = index[j];
		index[j] = temp;
	}
	
 } 
 
 

/******************************************
void next_fold(int fold, int total, int *index)

函数作用：
		生成随机索引数组(打乱下标) 
输入参数:
	 	int fold = k-fold的每折的大小 
	 	int total = 数据的行数 
		int *index = 存放随机索引的数组 
返回值：
备注:  
		输入的index是一个加工好的随机索引数组
		本函数将其前fold位移至最后
		其他各位依次前移 
******************************************/
void next_fold(int fold, int total, int *index)
{
	int i, j, temp;
	
	for(i = 0;i<fold;i++)
	{
		temp = index[total-1];
		for(j=total-1;j>0;j--)
		{
			index[j] = index[j-1];
		}
		index[0] = temp;
	}
 } 
 

 
/******************************************
void next_fold(int fold, int total, int *index)

函数作用：
		计算分类算法的正确率 
输入参数:
		double **data = 存有数据信息的二维数组
		int col_num = 数据的列数 
		int *index = 存放随机索引的数组 
		int train_size = 训练集容量 
返回值：
		double accu = 分类正确率 
备注:  
******************************************/
double  accuracy(double** data, int col_num,int *index, int train_size)
{
	int row_num = data[col_num][0], sum = 0, i;
	int pre = col_num+1, ans = col_num-1;
	double accu;
	
	for(i = train_size;i<row_num;i++)
	{
		if(data[pre][index[i]] == data[ans][index[i]])
			sum++;
	}
	
	accu = (double)sum/(row_num - train_size);
	
	return accu;
}

/******************************************
double mae_metric(double** data, int col_num, int *index, int train_size)

函数作用：
		计算回归算法的平均绝对误差 
输入参数:
		double **data = 存有数据信息的二维数组
		int col_num = 数据的列数 
		int *index = 存放随机索引的数组 
		int train_size = 训练集容量 
返回值：
		double mae = 平均绝对误差
备注:  
******************************************/
double mae_metric(double** data, int col_num, int *index, int train_size)
{
	int row_num = data[col_num][0], sum = 0, i;
	double mae=0;
	
	for(i=train_size;i<row_num;i++)
		mae += abs(data[col_num+1][index[i]]-data[col_num-1][index[i]]);
	mae /= (row_num-train_size);
	
	//打印结果 
	printf("\n			| mean absolute error |			 %f \n",mae);
	
	return mae; 
 } 
 
/******************************************
double rmse_metric(double** data, int col_num, int *index, int train_size)

函数作用：
		计算回归算法的均方根误差
输入参数:
		double **data = 存有数据信息的二维数组
		int col_num = 数据的列数 
		int *index = 存放随机索引的数组 
		int train_size = 训练集容量 
返回值：
		double rmse = 均方根误差 
备注:  
******************************************/
double rmse_metric(double** data, int col_num, int *index, int train_size)
{
	int row_num = data[col_num][0], sum = 0, i;
	double rmse=0;
	
	for(i=train_size;i<row_num;i++)
		rmse += (data[col_num+1][index[i]]-data[col_num-1][index[i]])*(data[col_num+1][index[i]]-data[col_num-1][index[i]]);
	rmse /= (row_num-train_size);
	rmse = sqrt(rmse);
	
	
	//打印结果 
	printf("\n			| root mean squared error |			 %f \n",rmse);
	
	return rmse; 
 } 
 
 
 
 
 
 /****************************
	生成混淆矩阵 
参数说明：
	dataset* --> 存储数据的结构体 
	inte --> 每一行int型数据的个数
说明:
	将生成的混淆矩阵写入文件中 
	行标为预测值，列标为实际值 
****************************/
//
//void confusion_matrix(dataset *data, int inte)
//{
//	int floa = data[0].inte[inte+2], total = data[0].inte[inte], i, j;
//	int **confu = (int**)malloc(sizeof(int*)*total);
//	FILE *fp;
//	time_t timer;
//	struct tm *tblock;
//	
//	for(i=0;i<total;i++)
//		confu[i] = (int*)malloc(sizeof(int)*total);
//	memset(confu,0,sizeof(int)*total*total);
//	
//	for(i=0;i<total;i++)
//	{
//		confu[(int)data[i].pre][(int)data[i].ans]++;
//	}
//		
//	
//	//将结果写入文件
//	fp = fopen("output.txt","at");
//	fputs("\r\n\r\n------------------------------------",fp);
//	fputs("------------------------------------",fp);
//	fputs("------------------------------------",fp);
//	fputs("------------------------------------",fp);
//	fputs("------------------------------------",fp);
//	fputs("------------------------------------\r\n",fp);
//	fputs("\r\n			| confusion matrix |			\r\n",fp);
//	for(i=0;i<total;i++)
//		fprintf(fp,"       	  %d",i);
//	for(i=0;i<total;i++)
//	{
//		fprintf(fp,"\r\n %d",i);
//		for(j=0;j<total;j++)
//			fprintf(fp,"\r\n	%d",confu[i][j]);
//	}
//	
//	timer = time(NULL);
//	tblock = localtime(&timer);
//	fprintf(fp,"\r\n	Local time : %s\r\n",asctime(tblock));
//	fputs("------------------------------------",fp);
//	fputs("------------------------------------",fp);
//	fputs("------------------------------------\r\n",fp);
//	fclose(fp); 	
//		
//	free(confu);
// } 
 
