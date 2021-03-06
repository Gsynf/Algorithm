/*动态规划 分为子问题，重点：因为只要全局前k，所以保留每个格子前k即可，后面的不要
每个点上左上路归并，复杂度O(K),每个点算一次，所以复杂度O(mnk)
*/
#include "pch.h"
#include <iostream>
#include<vector>
#include <algorithm>
#include <string.h>
using namespace std;
int k;
//int NumsOfPaths;
void topk(int a[], int b[], int c[], int s)
{
	int ai = 0, bj = 0, ck = 0;  //三个标识位，分别记录三个数组的下标
	for (int i = 0; i < k; i++)  //c数组没有到达末尾时
	{
		if (a[ai] > b[bj])
			c[ck++] = a[ai++];
		else
			c[ck++] = b[bj++];
	}
	for (int i = 0; i < k; i++)
	{
		if (c[i] != -1)
			c[i] += s;
		else
			break;
	}
	return;
}
/*
int fac(int n)
{
	int m[10];        //假设求10以内整数的阶乘
	m[1] = 1;         //递推的起始值
	for (int i = 2; i <= n; i++)
		m[i] = m[i - 1] * i;
	return m[n];      //返回递推的终值
}
*/
void TopKPaths(int m, int n)
{
	scanf_s("%d", &k);
	//k = min(k, NumsOfPaths);
	int gird[150][150];
	int value[150][150][10];
	memset(value, -1, sizeof(value));
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			scanf_s("%d", &gird[i][j]);
		}
	}
	value[0][0][0] = gird[0][0];
	//printf("随便一个是：%d\n",value[1][0][0]);
	//第一行各点的值确定
	for (int i = 1; i < n; i++)
	{
		value[0][i][0] = value[0][i - 1][0] + gird[0][i];
	}
	//第一列各点的数确定
	for (int i = 1; i < m; i++)
	{
		value[i][0][0] = value[i - 1][0][0] + gird[i][0];
	}

	for (int i = 1; i < m; i++)
	{
		for (int j = 1; j < n; j++)
		{
			int s = gird[i][j];
			topk(value[i - 1][j], value[i][j - 1], value[i][j], s);
		}
	}
	for (int i = 0; i < k - 1; i++)
	{
		if (value[m - 1][n - 1][i] > -1)
			printf("%d ", value[m - 1][n - 1][i]);
		else
		{
			printf("%d ", 0);
		}

	}
	for (int i = k - 1; i < k; i++)       //OJ系统小问题，最后一个输出不能有空格或者换行
	{
		if (value[m - 1][n - 1][i] > -1)
			printf("%d", value[m - 1][n - 1][i]);
		else
		{
			printf("%d", 0);
		}
	}
	return;
}
int main()
{
	int M, N = 0;
	scanf_s("%d %d", &M, &N);
	//NumsOfPaths = fac(M + N - 2) / (fac(M-1)*fac(N-1));
	TopKPaths(M, N);
	return 0;
}





















