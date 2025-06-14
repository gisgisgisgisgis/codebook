template <typename T>
struct Dinic {
    
    const T INF = numeric_limits<T>::max() / 2;

    struct edge {
        int v, r; T rc;
    };

    vector<vector<edge>> adj;
    vector<int> dis, it;
    Dinic(int n) : adj(n), dis(n), it(n) {}

    void add_edge(int u, int v, T c) {
        adj[u].pb({v, adj[v].size(), c});
        adj[v].pb({u, adj[u].size() - 1, 0});
    }

    bool bfs(int s, int t) {
        fill(all(dis), IINF);
        queue<int> q;
        q.push(s);
        dis[s] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (const auto& [v, r, rc] : adj[u]) {
                if (dis[v] < IINF || rc == 0) continue;
                dis[v] = dis[u] + 1;
                q.push(v);
            }
        }
        return dis[t] < IINF;
    }

    T dfs(int u, int t, T cap) {
        if (u == t || cap == 0) return cap;
        for (int &i = it[u]; i < (int)adj[u].size(); ++i) {
            auto &[v, r, rc] = adj[u][i];
            if (dis[v] != dis[u] + 1) continue;
            T tmp = dfs(v, t, min(cap, rc));
            if (tmp > 0) {
                rc -= tmp;
                adj[v][r].rc += tmp;
                return tmp;
            }
        }
        return 0;
    }

    T flow(int s, int t) {
        T ans = 0, tmp;
        while (bfs(s, t)) {
            fill(all(it), 0);
            while ((tmp = dfs(s, t, INF)) > 0) {
                ans += tmp;
            }
        }
        return ans;
    }

    bool inScut(int u) { return dis[u] < IINF; }
};