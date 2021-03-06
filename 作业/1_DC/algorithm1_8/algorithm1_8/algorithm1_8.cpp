/*OJ系统18分到90分：main函数里sort(node, node + n, cmpx);            //按x对输入点对排序
OJ系统90分到100分：筛选离中间位置距离d以内的点时要分为左右两部分分别筛选
*/
#include "pch.h"
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;

double MAX = 1e10; //定义的最大距离，以在只有一个点的时返回无穷大
#define N  100005  //申请数组长度为N;
int a, b;   //用来记录下标，与题无关
int n;
struct Node
{
	double x, y;
};

Node node[N];     //保存原始输入的点
Node snode[N];    //保存离mid距离为d的点

bool cmpx(Node a, Node b) { return a.x < b.x; }  //x坐标升序
bool cmpy(Node a, Node b) { return a.y < b.y; }  //y坐标升序
double min(double a, double b) { return a < b ? a : b; }  //返回最小值
double dis(Node a, Node b) { return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)); }  //返回点与点之间的距离  

double ClostestPair(int left, int right)  //left、right用来表示当前处理的数组中的下标位置
{
	int mid, i, j, tail = 0;  //mid表示数组中间的位置下标
	if (left == right) return MAX;   //如果只有一个点
	if (left + 1 == right) return dis(node[left], node[right]);   //如果只有两个点，直接计算
	mid = (left + right) / 2;
	double dlefe = ClostestPair(left, mid);  //递归求出左边的最小距离
	double dright = ClostestPair(mid + 1, right);  //递归求出右边的最小距离
	double d = min(dlefe, dright);  //d表示点对之间的距离
		  //下面是求是否存在左边的点到右边某点的距离小于d的点，或者是否存在在右边的点到左边某点的距离小于d的点，若是存在，必定处于一个d*2d的矩形中
   /*
   	for (i = left; i < right && fabs(node[mid].x - node[i].x) <d; i++)
	{   //筛选离中间位置距离d以内的点
		snode[tail++] = node[i];
	}
  */
	for (i = mid; i >= left && node[mid].x - node[i].x < d; i--)
	{   //筛选左边的点，在中间位置左侧d以内的点
		snode[tail++] = node[i];
	}
	for (i = mid + 1; i < right&&node[i].x - node[mid].x < d; i++)    //同上，筛选右边的点
	{
		snode[tail++] = node[i];
	}
	sort(snode, snode + tail, cmpy);                      //对矩形内的点按照y坐标进行排序
	for (i = 0; i < tail; i++) //枚举矩形内点对之间的距离
	{
		for (j = i + 1; j < tail && snode[j].y - snode[i].y < d; j++)
		{
			if (d > dis(snode[i], snode[j]))
			{           //更新点的值
				d = min(d, dis(snode[i], snode[j]));
			}
		}
	}
	return d;    //返回最小的点对之间的距离
}
void input()
{
	for (int i = 0; i < n; i++)
	{
		scanf_s("%lf %lf", &node[i].x, &node[i].y);
	}
}
void output()
{
	printf("%.2lf\n", ClostestPair(0, n));
}
int main()
{
	scanf_s("%d", &n);
	input();
	sort(node, node + n, cmpx);            //按x对输入点对排序
	output();
	return 0;
}





