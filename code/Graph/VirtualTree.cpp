// need LCA
vector<vector<int>> vir(n);
auto clear = [&](auto self, int u) -> void {
    for (int v : vir[u]) self(self, v);
    vir[u].clear();
};
auto build = [&](vector<int> &v) -> void { // be careful of the changes to the array
    // maybe dont need to sort when do it while dfs
    sort(all(v), [&](int a, int b) {
        return dfn[a] < dfn[b];
    });
    clear(clear, 0);
    if (v[0] != 0) v.insert(v.begin(), 0);
    int k = v.size();
    vector<int> st;
    rep (i, 0, k) {
        if (st.empty()) {
            st.push_back(v[i]);
            continue;
        }
        int p = lca(v[i], st.back());
        if (p == st.back()) {
            st.push_back(v[i]);
            continue;
        }
        while (st.size() >= 2 && dep[st.end()[-2]] >= dep[p]) {
            vir[st.end()[-2]].push_back(st.back());
            st.pop_back();
        }
        if (st.back() != p) {
            vir[p].push_back(st.back());
            st.pop_back();
            st.push_back(p);
        }
        st.push_back(v[i]);
    }
    while (st.size() >= 2) {
        vir[st.end()[-2]].push_back(st.back());
        st.pop_back();
    }
};