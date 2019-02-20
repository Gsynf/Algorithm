#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[]) {
  std::ios_base::sync_with_stdio(false);
  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    vector<int> a;
    for (int i = 0, t; i < n; i++) {
      cin >> t;
      if (a.empty() || t > a.back()) a.push_back(t);
      else *lower_bound(a.begin(), a.end(), t) = t;
    }
    cout << a.size() << endl;
  }
  return 0;
}