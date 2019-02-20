// algorithm4_2_2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

#define maxn (50)
#define eps (1e-20)

float z1, z2, z3, z4, z5, z6, z7, z8, z9, z0;
int N, M, op, tot, q[maxn], idx[maxn], idy[maxn];
float a[maxn][maxn], A[maxn];

inline void pivot(int x, int y)
{
	swap(idy[x], idx[y]);
	float tmp = a[x][y];
	a[x][y] = 1 / a[x][y];
	tot = 0;
	for (int i = 0; i <= N; ++i)
		if (y != i)
			a[x][i] /= tmp;

	for (int i = 0; i <= N; ++i)
		if (i != y && (a[x][i] > eps || a[x][i] < -eps))
			q[++tot] = i;
	for (int i = 0; i <= M; ++i)
	{
		if ((x == i) || (a[i][y] < eps&&a[i][y] > -eps))
			continue;
		for (int j = 1; j <= tot; ++j)
			a[i][q[j]] -= a[x][q[j]] * a[i][y];
		a[i][y] = -a[i][y] / tmp;
	}
}

int main()
{
	N = 6;
	M = 14;
	op = 1;

	scanf_s("%f %f %f %f %f %f %f %f %f %f", &z1, &z2, &z3, &z4, &z5, &z6, &z7, &z8, &z9, &z0);
	for (int i = 1; i<N; i++)
	{
		a[0][i] = 0;
	}
	a[0][N] = 1;

	/*for (int i = 1;i <= M;++i)
	{
	for (int j = 1;j <= N;++j) scanf("%lf",a[i]+j);
	scanf("%lf",a[i]);

	}*/

	a[1][1] = 1;
	a[1][2] = -1;
	a[1][3] = 0;
	a[1][4] = 0;
	a[1][5] = 0;
	a[1][6] = 1;
	a[1][0] = 0;


	a[2][1] = 0;
	a[2][2] = 1;
	a[2][3] = -1;
	a[2][4] = 0;
	a[2][5] = 0;
	a[2][6] = 1;
	a[2][0] = 0;

	a[3][1] = 0;
	a[3][2] = 0;
	a[3][3] = 1;
	a[3][4] = -1;
	a[3][5] = 0;
	a[3][6] = 1;
	a[3][0] = 0;

	a[4][1] = 0;
	a[4][2] = 0;
	a[4][3] = 0;
	a[4][4] = 1;
	a[4][5] = -1;
	a[4][6] = 1;
	a[4][0] = 0;

	a[5][1] = -1;
	a[5][2] = 0;
	a[5][3] = 0;
	a[5][4] = 0;
	a[5][5] = 0;
	a[5][6] = 0;
	a[5][0] = -z1;

	a[6][1] = 1;
	a[6][2] = 0;
	a[6][3] = 0;
	a[6][4] = 0;
	a[6][5] = 0;
	a[6][6] = 0;
	a[6][0] = z2;

	a[7][1] = 0;
	a[7][2] = -1;
	a[7][3] = 0;
	a[7][4] = 0;
	a[7][5] = 0;
	a[7][6] = 0;
	a[7][0] = -z3;

	a[8][1] = 0;
	a[8][2] = 1;
	a[8][3] = 0;
	a[8][4] = 0;
	a[8][5] = 0;
	a[8][6] = 0;
	a[8][0] = z4;

	a[9][1] = 0;
	a[9][2] = 0;
	a[9][3] = -1;
	a[9][4] = 0;
	a[9][5] = 0;
	a[9][6] = 0;
	a[9][0] = -z5;

	a[10][1] = 0;
	a[10][2] = 0;
	a[10][3] = 1;
	a[10][4] = 0;
	a[10][5] = 0;
	a[10][6] = 0;
	a[10][0] = z6;

	a[11][1] = 0;
	a[11][2] = 0;
	a[11][3] = 0;
	a[11][4] = -1;
	a[11][5] = 0;
	a[11][6] = 0;
	a[11][0] = -z7;

	a[12][1] = 0;
	a[12][2] = 0;
	a[12][3] = 0;
	a[12][4] = 1;
	a[12][5] = 0;
	a[12][6] = 0;
	a[12][0] = z8;

	a[13][1] = 0;
	a[13][2] = 0;
	a[13][3] = 0;
	a[13][4] = 0;
	a[13][5] = -1;
	a[13][6] = 0;
	a[13][0] = -z9;

	a[14][1] = 0;
	a[14][2] = 0;
	a[14][3] = 0;
	a[14][4] = 0;
	a[14][5] = 1;
	a[14][6] = 0;
	a[14][0] = z0;

	for (int i = 1; i <= N; ++i)
		idx[i] = i;
	for (int i = 1; i <= M; ++i)
		idy[i] = i + N;
	while (true)
	{
		int x = 0, y = 0;
		for (int i = 1; i <= M; ++i)
			if (a[i][0] < -eps && ((!x) || (rand() & 1)))
				x = i;
		if (!x)
			break;
		for (int i = 1; i <= N; ++i)
			if (a[x][i] < -eps && ((!y) || (rand() & 1)))
				y = i;
		if (!y)
			return puts("Infeasible"), 0;
		pivot(x, y);
	}
	while (true)
	{
		int x = 0, y = 0;
		float mn = 1e15;
		for (int i = 1; i <= N; ++i)
			if (a[0][i] > eps)
			{
				y = i; break;
			}
		if (!y)
			break;
		for (int i = 1; i <= M; ++i)
			if (a[i][y] > eps && a[i][0] / a[i][y] < mn)
				mn = a[i][0] / a[i][y], x = i;
		if (!x)
			return puts("Unbounded"), 0;
		pivot(x, y);
	}

	for (int i = 1; i <= M; ++i)
		if (idy[i] <= N)
			A[idy[i]] = a[i][0];
	for (int i = 1; i < N - 1; ++i)
	{
		printf("%.2f ", A[i]);
	}
	printf("%.2f", A[N - 1]);
	return 0;
}

