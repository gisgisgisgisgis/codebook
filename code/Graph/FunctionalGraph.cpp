struct FunctionalGraph {
    int n, cnt = 0;
    std::vector<std::vector<int>> adj;
    std::vector<int> f, bel, dep, ord, root, in, out, len;
    FunctionalGraph(int n) : n(n), adj(n), root(n),
    bel(n, -1), dep(n), ord(n), in(n), out(n) {};
    void dfs(int u) {
        in[u] = cnt++;
        for (int v : adj[u]) {
            if (bel[v] == -1) {
                dep[v] = dep[u] + 1;
                root[v] = root[u];
                bel[v] = bel[u];
                dfs(v);
            }
        } 
        out[u] = cnt;
    }
    void build(const auto &f_) {
        f = f_;
        for (int i = 0; i < n; i++) {
            adj[f[i]].push_back(i);
        }
        std::vector<int> vis(n, -1);
        for (int i = 0; i < n; i++) {
            if (vis[i] == -1) {
                int x = i;
                while (vis[x] == -1) {
                    vis[x] = i;
                    x = f[x];
                }
                if (vis[x] != i) {
                    continue;
                }
                int s = x, l = 0;
                do {
                    bel[x] = len.size();
                    ord[x] = l++;
                    root[x] = x;
                    x = f[x];
                } while (x != s);
                len.push_back(l);
            }
        } 
        for (int i = 0; i < n; i++) {
            if (root[i] == i) {
                dfs(i);
            }
        }
    }
    int dist(int x, int y) { // x -> y
        if (bel[x] != bel[y]) {
            return -1;
        } else if (dep[x] < dep[y]) {
            return -1;
        } else if (dep[y] != 0) {
            if (in[y] <= in[x] and in[x] < out[y]) {
                return dep[x] - dep[y];
            }
            return -1;
        } else {
            return dep[x] + (ord[y] - ord[root[x]] + len[bel[x]]) % len[bel[x]];
        }
    }
};
