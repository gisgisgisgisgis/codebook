template<class T>
struct MCMF {
    const T INF = numeric_limits<T>::max() / 2;
    struct edge { int v, r; T f, w; };
    vector<vector<edge>> adj;
    const int n;
    MCMF(int n) : n(n), adj(n) {}
    void addEdge(int u, int v, T f, T c) {
        adj[u].push_back({v, ssize(adj[v]), f, c});
        adj[v].push_back({u, ssize(adj[u]) - 1, 0, -c});
    }
    vector<T> dis;
    vector<bool> vis;
    bool spfa(int s, int t) {
        queue<int> que;
        dis.assign(n, INF);
        vis.assign(n, false);
        que.push(s);
        vis[s] = 1;
        dis[s] = 0;
        while (!que.empty()) {
            int u = que.front(); que.pop();
            vis[u] = 0;
            for (auto [v, _, f, w] : adj[u])
                if (f && chmin(dis[v], dis[u] + w))
                    if (!vis[v]) {
                        que.push(v);
                        vis[v] = 1;
                    }
        }
        return dis[t] != INF;
    }
    T dfs(int u, T in, int t) {
        if (u == t) return in;
        vis[u] = 1;
        T out = 0;
        for (auto &[v, rev, f, w] : adj[u])
            if (f && !vis[v] && dis[v] == dis[u] + w) {
                T x = dfs(v, min(in, f), t);
                in -= x;
                out += x;
                f -= x;
                adj[v][rev].f += x;
                if (!in) break;
            }
        if (in) dis[u] = INF; 
        vis[u] = 0;
        return out;
    }
    pair<T, T> flow(int s, int t) { // {flow, cost}
        T a = 0, b = 0;
        while (spfa(s, t)) {
            T x = dfs(s, INF, t);
            a += x;
            b += x * dis[t];
        }
        return {a, b};
    }
};