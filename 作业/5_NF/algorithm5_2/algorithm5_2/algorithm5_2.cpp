// algorithm5_2.cpp : 定义控制台应用程序的入口点。
/*有个定理，大概意思是一个有向图的最小割等于该图的最大流量(说个大概，不严谨)

把每个骑士拆成入点和出点，能互相攻击的连边，求得最大流(最小割)

根据定理，断掉一些边(即在两个互相攻击的骑士只选一个)使骑士们分在两个集合里的最小代价即为最大流量

所以将总骑士数 - 最大流量即为答案
*/

#include "stdafx.h"
#include<queue>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n, m, cnt, tot;
int st, ed;
int dx[8] = { 1,1,-1,-1,2,2,-2,-2 };
int dy[8] = { 2,-2,2,-2,1,-1,1,-1 };
int head[80005];
int cur[80005];
int dis[80005];
bool ban[205][205];
struct node {
	int fr;
	int to;
	int nxt;
	int flw;
}edge[1000005];
void init() {
	memset(head, -1, sizeof(head));
}
void addedge(int u, int v, int f) {
	edge[cnt].fr = u;
	edge[cnt].to = v;
	edge[cnt].flw = f;
	edge[cnt].nxt = head[u];
	head[u] = cnt++;
	edge[cnt].fr = v;
	edge[cnt].to = u;
	edge[cnt].flw = 0;
	edge[cnt].nxt = head[v];
	head[v] = cnt++;
}
bool bfs() {
	queue<int>que;
	memset(dis, 0x3f, sizeof(dis));
	que.push(st); dis[st] = 0;
	while (!que.empty()) {
		int u = que.front();
		que.pop();
		for (int i = head[u]; i != -1; i = edge[i].nxt) {
			if (!edge[i].flw)continue;
			int v = edge[i].to;
			if (dis[v] == 0x3f3f3f3f) {
				dis[v] = dis[u] + 1;
				que.push(v);
			}
		}
	}
	return (dis[ed] != 0x3f3f3f3f);
}
int dfs(int u, int flw) {
	int All = 0; int tmp;
	if (u == ed)return flw;
	for (int i = head[u]; i != -1; i = edge[i].nxt) {
		if (!edge[i].flw)continue;
		int v = edge[i].to; head[u] = i;
		if (dis[v] != dis[u] + 1)continue;
		if ((tmp = dfs(v, min(flw, edge[i].flw)))>0) {
			flw -= tmp;
			edge[i].flw -= tmp;
			edge[i ^ 1].flw += tmp;
			All += tmp;
			if (!flw)break;
		}
	}
	return All;
}
int dicnic() {
	scanf_s("%d%d", &n, &m);
	int ret = 0; ed = n*n + 1;
	for (int i = 1; i <= m; i++) {
		int x, y;
		scanf_s("%d%d", &x, &y);
		ban[x][y] = true;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (ban[i][j])continue;
			for (int k = 0; k<8; k++) {
				int xx = i + dx[k];
				int yy = j + dy[k];
				if (xx<1 || xx>n || yy<1 || yy>n)continue;
				if (ban[xx][yy])continue;
				if ((i + j) & 1)addedge((i - 1)*n + j, (xx - 1)*n + yy, 1);
				else addedge((xx - 1)*n + yy, (i - 1)*n + j, 1);
			}
			if ((i + j) & 1)addedge(st, (i - 1)*n + j, 1);
			else addedge((i - 1)*n + j, ed, 1);
		}
	}memcpy(cur, head, sizeof(cur));
	while (bfs()) {
		ret += dfs(st, 0x3f3f3f3f);
		memcpy(head, cur, sizeof(head));
	}
	return n*n - m - ret;
}
int main() {
	init();
	printf("%d\n", dicnic());
	return 0;
}
