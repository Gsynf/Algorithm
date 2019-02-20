#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

const long INF = 0x3f3f3f3f;
const long maxn = 1220001;

// 结点数，边数，源点，汇点，边的起点，终点
int n, m, s, t, source, end;
// 边的容量
long c;

// 边的结构体
struct Edge{
    int source, end;
    long capacity, flow;
    Edge(int u, int v, long c, long f):source(u), end(v), capacity(c), flow(f) {}
};

struct Dinic{
    vector<Edge> edges;
    vector<int> G[maxn];
    // 结点所在层
    int d[maxn];
    // 结点是否访问
    bool vis[maxn];
    long cur[maxn];
    
    // 初始化
    void init(int n) {
        for (int i = 0; i < n; i++) G[i].clear();
        edges.clear();
    }

    // 加入边
    void addEdge(int source, int end, long capacity) {
        edges.push_back(Edge(source, end, capacity, 0));
        edges.push_back(Edge(end, source, 0, 0));
        int size = edges.size();
        G[source].push_back(size - 2);
        G[end].push_back(size - 1);
    }

    // 扩展的BFS构建分层网络
    bool BFS() {
        memset(vis, false, sizeof(vis));
        queue<int> Q;
        Q.push(s);
        d[s] = 0;
        vis[s] = true;
        int i, pre;
        while (!Q.empty()) {
            pre = Q.front();
            Q.pop();
            for (i = 0; i < G[pre].size(); i++) {
                Edge& e = edges[G[pre][i]];
                if (!vis[e.end] && e.capacity>e.flow) {
                    vis[e.end] = true;
                    d[e.end] = d[pre]+1;
                    Q.push(e.end);
                }
            }
        }
        return vis[t];
    }

    // DFS寻找s->t的路径，并跑流
    long DFS(int x, long a) {
        if (x == t || a == 0) return a;
        long flow = 0, f;
        for (long& i = cur[x]; i<G[x].size(); i++) {
            Edge& e = edges[G[x][i]];
            if (d[x] + 1 == d [e.end] && (f = DFS(e.end, min(a, e.capacity - e.flow)))>0) {
                e.flow += f;
                edges[G[x][i]^1].flow -= f;
                flow += f;
                a -= f;
                if (a == 0) break;
            }
        }
        return flow;
    }

    // 求解最大流
    long Maxflow() {
        long flow = 0;
        // 扩展BFS算法构建分层网络
        while (BFS()) {
            memset(cur, 0, sizeof(cur));
            // DFS寻找s->t的路径
            flow += DFS(s, INF);
        }
        return flow;
    }
}DN;

int main(void) {
    scanf("%d %d %d %d",&n, &m, &s, &t);
    DN.init(maxn);
    // 输入
    int i;
    for(i=0; i < m; i++) {
        scanf("%d %d %ld", &source, &end ,&c);
        DN.addEdge(source, end, c);
    }
    printf("%ld\n", DN.Maxflow());
    return 0;
}