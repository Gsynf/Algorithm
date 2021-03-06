/*动态规划 分为子问题：  每一个点的可到达路径数=左边一个点的可到达路径数+上边一个点的可到达路径数，
the number of paths to arrive at a point (i, j) is denoted as P[i][j], it is easily concluded that P[i][j] = P[i - 1][j] + P[i][j - 1].
*/
//建一个value[m][n][v]的三维数组, m, n就表示（m, n）的点，v表示这个点的所有可能路径总和，然后DP，
//每个点的value就是左边点的value加上这个点的权重以及上边点的value加上这个点的权重，
//最后把（m, n）的value的第三维赋给一个一维数组，再排序

#include "pch.h"
#include <iostream>
#include<vector>
#include <algorithm>

using namespace std;

int NumsOfPaths(int m, int n)
{
	vector<vector<int>> P(m + 1, vector<int>(n + 1));    //建m*n表格，
	//The boundary conditions of the above equation occur at the leftmost column(P[i][j - 1] does not exist) and the uppermost row(P[i - 1][j] does not exist).
	//These conditions can be handled by initialization(pre - processing)-- - initialize P[0][j] = 1, P[i][0] = 1 for all valid i, j.Note the initial value is 1 instead of 0
	P[0][0] = 1;
	//第一行各点为1
	for (int i = 1; i < P.size(); i++)   //i<P.size()
	{
		P[i][0] = 1;
	}
	//第一列各点为1
	for (int i = 1; i < P[0].size(); i++)   //i < P[0].size()
	{
		P[0][i] = 1;
	}
	for (int i = 1; i < P.size(); i++)
	{
		for (int j = 1; j < P[0].size(); j++)
		{
			P[i][j] = P[i - 1][j] + P[i][j - 1];
		}
	}
	return P[m - 1][n - 1];
}

void Paths(int m, int n, int p[])
{
	int k = 1;
	scanf_s("%d", &k);
	int gird[100][100];
	int value[100][100][20];
	/*int ***value;
	value = new int **[m];
	for (int i = 0; i < m; i++)
		{
			 value[i] = new int *[n];
			 for (int j = 0; j < n; j++)
				 {
					  value[i][j] = new int[10];
				 }
		} */  //用于存放走到当前点所有的可能价值
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			scanf_s("%d", &gird[i][j]);
		}
	}

	value[0][0][0] = gird[0][0];
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
			for (int s = 0; s < int(NumsOfPaths(i+1, j+1)); s++)
			{
				if (s < int(NumsOfPaths(i+1, j)))
					value[i][j][s] = value[i][j - 1][s] + gird[i][j];
				if (s >= int(NumsOfPaths(i+1, j)) && s < int(NumsOfPaths(i+1, j+1)))
					value[i][j][s] = value[i - 1][j][s - int(NumsOfPaths(i+1, j))] + gird[i][j];
			}
		}
	}
	for (int i = 0; i < int(NumsOfPaths(m, n)); i++)
	{
		p[i] = value[m - 1][n - 1][i];
		//printf("%d ", p[i]);
	}
	sort(p, p + int(NumsOfPaths(m, n)), greater<int>());
	for (int i = 0; i < k-1; i++)
	{
		if (i < int(NumsOfPaths(m, n)))
			printf("%d\n", p[i]);
		else 
			printf("%d\n", 0);
	}
	for (int i = k-1; i < k; i++)       //OJ系统小问题，最后一个输出不能有空格或者换行
	{
		if (i < int(NumsOfPaths(m, n)))
			printf("%d", p[i]);
		else
			printf("%d", 0);
	}
}

int main()
{
	int M, N = 0;
	int p[100];
	scanf_s("%d %d", &M, &N);
	//printf(" num is %d\n", NumsOfPaths(M, N));
	Paths(M, N, p);

	return 0;
}