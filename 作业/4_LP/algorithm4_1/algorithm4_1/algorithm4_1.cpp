// algorithm4_1.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
using namespace std;

const int max_n = 205;
const int max_m = 1010;
const double eps = 1e-7;
const double inf = 1e10;

int n, m, L, R;
double A[max_m][max_n], B[max_m], C[max_n], ans;         //分别为课上的A,B,C

inline void pivot(int l, int e) {
	B[l] /= A[l][e];
	for (int i = 1; i <= n; ++i)
		if (i != e)
			A[l][i] /= A[l][e];
	A[l][e] = 1 / A[l][e];

	for (int i = 1; i <= m; ++i)
		if (i != l&&fabs(A[i][e])>eps) {
			B[i] -= B[l] * A[i][e];
			for (int j = 1; j <= n; ++j)
				if (j != e)
					A[i][j] -= A[l][j] * A[i][e];
			A[i][e] = -A[l][e] * A[i][e];
		}

	ans += B[l] * C[e];
	for (int i = 1; i <= n; ++i)
		if (i != e)
			C[i] -= C[e] * A[l][i];
	C[e] = -C[e] * A[l][e];
}

inline void simplex() {
	int e = 0;
	while (1) {
		for (e = 1; e <= n; ++e)
			if (C[e]>eps) break;
		if (e == n + 1) break;

		double data = inf, t; int l;
		for (int i = 1; i <= m; ++i)
			if (A[i][e]>eps && (t = B[i] / A[i][e])<data) {
				data = t;
				l = i;
			}
		pivot(l, e);
	}
}

int main() {
	scanf_s("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i)
		scanf_s("%lf", &C[i]);
	for (int i = 1; i <= m; ++i) {
		scanf_s("%d%d%lf", &L, &R, &B[i]);
		for (int j = L; j <= R; ++j)
			A[i][j] = 1;
	}
	simplex();
	printf("%0.2f\n", ans);
}

