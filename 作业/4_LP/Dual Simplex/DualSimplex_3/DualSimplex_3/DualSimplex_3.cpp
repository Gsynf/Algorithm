// DualSimplex_3.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include  <iostream>
#include  <conio.h>
#include  <math.h>
#include  <stdio.h>
using  namespace std;

typedef   int   BOOL;
#define   TRUE   1
#define   FALSE   0
typedef   double   REAL;
#define   ZERO   1e-10

//矩阵求逆
BOOL   Inv(REAL   **   a, int   n);
BOOL   Inv(REAL   *   a, int   n);

//矩阵相乘
void   Damul(REAL   *   a, REAL   *   b, size_t   m, size_t   n, size_t   k, REAL   *   c);

//线形规划--修正的单纯形法,返回真表示计算成功，返回假表示计算失败
BOOL   Line_Optimize(REAL   *   A, REAL   *   B, REAL   *   C, int   m, int   n,
	REAL   *   Result, REAL   *   X, int   *   Is);
//A-----------等式约束的系数矩阵
//B-----------等式约束右端常数
//C-----------所求最小值表达式的各项系数
//m-----------系数矩阵行数
//n-----------系数矩阵列
//Result------返回最小值
//X-----------返回计算结果
//Is----------作为基底的X索引,计算结束后返回各X值所在索引//非基向量行数

template   <class   T>
inline   void   ExChange(T&   a, T&   b)
{
	T   temp = a;
	a = b;
	b = temp;
}


BOOL   Inv(REAL   **   a, int   n)
{
	REAL   d;
	int   i, j, k;
	int   success = FALSE;
	int   *   is = new   int[n];
	int   *   js = new   int[n];

	for (k = 0; k <n; k++) {
		d = 0.0;
		for (i = k; i <n; i++) {
			for (j = k; j <n; j++) {
				if (fabs(a[i][j])> d) {
					d = fabs(a[i][j]);
					is[k] = i;
					js[k] = j;
				}
			}
		}

		if (d <ZERO)   goto   Clear;

		for (j = 0; j <n; j++)ExChange(a[k][j], a[is[k]][j]);

		for (i = 0; i <n; i++)ExChange(a[i][k], a[i][js[k]]);

		a[k][k] = 1 / a[k][k];

		for (j = 0; j <n; j++) {
			if (j != k)a[k][j] *= a[k][k];
		}

		for (i = 0; i <n; i++) {
			if (i != k) {
				for (j = 0; j <n; j++)
					if (j != k)a[i][j] -= a[i][k] * a[k][j];
			}
		}

		for (i = 0; i <n; i++) {
			if (i != k) {
				a[i][k] *= ((-1.0)*a[k][k]);
			}
		}

	}   //end   for

	for (k = (n - 1); k >= 0; k--)
	{
		for (j = 0; j <n; j++)
			ExChange(a[k][j], a[js[k]][j]);

		for (i = 0; i <n; i++)
			ExChange(a[i][k], a[i][is[k]]);
	}
	success = TRUE;
Clear:
	delete[]   is;
	delete[]   js;
	return   success;
}


BOOL   Inv(REAL   *   a, int   n)
{
	REAL   **kma = new   REAL*[n];
	for (int i = 0; i <n; i++) {
		kma[i] = a + i*n;
	}
	BOOL   ret = Inv(kma, n);
	delete[]   kma;
	return   ret;
}

void   Damul(REAL   *   a, REAL   *   b, size_t   m, size_t   n, size_t   k, REAL   *   c)
{
	unsigned int   i, j, l, u;
	for (i = 0; i <= (m - 1); i++)
	{
		for (j = 0; j <= (k - 1); j++)
		{
			u = i*k + j;
			c[u] = 0.0;
			for (l = 0; l <= n - 1; l++)
			{
				c[u] += a[i*n + l] * b[l*k + j];
			}
		}
	}
	return;
}


BOOL   Line_Optimize(REAL   *   A, REAL   *   B, REAL   *   C, int   m, int   n,
	REAL   *   Result, REAL   *   X, int   *   Is)
{
	REAL   r;
	int   i, j, k;
	int   Success = FALSE;
	REAL*   b = new   REAL[m*m];
	REAL*   MatTmp = new   REAL[m*m];
	REAL*   Mat1 = new   REAL[m];
	REAL*   Mat2 = new   REAL[m];
	REAL*   E = new   REAL[m*m];

	for (i = 0; i <m; i++) {
		for (j = 0; j <m; j++) {
			b[i*m + j] = A[i*n + Is[j]];
		}
	}

	if (!Inv(b, m)) {
		goto   Release;
	}

	Damul(b, B, m, m, 1, X);


	for (;;) {
		for (i = 0; i <m; i++) {
			Mat2[i] = C[Is[i]];
		}
		Damul(Mat2, b, 1, m, m, Mat1);

		for (i = 0; i <n; i++) {
			for (j = 0; j <m; j++) {
				Mat2[j] = A[j*n + i];
			}
			Damul(Mat1, Mat2, 1, m, 1, &r);
			r = C[i] - r;
			if (r <-ZERO) {
				break;
			}
		}

		if (i >= n)
		{
			*Result = 0;
			for (i = 0; i <m; i++) {
				*Result += C[Is[i]] * X[i];
			}
			Success = TRUE;
			goto   Release;
		}

		Damul(b, Mat2, m, m, 1, Mat1);

		r = 1E10;
		j = -1;
		for (k = 0; k <m; k++) {
			if (Mat1[k]> ZERO) {
				REAL   temp = X[k] / Mat1[k];
				if (temp <r) {
					r = temp;
					j = k;
				}
			}
		}

		if (j   <   0) {
			Success = FALSE;
			goto   Release;
		}

		for (k = 0; k <m*m; k++) {
			E[k] = 0;
		}

		for (k = 0; k <m; k++) {
			E[k*m + k] = 1;
		}

		for (k = 0; k <m; k++) {
			E[k*m + j] = -Mat1[k] / Mat1[j];
		}
		E[j*m + j] = 1 / Mat1[j];

		Is[j] = i;

		Damul(E, b, m, m, m, MatTmp);
		Damul(E, X, m, m, 1, Mat2);

		for (i = 0; i <m*m; i++) {
			b[i] = MatTmp[i];
		}

		for (i = 0; i <m; i++) {
			X[i] = Mat2[i];
		}
	}

Release:
	delete[]   E;
	delete[]   Mat2;
	delete[]   Mat1;
	delete[]   MatTmp;
	delete[]   b;
	return   Success;
}
void   main()
{
	REAL   A[] = {
		3, -1, 1, -2, 0, 0,
		2,  1, 0,  1, 1, 0,
		-1, 3, 0, -3, 0, 1,
	};
	REAL   B[] = {
		-3,4,12
	};
	REAL   C[] = {
		-7, 7, -2, -1, -6, 0
	};
	REAL   RESULT;
	REAL   x[3];
	int   Is[] = {
		0,1,3
	};

	if (!Line_Optimize(A, B, C, 3, 6, &RESULT, x, Is)) {
		cout << "Calculate   Wrong! " << endl;
		return;
	}

	for (int i = 0; i <3; i++) {
		cout << "The   X " << Is[i] << " is: " << x[i] << endl;
	}

	cout << "The   other    variables   is   0. " << endl;
	cout << "The   Minmize   value   is:   " << RESULT << endl;
}

