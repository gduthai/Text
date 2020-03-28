#include<stdio.h>
#include<stdlib.h>
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
	Number num1 = { 13,2 }, num2 = { 4 , 3 };
	calculate('*', &num1, &num2);
	printf("%d/%d", num1.zi,num1.mu);
}

