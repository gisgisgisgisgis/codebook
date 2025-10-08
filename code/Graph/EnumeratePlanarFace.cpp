// 0-based
struct PlanarGraph{
    int n, m, id;
    vector<Pt> v;
    vector<vector<pair<int, int>>> adj;
    vector<int> conv, nxt, vis;

    PlanarGraph(int n, int m, vector<Pt> _v) : 
    n(n), m(m), id(0),
    v(_v), adj(n),
    conv(m << 1), nxt(m << 1), vis(m << 1) {}

    void add_edge(int x, int y) {
        adj[x].push_back({y, id << 1});
        adj[y].push_back({x, id << 1 | 1});
        conv[id << 1] = x;
        conv[id << 1 | 1] = y;
        id++;
    }

    vector<int> enumerate_face() {
        for (int i = 0; i < n; i++) {
            sort(all(adj[i]), [&](const auto &a, const auto & b) {
                return argcmp((v[a.first] - v[i]), (v[b.first] - v[i]));
            });
            int sz = adj[i].size(), pre = sz - 1;
            for (int j = 0; j < sz; j++) {
                nxt[adj[i][pre].second] = adj[i][j].second ^ 1;
                pre = j;
            }
        }

        vector<int> ret;
        for (int i = 0; i < m * 2; i++) {
            if (!vis[i]) {
                int area = 0, now = i;
                vector<int> pt;
                while (!vis[now]) {
                    vis[now] = true;
                    pt.push_back(conv[now]);
                    now = nxt[now];
                }
                pt.push_back(pt.front());
                for (int i = 0; i + 1 < ssize(pt); i++) {
                    area -= (v[pt[i]] ^ v[pt[i + 1]]);
                }
                // pt = face boundary
                if (area > 0) {
                    ret.push_back(area);
                } else {
                    // pt is outer face
                }
            }
        }
        return ret;
    }
};
