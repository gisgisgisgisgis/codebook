vector<int> BuildDomTree(vector<vector<int>> adj, int rt) {
    int n = adj.size();

    // buckets: list of vertices y with sdom(y) = x
    vector<vector<int>> buckets(n), radj(n);

    // rev[dfn[x]] = x
    vector<int> dfn(n, -1), rev(n, -1), pa(n, -1);
    vector<int> sdom(n, -1), dom(n, -1);
    vector<int> fa(n, -1), val(n, -1);

    int stamp = 0;

    // re-number in DFS order
    auto dfs = [&](auto self, int u) -> void {
        rev[dfn[u] = stamp] = u;
        fa[stamp] = sdom[stamp] = val[stamp] = stamp;
        stamp++;
        for (int v : adj[u]) {
            if (dfn[v] == -1) {
                self(self, v);
                pa[dfn[v]] = dfn[u];
            }
            radj[dfn[v]].pb(dfn[u]);
        }
    };

    function<int(int, bool)> Eval = [&](int x, bool fir) {
        if (x == fa[x]) return fir ? x : -1;
        int p = Eval(fa[x], false);
        // x is one step away from the root
        if (p == -1) return x;
        if (sdom[val[x]] > sdom[val[fa[x]]]) val[x] = val[fa[x]];
        fa[x] = p;
        return fir ? val[x] : p;
    };

    auto Link = [&](int x, int y) -> void { fa[x] = y; };

    dfs(dfs, rt);

    // compute sdom in reversed DFS order
    for (int x = stamp - 1; x >= 0; --x) {
        for (int y : radj[x]) {
            // sdom[x] = min({y | (y, x) in E(G), y < x}, {sdom[z] | (y, x) in E(G), z > x && z is y's ancestor})
            chmin(sdom[x], sdom[Eval(y, true)]);
        }
        if (x > 0) buckets[sdom[x]].pb(x);
        for (int u : buckets[x]) {
            int p = Eval(u, true);
            if (sdom[p] == x) dom[u] = x;
            else dom[u] = p;
        }
        if (x > 0) Link(x, pa[x]);
    }
    // idom[x] = -1 if x is unreachable from rt
    vector<int> idom(n, -1);
    idom[rt] = rt;
    rep (x, 1, stamp) {
        if (sdom[x] != dom[x]) dom[x] = dom[dom[x]];
    }
    rep (i, 1, stamp) idom[rev[i]] = rev[dom[i]];
    return idom;
}