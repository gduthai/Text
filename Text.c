#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
typedef struct number {
	int zi;  //保存
	int mu;     //保存分母
}Number;


int gcd(int a, int b){                          //求最大公约数
	return b == 0 ? a : gcd(b, a % b);
}



int lcm(int a, int b) {                         //求最小公倍数：相乘除以最大公约数
	return a * b / gcd(a, b);                
}

void symbolize(Number *num) {                        //分数化简
	int n = gcd(num->zi, num->mu);
	num->zi /= n;                                               //上下除以最大公约数即可化简
	num->mu /= n;
}                          


void calculate(char signal, Number *left, Number *right) {  // 计算函数并化简，结果保存在左边的数中
	int n,m,z;
	n = lcm(left->mu, right->mu);
	m = gcd(left->mu, right->mu);
	if (signal == '+') {
		z = left->zi * right->mu / m + right->zi * left->mu / m;  //求分子
		left->mu = n;
		left->zi = z;
		symbolize(left);
	}
	if (signal == '-') {
		z = left->zi * right->mu / m - right->zi * left->mu / m;  //求分子
		left->mu = n;
		left->zi = z;
		symbolize(left);
	}
	if (signal == '*') {
		left->mu = left->mu * right->mu;
		left->zi = left->zi * right->zi;
		symbolize(left);
	}
	if (signal == '/') {
		left->mu = left->mu * right->zi;
		left->zi = left->zi * right->mu;
		symbolize(left);
	}
}

void main() {
	FILE *fp;
	int n, k, i, p,signalnum23,m;
	int realquestionnum, questionnum, num=10, range=13, length;	//realquestionnum表示实际生成题目数量，questionnum表示有效题目数量，num表示要生成题目数量，range表示运算中出现的数值范围，length用于记录当前的运算长度
	Number count[20][4],result[10]; 	//count用于生成数值并计算，sign用于生成符号并计算，result用于记录结果
	int sign[20][3];	//memorycount用于存储原始数值，memorysign用于存储原始符号
	char nn[2], rr[2];					//用于检测输入指令
	char signal[4] = { '+','-','/','*' };	//用于在输出中显示各个符号
	/*printf("请按-n回车加数字回车您想生成的题目数量\n");
	scanf("%s", nn);
	if (nn[0] != '-' || nn[1] != 'n')
	{
		printf("您的的输入格式不正确，请重试");
		exit(1);
	}
	else scanf("%d", &num);

	printf("请按-r回车后加数字回车您想生成的数值范围\n");
	scanf("%s", rr);
	if (rr[0] != '-' || rr[1] != 'r')
	{
		printf("您的的输入格式不正确，请重试");
		exit(1);
	}
	else scanf("%d", &range);
	*/
	

	questionnum = 0, length = 3;
	for (realquestionnum = 0; realquestionnum < num; realquestionnum++)	//生成 每道题的数还有符号
	{
		for (k = 0; k < 4; k++)
		{	//随机设置四个自然数
			count[realquestionnum][k].zi = rand() % range;
			count[realquestionnum][k].mu = 1;
		}
		for (i = 0; i < 3; i++)	//随机设置三个符号
		{
			sign[realquestionnum][i] = rand() % 4;
		}
	}
	fp = fopen("Test.txt", "w");
	for (realquestionnum = 0; realquestionnum < num; realquestionnum++) {
		fprintf(fp, "%d%c%d%c%d%c%d=\n", count[realquestionnum][0].zi / count[realquestionnum][0].mu, signal[sign[realquestionnum][0]], count[realquestionnum][1].zi / count[realquestionnum][1].mu, signal[sign[realquestionnum][1]], count[realquestionnum][2].zi / count[realquestionnum][2].mu, signal[sign[realquestionnum][2]], count[realquestionnum][3].zi / count[realquestionnum][3].mu);
		printf("%d%c%d%c%d%c%d=\n", count[realquestionnum][0].zi / count[realquestionnum][0].mu, signal[sign[realquestionnum][0]], count[realquestionnum][1].zi / count[realquestionnum][1].mu, signal[sign[realquestionnum][1]], count[realquestionnum][2].zi / count[realquestionnum][2].mu, signal[sign[realquestionnum][2]], count[realquestionnum][3].zi / count[realquestionnum][3].mu);
	}
	fclose(fp);
	// 设定计算长度为3
	for (realquestionnum = 0; realquestionnum < num; realquestionnum++) {               //运算函数
		//printf(" %d %d %d", sign[realquestionnum][0], sign[realquestionnum][1], sign[realquestionnum][2]);
		length = 3;
		signalnum23 = 0;
		for (n = 0; n < length; n++)
			if (sign[realquestionnum][n] == 2 || sign[realquestionnum][n] == 3)
				signalnum23++;                
		n = 0;//计算除号乘号的个数
		while(n <length) {
			m = sign[realquestionnum][n];  
			printf("%d %d",m,n);
			if (m == 2 || m == 3) {                                                                                         //若是乘法或者除法  直接计算
				printf(" %d/%d   %d   %d/%d", count[realquestionnum][n].zi, count[realquestionnum][n].mu, m, count[realquestionnum][n + 1].zi, count[realquestionnum][n + 1].mu);
				calculate(signal[m], &count[realquestionnum][n], &count[realquestionnum][n + 1]);
				result[realquestionnum].zi = count[realquestionnum][n].zi;
				result[realquestionnum].mu = count[realquestionnum][n].mu;
				printf("=%d  %d\n", result[realquestionnum].zi, result[realquestionnum].mu);
				signalnum23--;                
				printf(" \n%d/%d   %d   %d/%d\n", count[realquestionnum][n].zi, count[realquestionnum][n].mu, m, count[realquestionnum][n + 1].zi, count[realquestionnum][n + 1].mu);
                                                              //已经运算则
				for (p = n; p + 2 <= length; p++)	//把符号和数字向前推一格
				{
					count[realquestionnum][p + 1].zi= count[realquestionnum][p + 2].zi;
					count[realquestionnum][p + 1].mu= count[realquestionnum][p + 2].mu;
					sign[realquestionnum][p] = sign[realquestionnum][p + 1];
				}
				printf(" \n%d/%d   %d   %d/%d\n", count[realquestionnum][n].zi, count[realquestionnum][n].mu, m, count[realquestionnum][n + 1].zi, count[realquestionnum][n + 1].mu);
				length--;
				n = 0;
				continue;

			}
			else if (signalnum23 == 0&&(m==0||m==1)) {                                                                                     //是加法而且
				printf(" %d/%d   %d   %d/%d", count[realquestionnum][n].zi, count[realquestionnum][n].mu, m, count[realquestionnum][n + 1].zi, count[realquestionnum][n + 1].mu);
				calculate(signal[m], &count[realquestionnum][n], &count[realquestionnum][n + 1]);
				result[realquestionnum].zi = count[realquestionnum][n].zi;
				result[realquestionnum].mu = count[realquestionnum][n].mu;
				printf("=%d  %d\n", result[realquestionnum].zi, result[realquestionnum].mu);
				printf("\n %d/%d   %d   %d/%d\n", count[realquestionnum][n].zi, count[realquestionnum][n].mu, m, count[realquestionnum][n + 1].zi, count[realquestionnum][n + 1].mu);
				printf("  =%d ", sign[realquestionnum][1]);
				for (p = n; p + 2 <= length; p++) {	//把符号和数字向前推一格
					sign[realquestionnum][p] = sign[realquestionnum][p + 1];
					count[realquestionnum][p + 1].zi = count[realquestionnum][p + 2].zi;
					count[realquestionnum][p + 1].mu = count[realquestionnum][p + 2].mu;
					
				}
				printf("  =%d ", sign[realquestionnum][0]);
				printf("\n %d/%d   %d   %d/%d\n", count[realquestionnum][n].zi, count[realquestionnum][n].mu, m, count[realquestionnum][n + 1].zi, count[realquestionnum][n + 1].mu);
				length--;
			
			}
			n++;
		}
	}
	

	for (realquestionnum = 0; realquestionnum < num; realquestionnum++)
		printf("%d%c%d%c%d%c%d=%d/%d\n", count[realquestionnum][0].zi / count[realquestionnum][0].mu,signal[sign[realquestionnum][0]], count[realquestionnum][1].zi / count[realquestionnum][1].mu, signal[sign[realquestionnum][1]],count[realquestionnum][2].zi / count[realquestionnum][2].mu, signal[sign[realquestionnum][2]], count[realquestionnum][3].zi / count[realquestionnum][3].mu,result[realquestionnum].zi, result[realquestionnum].mu);
	getchar();

	return 0;
	
}

