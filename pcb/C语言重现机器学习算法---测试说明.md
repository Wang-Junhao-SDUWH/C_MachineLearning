# C语言重现机器学习算法---测试说明

### 1.  Simple Linear Regression      (20)

- #### 参数说明

  - #####  数据集：Swedish Auto Insurance Dataset

  - ##### 数据集分割：train-test split， 0.6 : 0.4

  - ##### 评估指标: root mean squared error

  - ##### 基准模型: zero rule algorithm

- #### 测试结果

  - **分别用不同的seed(1,39,97),生成不同的训练集-数据集分割多次评估**
  - ![image-20200501111136942](C:\Users\Treo\AppData\Roaming\Typora\typora-user-images\image-20200501111136942.png)
  - ![image-20200501111415234](C:\Users\Treo\AppData\Roaming\Typora\typora-user-images\image-20200501111415234.png)
  - ![image-20200501111434377](C:\Users\Treo\AppData\Roaming\Typora\typora-user-images\image-20200501111434377.png)
  

- #### main.c相关代码

  - ```c
    train_size = s_rate * row_num;
      	rand_index(row_num, 2020, index);
      
      	linear_pre(data, 0, col_num,  index, train_size);
      	printf("\n Simple Linear Regression : ");
      	rmse_metric( data, col_num, index, train_size);
      	
      	printf(" Zero Rule : ");
      	zero_rule(data,col_num,0,index,train_size);
      	rmse_metric( data, col_num, index, train_size);
    ```


### 2. Multivariate Linear Regression      (25)

- #### 参数说明

  - #####  数据集：Wine Quality Dataset

  - ##### 数据集分割：cross validation split， 5-fold

  - ##### 每组分割训练次数：100

  - ##### 评估指标: root mean squared error

  - ##### 基准模型: zero rule algorithm


- #### 测试结果

  - **分别用不同的seed(1,39,97),生成不同的训练集-数据集分割多次评估**
  - ![image-20200501160630749](C:\Users\Treo\AppData\Roaming\Typora\typora-user-images\image-20200501160630749.png)
  - ![image-20200501160659437](C:\Users\Treo\AppData\Roaming\Typora\typora-user-images\image-20200501160659437.png)
  - ![image-20200501160727985](C:\Users\Treo\AppData\Roaming\Typora\typora-user-images\image-20200501160727985.png)

- #### main.c相关代码

  - ```c
    normalize_data(data,col_num);
    	
  	printf(" \n\n Multivariate Linear Regression : \n");
    	 mlr_eva(l_rate, epoch, data, col_num, k);
    	 
    	//生成第一个随机索引数组 
    	rand_index(row_num, 1, index);
    	fold = row_num/k;
    	train_size = fold*(k-1);
    	printf(" \nZero Rule: \n");
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
    ```
    
    


### 3. Perceptron      (25)

- #### 参数说明

  - #####  数据集：Sonar Dataset

  - ##### 数据集分割：cross validation split， 7-fold

  - ##### 学习速率: 0.01

  - ##### 评估指标: accuracy

  - ##### 基准模型: zero rule algorithm

- #### 测试结果

  - **分别用不同的seed(1,39,97),生成不同的训练集-数据集分割多次评估**
  - ![image-20200501122520073](C:\Users\Treo\AppData\Roaming\Typora\typora-user-images\image-20200501122520073.png)
  - ![image-20200501122441820](C:\Users\Treo\AppData\Roaming\Typora\typora-user-images\image-20200501122441820.png)
  - ![image-20200501122550227](C:\Users\Treo\AppData\Roaming\Typora\typora-user-images\image-20200501122550227.png)

- #### main.c相关代码

  - ```c
    	pcep_eva(l_rate, epoch, data, col_num,k);
      	
      	//生成第一个随机索引数组 
      	rand_index(row_num, 1, index);
      	fold = row_num/k;
      	train_size = fold*(k-1);
      	printf("\n Zero Rule: \n");
      	//交叉检验 
      	for(i=0;i<k;i++)
      	{
      		zero_rule(data,col_num,1,index, train_size,count);
      		
      		acc[i] = accuracy(data,col_num,index,train_size);
      		
      		next_fold(fold, row_num, index);
      	}
      	
      	for(i=0;i<k;i++)
      	{
      		temp += acc[i];
      		printf("\n accuracy of fold[%d] : %f",i,acc[i]);
      	}
      	temp /= k;
      	printf("\n average accuracy : %f \n",temp);
    ```

    

### 4. Naive Bayes      (30)

- #### 参数说明

  - #####  数据集：Iris Flower Species Dataset

  - ##### 数据集分割：cross validation split， 7-fold

  - ##### 评估指标: accuracy

  - ##### 基准模型: zero rule algorithm


- #### 测试结果

  - **分别用不同的seed(1,39,97,2021),生成不同的训练集-数据集分割多次评估**
  - ![image-20200501150840585](C:\Users\Treo\AppData\Roaming\Typora\typora-user-images\image-20200501150840585.png)
  - ![image-20200501150909926](C:\Users\Treo\AppData\Roaming\Typora\typora-user-images\image-20200501150909926.png)
  - ![image-20200501150938476](C:\Users\Treo\AppData\Roaming\Typora\typora-user-images\image-20200501150938476.png)
  - ![image-20200501150959950](C:\Users\Treo\AppData\Roaming\Typora\typora-user-images\image-20200501150959950.png)

- #### main.c相关代码

  - ```c
    bayes_top(data,col_num,k);
    	
    	//生成第一个随机索引数组 
    	rand_index(row_num, 2021, index);
    	fold = row_num/k;
    	train_size = fold*(k-1);
    	printf("\n Zero Rule: \n");
    	//交叉检验 
    	for(i=0;i<k;i++)
    	{
    		zero_rule(data,col_num,1,index, train_size,count);
    		
    		acc[i] = accuracy(data,col_num,index,train_size);
    		
    		next_fold(fold, row_num, index);
    	}
    	
    	for(i=0;i<k;i++)
    	{
    		temp += acc[i];
    		printf("\n accuracy of fold[%d] : %f",i,acc[i]);
    	}
    	temp /= k;
    	printf("\n average accuracy : %f \n",temp);
    ```

    

