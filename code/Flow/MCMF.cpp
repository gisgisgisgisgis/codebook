template<class T>
struct MCMF {
    struct edge { int v; T f, w; int rev; };
    vector<vector<edge>> adj;
    const int n;
    MCMF(int n) : n(n), adj(n) {}
    void addEdge(int u, int v, T f, T c) {
        adj[u].push_back({v, f, c, ssize(adj[v])});
        adj[v].push_back({u, 0, -c, ssize(adj[u]) - 1});
    }
    vector<T> dis;
    vector<bool> vis;
    bool spfa(int s, int t) {
        queue<int> que;
        dis.assign(n, inf<T>);
        vis.assign(n, false);
        que.push(s);
        vis[s] = 1;
        dis[s] = 0;
        while (!que.empty()) {
            int u = que.front(); que.pop();
            vis[u] = 0;
            for (auto [v, f, w, _] : adj[u])
                if (f && chmin(dis[v], dis[u] + w))
                    if (!vis[v]) {
                        que.push(v);
                        vis[v] = 1;
                    }
        }
        return dis[t] != inf<T>;
    }
    T dfs(int u, T in, int t) {
        if (u == t) return in;
        vis[u] = 1;
        T out = 0;
        for (auto &[v, f, w, rev] : adj[u])
            if (f && !vis[v] && dis[v] == dis[u] + w) {
                T x = dfs(v, min(in, f), t);
                in -= x;
                out += x;
                f -= x;
                adj[v][rev].f += x;
                if (!in) break;
            }
        if (in) dis[u] = inf<T>; 
        vis[u] = 0;
        return out;
    }
    pair<T, T> flow(int s, int t) { // {flow, cost}
        T a = 0, b = 0;
        while (spfa(s, t)) {
            T x = dfs(s, inf<T>, t);
            a += x;
            b += x * dis[t];
        }
        return {a, b};
    }
};