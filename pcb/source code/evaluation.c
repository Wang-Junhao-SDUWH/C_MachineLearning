 #include <stdio.h>
 #include <stdlib.h>
 #include <time.h> 
 #include <string.h>
 #include <math.h>
 #include "include.h"
 #include "struct.h" 
 
/******************************************
void rand_index(int total, int seed, int *index)

�������ã�
		���������������(�����±�) 
�������:
	 	int total = ���ݵ����� 
	 	int seed = �����������������������
		int *index = ���������������� 
����ֵ��
��ע:  
******************************************/
void rand_index(int total, int seed, int *index)
{
	int temp, i, j, a=total*3;

	//��ʼ��һ����Ȼ������ 
	for(i = 0;i<total;i++)
		index[i] = i;
		
	//����˳�� 
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

�������ã�
		���������������(�����±�) 
�������:
	 	int fold = k-fold��ÿ�۵Ĵ�С 
	 	int total = ���ݵ����� 
		int *index = ���������������� 
����ֵ��
��ע:  
		�����index��һ���ӹ��õ������������
		����������ǰfoldλ�������
		������λ����ǰ�� 
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

�������ã�
		��������㷨����ȷ�� 
�������:
		double **data = ����������Ϣ�Ķ�ά����
		int col_num = ���ݵ����� 
		int *index = ���������������� 
		int train_size = ѵ�������� 
����ֵ��
		double accu = ������ȷ�� 
��ע:  
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

�������ã�
		����ع��㷨��ƽ��������� 
�������:
		double **data = ����������Ϣ�Ķ�ά����
		int col_num = ���ݵ����� 
		int *index = ���������������� 
		int train_size = ѵ�������� 
����ֵ��
		double mae = ƽ���������
��ע:  
******************************************/
double mae_metric(double** data, int col_num, int *index, int train_size)
{
	int row_num = data[col_num][0], sum = 0, i;
	double mae=0;
	
	for(i=train_size;i<row_num;i++)
		mae += abs(data[col_num+1][index[i]]-data[col_num-1][index[i]]);
	mae /= (row_num-train_size);
	
	//��ӡ��� 
	printf("\n			| mean absolute error |			 %f \n",mae);
	
	return mae; 
 } 
 
/******************************************
double rmse_metric(double** data, int col_num, int *index, int train_size)

�������ã�
		����ع��㷨�ľ��������
�������:
		double **data = ����������Ϣ�Ķ�ά����
		int col_num = ���ݵ����� 
		int *index = ���������������� 
		int train_size = ѵ�������� 
����ֵ��
		double rmse = ��������� 
��ע:  
******************************************/
double rmse_metric(double** data, int col_num, int *index, int train_size)
{
	int row_num = data[col_num][0], sum = 0, i;
	double rmse=0;
	
	for(i=train_size;i<row_num;i++)
		rmse += (data[col_num+1][index[i]]-data[col_num-1][index[i]])*(data[col_num+1][index[i]]-data[col_num-1][index[i]]);
	rmse /= (row_num-train_size);
	rmse = sqrt(rmse);
	
	
	//��ӡ��� 
	printf("\n			| root mean squared error |			 %f \n",rmse);
	
	return rmse; 
 } 
 
 
 
 
 
 /****************************
	���ɻ������� 
����˵����
	dataset* --> �洢���ݵĽṹ�� 
	inte --> ÿһ��int�����ݵĸ���
˵��:
	�����ɵĻ�������д���ļ��� 
	�б�ΪԤ��ֵ���б�Ϊʵ��ֵ 
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
//	//�����д���ļ�
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
 
