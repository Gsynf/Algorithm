// 猴子的位置排序，香蕉位置排序，依次求第i个猴子和第i个香蕉之间的距离，返回最大的距离
//注意while与do while的区别

#include "pch.h"
#include <iostream>
#include <algorithm> 

using namespace std;

void time(int *m, int *b, int n, int maxtime)
{
	sort(m, m + n);
	sort(b, b + n);
	for (int i = 0; i < n; i++)
	{
		maxtime=maxtime> abs(m[i] - b[i]) ? maxtime : abs(m[i] - b[i]);
	}
	cout << maxtime << endl;
}

int main()
{
	int n1 = 0;
	int n2 = 0;
	int n = 0;
	int m[500];   //猴位置
	int b[50000];   //香蕉位置
	do 
	{
		scanf_s("%d", &m[n1++]); // 每次猴子位置数组下标要加1
	} while ((getchar()) != '\n');// 这里用来判断是否输入了回车，如果是则结束
	do 
	{
		scanf_s("%d", &b[n2++]); // 每次香蕉位置数组下标要加1
	} while ((getchar()) != '\n');// 这里用来判断是否输入了回车，如果是则结束

	if (!n1 || !n2 || n1!=n2)
		return 0;
	int maxtime=0;
	n = n1;
	time(m, b, n,maxtime);
	return 0;
}


