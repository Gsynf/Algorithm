// 1）将所有人的重量进行排序；
// 2）从当前最轻的重量i开始考虑，找能跟其坐一只船的最重的人j；
// 3）比那个最重的人j都重的人都单独坐一个船；


#include "pch.h"
#include <iostream>
#include <algorithm> 

using namespace std; 

void boatnum(int *w, int n, float l) 
{
	sort(w, w + n);
	int i = 0;
	int j = n - 1;
	int res = 0;
	while (i <= j) {
		if (i == j)   //找到中间的剩一个，派一艘船
		{
			res++;
			break;
		}
		if (w[i] + w[j] <= l)  //目前最轻和最重之和小于最大载重，它两一起乘船
		{
			res++;
			i++;
			j--;
		}
		else     //目前最轻和最重之和大于最大载重，找次重的继续比较
		{ 
			res++; 
			j--; 
		}
	}
	printf("%d", res);
}
int main()
{
		int n=0;
		scanf_s("%d", &n);    //人数
		int w[50005];   //每个人质量
		if (!n)
			return 0;
		int l;
		scanf_s("%d", &l);   		//一艘船最大载重
		
		for (int i = 0; i < n; i++)
		{ 
			scanf_s("%d", &w[i]);
			if (w[i] > l)
				return -1;
		}
		boatnum(w, n, l);
	return 0;
}

