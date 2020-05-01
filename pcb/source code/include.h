#define MAX_SIZE 50000
#define ROW_SIZE 500
#define COL_SIZE 500
#define MAX_CLASS 200
#define MAX 100000
#define MIN -100000
#define pi 3.1415926535


double** csv2array(const char* filename,int col_num,int row_num);
void normalize_data(double** data, int col_num);
void mean_stdev(double** data,int col_num);
void standardize_data(double** data, int col_num);


void rand_index(int total, int seed, int *index);
void next_fold(int fold, int total, int *index);
//void confusion_matrix(dataset *data, int inte);
double  accuracy(double** data, int col_num,int *index, int train_size);
double mae_metric(double** data, int col_num, int *index, int train_size);
double rmse_metric(double** data, int col_num, int *index, int train_size);

//simple linearregression
void linear_calc(int t_col, double** data, int col_num, int* index,int train_size,double *ab);
void linear_pre(double **data, int t_col, int col_num, int* index, int train_size);

// multivariate linear regression
void mlr_eva(double l_rate, int epoch, double** data, int col_num, int k);
void mlr_pre(double **data, double l_rate, int epoch, int col_num, int *index,int train_size, double *coe);
void mlr_sgd(double l_rate, int epoch, double** data, int col_num, int *index, int train_size,double *coe);
double mlr_row_pre(double *coe, int row, double **data, int col_num);

//perceptron
void pcep_top(double l_rate, int epoch, double** data, int col_num, int k);
void pcep_pre(double **data, double l_rate, int epoch, int col_num, int *index,int train_size);
void pcep_sgd(double l_rate, int epoch, double** data, int col_num, int *index, int train_size,double *weights);
double pcep_row_pre(double *weights, int row, double **data, int col_num);

//naive bayes
void bayes_top(double **data, int col_num,int k);
void naive_bayes(double **data, int col_num,int *index,int train_size);
void bayes_pre(double **data,int col_num, int *index,int train_size,int class_num,int *count,double **m_s);
double calc_norm(double x,double mean, double std);
void calc_ms(double **m_s, int* count, int class_num, double ** data, int col_num,int *index, int train_size, int *trans);
int separate(int *count, double **data,int col_num,int *index, int train_size, int *trans);

void zero_rule(double **data,int col_num,int isclassi, int *index, int train_size, int *count);

/*********************************************************
					信息索引表
 
	data[col_num][0] = 总行数 
	data[col_num][1] = 总列数 
	data[col_num+1][x] = 各行预测值
	data[col_num+2][x] = 各行预测值
	......
	data[col_num+n][x] = 各行预测值
	
	data[x][row_num] = 各列均值
	data[x][row_num+1] = 各列标准差 
*********************************************************/ 

/*********************************************************
					备注 
 	1. 请手动删除数据的header 
*********************************************************/ 
