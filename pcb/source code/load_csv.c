#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include.h"
#include "struct.h"

/******************************************
double** csv2array(const char* filename,int col_num,int row_num)

�������ã�
		��csv�ļ��е����ݶ����ά����
�������:
	 	const char *filename = �ļ��� 
	 	int col_num = ����(��ȷ��)
		int row_num = ����(�Ⱦ�ȷ�������) 
����ֵ��
		double **tank = ����������Ϣ�Ķ�ά����
��ע: 
		����㾫ȷ�������������� **tank 
******************************************/
double** csv2array(const char* filename,int col_num,int row_num)
{
	char *row = (char *)malloc(ROW_SIZE), *col;
	FILE *fp = fopen(filename,"rt");
	int i = 0, j;
	double **tank;
	//�б���ǰ���б��ں� 
	tank = (double **)malloc(sizeof(double*)*(col_num+5));	//�˴�col_num + 5 ��Ϊ���պ󱣴�һЩ���õ���Ϣ
	for(i=0;i<=col_num+1;i++)
	{
		tank[i] = (double *)malloc(sizeof(double)*row_num);
	}
	
	
	i = 0;
	
	//�����ݶ���tank
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
	
	
	//������������������tank���õ�λ�� 
	tank[col_num][0] = i;
	tank[col_num][1] = col_num;
	
	fclose(fp);
	return tank; 
 } 






