struct TwoSat {
    int n;
    vector<vector<int>> G;
    vector<bool> ans;
    vector<int> id, dfn, low, stk;
    TwoSat(int n) : n(n), G(2 * n) {}
    void addClause(int u, bool f, int v, bool g) { // (u = f) or (v = g)
        G[2 * u + !f].push_back(2 * v + g);
        G[2 * v + !g].push_back(2 * u + f);
    }
    void addImply(int u, bool f, int v, bool g) { // (u = f) -> (v = g)
        G[2 * u + f].push_back(2 * v + g);
        G[2 * v + !g].push_back(2 * u + !f);
    }
    int addVar() {
        G.emplace_back();
        G.emplace_back();
        return n++;
    }
    void addAtMostOne(const vector<pair<int, bool>> &li) {
        if (ssize(li) <= 1) return;
        int pu; bool pf; tie(pu, pf) = li[0];
        for (int i = 2; i < ssize(li); i++) {
            const auto &[u, f] = li[i];
            int nxt = addVar();
            addClause(pu, !pf, u, !f);
            addClause(pu, !pf, nxt, true);
            addClause(u, !f, nxt, true);
            tie(pu, pf) = make_pair(nxt, true);
        }
        addClause(pu, !pf, li[1].first, !li[1].second);
    } // {b42333}
    int cur = 0, scc = 0;
    void dfs(int u) {
        stk.push_back(u);
        dfn[u] = low[u] = cur++;
        for (int v : G[u]) {
            if (dfn[v] == -1) {
                dfs(v);
                chmin(low[u], low[v]);
            } else if (id[v] == -1) {
                chmin(low[u], dfn[v]);
            }
        }
        if (dfn[u] == low[u]) {
            int x;
            do {
                x = stk.back();
                stk.pop_back();
                id[x] = scc;
            } while (x != u);
            scc++;
        }
    }
    bool satisfiable() {
        ans.assign(n, 0);
        id.assign(2 * n, -1);
        dfn.assign(2 * n, -1);
        low.assign(2 * n, -1);
        for (int i = 0; i < n * 2; i++)
            if (dfn[i] == -1) {
                dfs(i);
            }
        for (int i = 0; i < n; ++i) {
            if (id[2 * i] == id[2 * i + 1]) {
                return false;
            }
            ans[i] = id[2 * i] > id[2 * i + 1];
        }
        return true;
    }
}; // [9fb62b] \ addVar, addAtMostOne