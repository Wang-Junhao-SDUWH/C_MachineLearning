#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include.h"
#include "struct.h"

/******************************************
double** csv2array(const char* filename,int col_num,int row_num)

函数作用：
		将csv文件中的数据读入二维数组
输入参数:
	 	const char *filename = 文件名 
	 	int col_num = 列数(精确的)
		int row_num = 行数(比精确行数大的) 
返回值：
		double **tank = 存有数据信息的二维数组
备注: 
		会计算精确的行数并保存至 **tank 
******************************************/
double** csv2array(const char* filename,int col_num,int row_num)
{
	char *row = (char *)malloc(ROW_SIZE), *col;
	FILE *fp = fopen(filename,"rt");
	int i = 0, j;
	double **tank;
	//列标在前，行标在后 
	tank = (double **)malloc(sizeof(double*)*(col_num+5));	//此处col_num + 5 是为了日后保存一些有用的信息
	for(i=0;i<=col_num+1;i++)
	{
		tank[i] = (double *)malloc(sizeof(double)*row_num);
	}
	
	
	i = 0;
	
	//将数据读入tank
	while(fgets(row, 2000, fp) != NULL)
	{
		
		col = strtok(row,",");
		
		for(j=0;j<col_num;j++)
		{
			tank[j][i] = atof(col);
			col = strtok(NULL,",");
		}
		
		i++;
	}
	
	
	//将总行数、列数存入tank闲置的位置 
	tank[col_num][0] = i;
	tank[col_num][1] = col_num;
	
	fclose(fp);
	return tank; 
 } 






