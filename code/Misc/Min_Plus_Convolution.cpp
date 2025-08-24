#include<bits/stdc++.h>
using namespace std;

#define int long long
#define rep(a, b, c) for (int a = b; a < c; a++)

const int INF = 1e18;

// a is convex a[i+1]-a[i] <= a[i+2]-a[i+1]
vector<int> min_plus_convolution(vector<int> &a, vector<int> &b) {
  int n = ssize(a), m = ssize(b);
  vector<int> c(n + m - 1, INF);
  auto dc = [&](auto Y, int l, int r, int jl, int jr) {
    if (l > r) return;
    int mid = (l + r) / 2, from = -1, &best = c[mid];
    for (int j = jl; j <= jr; ++j)
      if (int i = mid - j; i >= 0 && i < n)
        if (best > a[i] + b[j]) 
          best = a[i] + b[j], from = j;
    Y(Y, l, mid - 1, jl, from), Y(Y, mid + 1, r, from, jr);
  };
  return dc(dc, 0, n - 1 + m - 1, 0, m - 1), c;
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, m; cin >> n >> m;
    vector<int> a(n), b(m);
    rep (i, 0, n) cin >> a[i];
    rep (i, 0, m) cin >> b[i];
    auto ans = min_plus_convolution(a, b);
    rep (i, 0, n + m - 1) cout << ans[i] << " \n" [i == n + m - 2];
}