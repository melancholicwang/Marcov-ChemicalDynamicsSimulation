#include "0312.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "string.h"

int main(){


	struct GlobVariable Glob;
	struct GlobVariable *GlobPointer;

	Glob.mark = 0;                                  //结构体初始化
	Glob.ArrayFlag = 0;
	memset(Glob.LastStatus, 0, sizeof(int) * 9);
	memset(Glob.CacheLastStatus, 0, sizeof(int) * 9);
	memset(Glob.MinStatus, 0, sizeof(double) * 9);
	memset(Glob.MaxStatus, 0, sizeof(double) * 9);
	memset(Glob.CacheAry, 0, sizeof(double) * 9);
	memset(Glob.RecallStatus, 0, sizeof(int) * 9);

	GlobPointer = &Glob;


	FILE *fp = fopen("Data.txt", "r");
	if (fp == NULL)                               //若文件不存在 报错
	{
		printf("Error : Can't open the file.\n");
		exit(1);
	}
	int num = 20;
	double Source[9] = { 0 };
	double data = 0;
	double *result = NULL;
	int IsCorrect = 2;
	int counter = 0;

	/*-------------------------------进行学习(20)---------------------------------*/

	for (int j = 0; j < num; j++) {
		for (int i = 0; i < 9; i++) {
			fscanf(fp, "%lf", &data);
			Source[i] = data;
		}
		data = 0;
		result = marcovp(Source, num, 0, 0, GlobPointer);              //进行学习 此处Result的值为NULL 
	}
	/*
	printf("\n输出ArrayFlag：\n%d\n", GlobPointer->ArrayFlag);

	printf("输出镜像矩阵：\n");
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 3; j++) {
			printf("%d", GlobPointer->MirrorMatrix[8][i][j]);
			counter++;
			if (counter % 4 == 0) {
				printf("\n");
			}
		}
	}

	printf("输出镜像概率分布：\n");
	for (int i = 0; i <= 3; i++) {
		printf("%d\n", GlobPointer->MirrorProbability[8][i]);
	}
	printf("输出预测后的转移矩阵：\n");
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 3; j++) {
			printf("%d", GlobPointer->TransMatrix[8][i][j]);
			counter++;
			if (counter % 4 == 0) {
				printf("\n");
			}
		}
	}
	printf("输出预测后的概率分布：\n");
	for (int i = 0; i <= 3; i++) {
		printf("%d\n", GlobPointer->InitProbability[8][i]);
	}
	*/


	//system("pause");

	/*-------------------------------进行首次预测（21st Step）---------------------------------*/

	double *PredictResult = (double*)calloc(9, sizeof(double));

	PredictResult = marcovp(NULL, num, 1, 0, GlobPointer);                                  //进行预测 输出预测结果

	printf("\n首次预测的值为 :\n");
	for (int i = 0; i < 9; i++) {
		printf("\n%.16e\n", PredictResult[i]);

	}

	system("pause");

	printf("输出CacheAry：\n");
	for (int i = 0; i < 9; i++) {
		printf("%.16e\n", GlobPointer->CacheAry[i]);

	}
	printf("输出CacheLastStatus：\n");
	for (int i = 0; i < 9; i++) {
		printf("%d\n", GlobPointer->CacheLastStatus[i]);
	}

	printf("\n输出ArrayFlag：\n%d\n", GlobPointer->ArrayFlag);


	printf("输出镜像矩阵：\n");
	counter = 0;
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 3; j++) {
			printf("%d", GlobPointer->MirrorMatrix[8][i][j]);
			counter++;
			if (counter % 4 == 0) {
				printf("\n");
			}
		}
	}

	printf("输出镜像概率分布：\n");
	for (int i = 0; i <= 3; i++) {
		printf("%d\n", GlobPointer->MirrorProbability[8][i]);
	}
	printf("输出预测后的转移矩阵：\n");
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 3; j++) {
			printf("%d", GlobPointer->TransMatrix[8][i][j]);
			counter++;
			if (counter % 4 == 0) {
				printf("\n");
			}
		}
	}
	printf("输出预测后的概率分布：\n");
	for (int i = 0; i <= 3; i++) {
		printf("%d\n", GlobPointer->InitProbability[8][i]);
	}


	//system("pause");

	/*-------------------------------不准确，回溯并再次预测(21st Step)---------------------------------*/

	printf("\n假设预测不准确 \n");
	IsCorrect = 0;

	//这里还要加一个是否已经回溯过的判断

	if (!IsCorrect){
		PredictResult = marcovp(NULL, num, 1, 1, GlobPointer);
	}

	printf("\n回溯后的预测值为： \n");

	for (int i = 0; i < 9; i++) {
		printf("\n%.16e\n", PredictResult[i]);

	}
	printf("输出CacheAry：\n");
	for (int i = 0; i < 9; i++) {
		printf("%.16e\n", GlobPointer->CacheAry[i]);
	}

	printf("输出CacheLastStatus：\n");
	for (int i = 0; i < 9; i++) {
		printf("%d\n", GlobPointer->CacheLastStatus[i]);
	}

	printf("\n输出ArrayFlag：\n%d\n", GlobPointer->ArrayFlag);
	//system("pause");

	printf("输出镜像矩阵：\n");
	counter = 0;
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 3; j++) {
			printf("%d", GlobPointer->MirrorMatrix[8][i][j]);
			counter++;
			if (counter % 4 == 0) {
				printf("\n");
			}
		}
	}
	printf("输出镜像概率分布：\n");
	for (int i = 0; i <= 3; i++) {
		printf("%d\n", GlobPointer->MirrorProbability[8][i]);
	}
	printf("输出预测后的转移矩阵：\n");
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 3; j++) {
			printf("%d", GlobPointer->TransMatrix[8][i][j]);
			counter++;
			if (counter % 4 == 0) {
				printf("\n");
			}
		}
	}
	printf("输出预测后的概率分布：\n");
	for (int i = 0; i <= 3; i++) {
		printf("%d\n", GlobPointer->InitProbability[8][i]);
	}

	/*----------------------------不准确，21步进行学习(21st Step)---------------------------------*/

	printf("\n假设预测不准确，那么下一步进行学习 \n");
	Source[0] = 5.166034207867376E-004;
	Source[1] = 4.346928501697935E-004;
	Source[2] = 4.750490770142530E-004;
	Source[3] = -1.970079378272880E-003;
	Source[4] = -1.546372660686910E-004;
	Source[5] = -1.689935046106157E-004;
	Source[6] = 1.582613378448928E-003;
	Source[7] = -1.713949095850274E-004;
	Source[8] = -1.873067980043166E-004;

	result = marcovp(Source, num + 1, 0, 0, GlobPointer);

	printf("输出LastStatus：\n");
	for (int i = 0; i < 9; i++) {
		printf("%d\n", GlobPointer->LastStatus[i]);
	}
	printf("\n输出ArrayFlag：\n%d\n", GlobPointer->ArrayFlag);

	printf("输出镜像矩阵：\n");
	counter = 0;
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 3; j++) {
			printf("%d", GlobPointer->MirrorMatrix[8][i][j]);
			counter++;
			if (counter % 4 == 0) {
				printf("\n");
			}
		}
	}
	printf("输出镜像概率分布：\n");
	for (int i = 0; i <= 3; i++) {
		printf("%d\n", GlobPointer->MirrorProbability[8][i]);
	}
	printf("输出预测后的转移矩阵：\n");
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 3; j++) {
			printf("%d", GlobPointer->TransMatrix[8][i][j]);
			counter++;
			if (counter % 4 == 0) {
				printf("\n");
			}
		}
	}
	printf("输出预测后的概率分布：\n");
	for (int i = 0; i <= 3; i++) {
		printf("%d\n", GlobPointer->InitProbability[8][i]);
	}


	/*
	for (int i = 0; i < 9; i++) {
	printf("%d\n",NumOfPositiveStatus[i]);
	}
	for (int i = 0; i < 9; i++) {
	printf("%d\n", NumOfNegativeStatus[i]);
	}
	*/
	/*-----------------------------准确，继续预测（22nd Step）-----------------------------------*/
	/*
	printf("\n假设预测准确 那么继续预测下一步 \n");
	IsCorrect = 1;

	if (IsCorrect){
	PredictResult = marcovp(NULL, num + 1, 1, 0);
	}

	/*
	int Flag = 0;
	for (int i = 1; i <= num + 1; i++) {
	for (int j = Flag; j < i * 9; j++) {
	printf("输出录入的几个值，包括预测准确值%.16e!!!!!!!", SourceDataAry[j]);
	printf("------%d\n", j);
	}
	Flag = Flag + 9;
	}

	printf("\n第%d步的预测值是： \n", num + 2);


	for (int i = 0; i < 9; i++) {
	printf("\n%.16e\n", PredictResult[i]);
	}

	//system("pause");
	printf("输出CacheAry：\n");
	for (int i = 0; i < 9; i++) {
	printf("%.16e\n", GlobPointer->CacheAry[i]);
	}

	printf("输出CacheLastStatus：\n");
	for (int i = 0; i < 9; i++) {
	printf("%d\n", GlobPointer->CacheLastStatus[i]);
	}
	printf("\n输出ArrayFlag：\n%d\n", GlobPointer->ArrayFlag);

	printf("输出镜像矩阵：\n");
	counter = 0;
	for (int i = 0; i <= 3; i++) {
	for (int j = 0; j <= 3; j++) {
	printf("%d", GlobPointer->MirrorMatrix[8][i][j]);
	counter++;
	if (counter % 4 == 0) {
	printf("\n");
	}
	}
	}
	printf("输出镜像概率分布：\n");
	for (int i = 0; i <= 3; i++) {
	printf("%d\n",GlobPointer->MirrorProbability[8][i]);
	}
	printf("输出预测后的转移矩阵：\n");
	for (int i = 0; i <= 3; i++) {
	for (int j = 0; j <= 3; j++) {
	printf("%d", GlobPointer->TransMatrix[8][i][j]);
	counter++;
	if (counter % 4 == 0) {
	printf("\n");
	}
	}
	}
	printf("输出预测后的概率分布：\n");
	for (int i = 0; i <= 3; i++) {
	printf("%d\n", GlobPointer->InitProbability[8][i]);
	}

	*/
	/*--------------------预测第22步(22nd Step)----------------------*/

	printf("第21步预测不准确，学习一步，预测第22步：\n");
	PredictResult = marcovp(NULL, num + 1, 1, 0, GlobPointer);
	/*
	int Flag = 0;
	for (int i = 1; i <=  num + 1; i++) {
	for (int j = Flag; j < i * 9; j++) {
	printf("输出录入的几个值，包括预测准确值%.16e!!!!!!!", GlobPointer->SourceDataAry[j]);
	printf("------%d\n", j);
	}
	Flag = Flag + 9;
	}
	*/
	printf("\n第%d步的预测值是： \n", num + 2);


	for (int i = 0; i < 9; i++) {
		printf("\n%.16e\n", PredictResult[i]);
	}


	//system("pause");
	printf("输出CacheAry：\n");
	for (int i = 0; i < 9; i++) {
		printf("%.16e\n", GlobPointer->CacheAry[i]);
	}

	printf("输出CacheLastStatus：\n");
	for (int i = 0; i < 9; i++) {
		printf("%d\n", GlobPointer->CacheLastStatus[i]);
	}
	printf("\n输出ArrayFlag：\n%d\n", GlobPointer->ArrayFlag);

	printf("输出镜像矩阵：\n");
	counter = 0;
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 3; j++) {
			printf("%d", GlobPointer->MirrorMatrix[8][i][j]);
			counter++;
			if (counter % 4 == 0) {
				printf("\n");
			}
		}
	}
	printf("输出镜像概率分布：\n");
	for (int i = 0; i <= 3; i++) {
		printf("%d\n", GlobPointer->MirrorProbability[8][i]);
	}
	printf("输出预测后的转移矩阵：\n");
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 3; j++) {
			printf("%d", GlobPointer->TransMatrix[8][i][j]);
			counter++;
			if (counter % 4 == 0) {
				printf("\n");
			}
		}
	}
	printf("输出预测后的概率分布：\n");
	for (int i = 0; i <= 3; i++) {
		printf("%d\n", GlobPointer->InitProbability[8][i]);
	}

	/*-------------------预测准确，继续预测第23步------------------*/

	printf("第22步预测准确，继续预测第23步：\n");
	PredictResult = marcovp(NULL, num + 2, 1, 0, GlobPointer);                                  //进行预测 输出预测结果

	/*
	int Flag = 0;
	for (int i = 1; i <=  num + 2; i++) {
	for (int j = Flag; j < i * 9; j++) {
	printf("输出录入的几个值，包括预测准确值%.16e!!!!!!!", SourceDataAry[j]);
	printf("------%d\n", j);
	}
	Flag = Flag + 9;
	}
	*/

	printf("\n首次预测的值为 :\n");
	for (int i = 0; i < 9; i++) {
		printf("\n%.16e\n", PredictResult[i]);

	}

	printf("输出CacheAry：\n");
	for (int i = 0; i < 9; i++) {
		printf("%.16e\n", GlobPointer->CacheAry[i]);

	}
	printf("输出CacheLastStatus：\n");
	for (int i = 0; i < 9; i++) {
		printf("%d\n", GlobPointer->CacheLastStatus[i]);
	}

	printf("\n输出ArrayFlag：\n%d\n", GlobPointer->ArrayFlag);


	printf("输出镜像矩阵：\n");
	counter = 0;
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 3; j++) {
			printf("%d", GlobPointer->MirrorMatrix[8][i][j]);
			counter++;
			if (counter % 4 == 0) {
				printf("\n");
			}
		}
	}

	printf("输出镜像概率分布：\n");
	for (int i = 0; i <= 3; i++) {
		printf("%d\n", GlobPointer->MirrorProbability[8][i]);
	}
	printf("输出预测后的转移矩阵：\n");
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 3; j++) {
			printf("%d", GlobPointer->TransMatrix[8][i][j]);
			counter++;
			if (counter % 4 == 0) {
				printf("\n");
			}
		}
	}
	printf("输出预测后的概率分布：\n");
	for (int i = 0; i <= 3; i++) {
		printf("%d\n", GlobPointer->InitProbability[8][i]);
	}
	/*-----------------预测准确，继续第24步--------------*/

	printf("第23步预测准确，继续预测第24步：\n");
	PredictResult = marcovp(NULL, num + 3, 1, 0, GlobPointer);                                  //进行预测 输出预测结果

	/*
	int Flag = 0;
	for (int i = 1; i <=  num + 3; i++) {
	for (int j = Flag; j < i * 9; j++) {
	printf("输出录入的几个值，包括预测准确值%.16e!!!!!!!", GlobPointer->SourceDataAry[j]);
	printf("------%d\n", j);
	}
	Flag = Flag + 9;
	}
	*/

	printf("\n首次预测的值为 :\n");
	for (int i = 0; i < 9; i++) {
		printf("\n%.16e\n", PredictResult[i]);

	}

	printf("输出CacheAry：\n");
	for (int i = 0; i < 9; i++) {
		printf("%.16e\n", GlobPointer->CacheAry[i]);

	}
	printf("输出CacheLastStatus：\n");
	for (int i = 0; i < 9; i++) {
		printf("%d\n", GlobPointer->CacheLastStatus[i]);
	}

	printf("\n输出ArrayFlag：\n%d\n", GlobPointer->ArrayFlag);


	printf("输出镜像矩阵：\n");
	counter = 0;
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 3; j++) {
			printf("%d", GlobPointer->MirrorMatrix[8][i][j]);
			counter++;
			if (counter % 4 == 0) {
				printf("\n");
			}
		}
	}

	printf("输出镜像概率分布：\n");
	for (int i = 0; i <= 3; i++) {
		printf("%d\n", GlobPointer->MirrorProbability[8][i]);
	}
	printf("输出预测后的转移矩阵：\n");
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 3; j++) {
			printf("%d", GlobPointer->TransMatrix[8][i][j]);
			counter++;
			if (counter % 4 == 0) {
				printf("\n");
			}
		}
	}
	printf("输出预测后的概率分布：\n");
	for (int i = 0; i <= 3; i++) {
		printf("%d\n", GlobPointer->InitProbability[8][i]);
	}
	/*--------------------不准确，回溯并再次预测(24th step)----------------*/

	printf("假设预测不正确，24步进行回溯：\n");

	PredictResult = marcovp(NULL, num + 3, 1, 1, GlobPointer);

	printf("\n回溯后的预测值为： \n");

	for (int i = 0; i < 9; i++) {
		printf("\n%.16e\n", PredictResult[i]);

	}
	printf("输出CacheAry：\n");
	for (int i = 0; i < 9; i++) {
		printf("%.16e\n", GlobPointer->CacheAry[i]);
	}

	printf("输出CacheLastStatus：\n");
	for (int i = 0; i < 9; i++) {
		printf("%d\n", GlobPointer->CacheLastStatus[i]);
	}

	printf("\n输出ArrayFlag：\n%d\n", GlobPointer->ArrayFlag);
	//system("pause");

	printf("输出镜像矩阵：\n");
	counter = 0;
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 3; j++) {
			printf("%d", GlobPointer->MirrorMatrix[8][i][j]);
			counter++;
			if (counter % 4 == 0) {
				printf("\n");
			}
		}
	}
	printf("输出镜像概率分布：\n");
	for (int i = 0; i <= 3; i++) {
		printf("%d\n", GlobPointer->MirrorProbability[8][i]);
	}
	printf("输出预测后的转移矩阵：\n");
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 3; j++) {
			printf("%d", GlobPointer->TransMatrix[8][i][j]);
			counter++;
			if (counter % 4 == 0) {
				printf("\n");
			}
		}
	}
	printf("输出预测后的概率分布：\n");
	for (int i = 0; i <= 3; i++) {
		printf("%d\n", GlobPointer->InitProbability[8][i]);
	}


	/*----------------------------不准确，24步进行学习(24st Step)---------------------------------*/

	printf("\n假设预测不准确，那么下一步进行学习 \n");
	Source[0] = -2.048813751117822E-003;
	Source[1] = 4.004778675943675E-004;
	Source[2] = 4.376575131231622E-004;
	Source[3] = -9.474301144078221E-004;
	Source[4] = -1.804036805887809E-004;
	Source[5] = -1.971520164739591E-004;
	Source[6] = 2.484093252582885E-003;
	Source[7] = -1.199679649359405E-004;
	Source[8] = -1.311054411939462E-004;

	result = marcovp(Source, num + 4, 0, 0, GlobPointer);
	/*
	int Flag = 0;
	for (int i = 1; i <= num + 4; i++) {
	for (int j = Flag; j < i * 9; j++) {
	printf("输出录入的几个值，包括预测准确值%.16e!!!!!!!", GlobPointer->SourceDataAry[j]);
	printf("------%d\n", j);
	}
	Flag = Flag + 9;
	}
	*/
	printf("输出LastStatus：\n");
	for (int i = 0; i < 9; i++) {
		printf("%d\n", GlobPointer->LastStatus[i]);
	}
	printf("\n输出ArrayFlag：\n%d\n", GlobPointer->ArrayFlag);

	printf("输出镜像矩阵：\n");
	counter = 0;
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 3; j++) {
			printf("%d", GlobPointer->MirrorMatrix[8][i][j]);
			counter++;
			if (counter % 4 == 0) {
				printf("\n");
			}
		}
	}
	printf("输出镜像概率分布：\n");
	for (int i = 0; i <= 3; i++) {
		printf("%d\n", GlobPointer->MirrorProbability[8][i]);
	}
	printf("输出预测后的转移矩阵：\n");
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 3; j++) {
			printf("%d", GlobPointer->TransMatrix[8][i][j]);
			counter++;
			if (counter % 4 == 0) {
				printf("\n");
			}
		}
	}
	printf("输出预测后的概率分布：\n");
	for (int i = 0; i <= 3; i++) {
		printf("%d\n", GlobPointer->InitProbability[8][i]);
	}


	/*-----------------第24步学习，接下来预测第25步-------------*/

	printf("第24步预测不准确，学习一步，预测第25步：\n");
	PredictResult = marcovp(NULL, num + 4, 1, 0, GlobPointer);
	/*
	int Flag = 0;
	for (int i = 1; i <= num + 4; i++) {
	for (int j = Flag; j < i * 9; j++) {
	printf("输出录入的几个值，包括预测准确值%.16e!!!!!!!", GlobPointer->SourceDataAry[j]);
	printf("------%d\n", j);
	}
	Flag = Flag + 9;
	}
	*/
	printf("\n第%d步的预测值是： \n", num + 5);


	for (int i = 0; i < 9; i++) {
		printf("\n%.16e\n", PredictResult[i]);
	}


	//system("pause");
	printf("输出CacheAry：\n");
	for (int i = 0; i < 9; i++) {
		printf("%.16e\n", GlobPointer->CacheAry[i]);
	}

	printf("输出CacheLastStatus：\n");
	for (int i = 0; i < 9; i++) {
		printf("%d\n", GlobPointer->CacheLastStatus[i]);
	}
	printf("\n输出ArrayFlag：\n%d\n", GlobPointer->ArrayFlag);

	printf("输出镜像矩阵：\n");
	counter = 0;
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 3; j++) {
			printf("%d", GlobPointer->MirrorMatrix[8][i][j]);
			counter++;
			if (counter % 4 == 0) {
				printf("\n");
			}
		}
	}
	printf("输出镜像概率分布：\n");
	for (int i = 0; i <= 3; i++) {
		printf("%d\n", GlobPointer->MirrorProbability[8][i]);
	}
	printf("输出预测后的转移矩阵：\n");
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 3; j++) {
			printf("%d", GlobPointer->TransMatrix[8][i][j]);
			counter++;
			if (counter % 4 == 0) {
				printf("\n");
			}
		}
	}
	printf("输出预测后的概率分布：\n");
	for (int i = 0; i <= 3; i++) {
		printf("%d\n", GlobPointer->InitProbability[8][i]);
	}

	free(PredictResult);
	PredictResult = NULL;
	fclose(fp);
	system("pause");

	return 0;

}
