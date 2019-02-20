#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[]) {
  std::ios_base::sync_with_stdio(false);
  int n, m, K;
  cin >> n >> m >> K;
  vector<vector<int>> a(n, vector<int>(m, 0));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> a[i][j];
    }
  }
  vector<vector<vector<int>>> f(n + 1, vector<vector<int>>(m + 1));
  f[0][1].push_back(0);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      std::merge(f[i - 1][j].begin(), f[i - 1][j].end(), f[i][j - 1].begin(),
                 f[i][j - 1].end(), std::back_inserter(f[i][j]),
                 greater<int>());
      f[i][j].erase(f[i][j].begin() + min(K, (int)f[i][j].size()),
                    f[i][j].end());
      for (auto& x : f[i][j]) {
        x += a[i - 1][j - 1];
      }
    }
  }
  assert(f[n][m].size() == K);
  for (int i = 0; i < f[n][m].size(); i++) {
    if (i) cout << " ";
    cout << f[n][m][i];
  }
  return 0;
}
