// DualSimplex_2.cpp : �������̨Ӧ�ó������ڵ㡣
//
/*
��ż�������㷨
�����ʽ��
A�������α���󣬸�������ϵ���ͳ��� M * N + 1 ά
a_11 a_12 ������ a_1N b_1
a_21 a_22 ������ a_2N b_2
��     ��        ��   ��
��     ��        ��   ��
��     ��        ��   ��
a_M1 a_M2 ������ a_MN b_M

C��Ŀ�꺯��ϵ������ N ά
Lambda������������ N ά
base_V���������±� M ά
B����������Ŀ�꺯���ж�Ӧ��ϵ�� M ά
goal��Ŀ��ֵ
*/

#include "stdafx.h"

#include <stdio.h>
#include <iostream>

#define N 6  
#define M 3 //N��������M��Լ������

using namespace std;

double A[M][N + 1] = { 
{ 3, -1, 1, -2, 0, 0, -3 },
{ 2,  1, 0,  1, 1, 0,  4 },
{ -1, 3, 0, -3, 0, 1, 12 }
};
double C[N] = { -7, 7, -2, -1, -6, 0 };//Ŀ�꺯��ϵ��
//double Goal[N] = { 0, 0, 0, 0, 0, 0};//������
double Lambda[N] = { 0, 0, 0, 0, 0, 0 };//������
int base_V[M] = { 2, 4, 5 };//����������ʼ������Ϊ ����A �ĵ�2��4��5��
double B[M] = { 0, 0, 0 };
double goal;//Ŀ��ֵ

bool is_base(int v)
{
	for (int i = 0; i < M; i++)
		if (base_V[i] == v)
			return true;
	return false;
}

double dual()
{
	// ��������A����ʽ�����ڷ���
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N + 1; j++)
			cout << " " << A[i][j];
		cout << endl;
	}

	while (1)
	{
		for (int i = 0; i < M; i++)
			B[i] = C[base_V[i]];
		//���������
		cout << "������C:" << endl;
		for (int i = 0; i < N; i++)
		{
			double lam_temp = 0;
			for (int j = 0; j < M; j++)
				lam_temp += B[j] * A[j][i];
			Lambda[i] = C[i] - lam_temp;

			if (Lambda[i] < 0)
			{
				cout << "can not be soluted by dual method" << endl;
				return NULL;
			}
			cout << Lambda[i] << ' ';
		}
		cout << endl;
		//����Ŀ��ֵ
		double goal_temp = 0;
		for (int i = 0; i < M; i++)
			goal_temp += B[i] * A[i][N];
		goal = goal_temp;
		cout << "Ŀ��ֵ" << goal << endl;

		int temp = 0;
		double min_b = 1000;
		int out_base = 0;
		int row = 0;
		cout << "������" << endl;
		for (int i = 0; i < M; i++)
		{
			cout << A[i][N] << ' ';
			if (A[i][N] < 0)//�жϳ�����
				temp = 1;
			if (A[i][N] < min_b)
			{
				min_b = A[i][N];
				out_base = base_V[i]; //ȷ�����������±�
				row = i;
			}
		}
		cout << endl;
		//ȡ������ֵ����
		if (temp == 0)
			break;
		//δ�ﵽ��������
		double min_abs = 1000;
		int in_base = 0;
		for (int i = 0; i < N; i++)
		{

			if (!is_base(i) && A[row][i] < 0)
			{
				double temp_min = abs(Lambda[i] / A[row][i]);
				if (temp_min < min_abs)
				{
					min_abs = temp_min;//ȷ���������
					in_base = i;
				}
			}
		}
		base_V[row] = in_base;
		//�����б任����������
		for (int i = 0; i < M; i++)
		{
			temp = A[row][in_base];
			for (int j = 0; j < N + 1; j++)
			{
				if (i != row)
					A[i][j] += -A[row][j] / temp;
				else
					A[i][j] /= temp;
			}
		}
		//cout << "in_base:" << in_base << "\trow:" << row << endl;
		cout << endl;
	}
	return goal;
}

int main()
{
	double g = dual();
	cout << endl;
	cout << "����ֵ" << g << endl;
	//cout << A[0][6];
	return 1;
}


