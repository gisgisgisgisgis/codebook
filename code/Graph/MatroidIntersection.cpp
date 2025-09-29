/*
M1 = xx matroid, M2 = xx matroid
y<-s if I+y   satisfies M1
y->t if I+y   satisfies M2
x<-y if I-x+y satisfies M2
x->y if I-x+y satisfies M1
交換圖點權：
-w[e] if e \in I
w[e] otherwise
*/
vector<int> I(, 0);
while (true) {
    vector<vector<int>> adj();
    int s = , t = s + 1;
    auto M1 = [&]() -> void { // xx matroid
        {   // y<-s

        }
        {   // x->y

        }
    };
    auto M2 = [&]() -> void { // xx matroid
        {   // y->t

        }
        {   // x<-y

        }
    };
    auto augment = [&]() -> bool { // 註解掉的是帶權版
        vector<int> vis( + 2, 0), dis( + 2, IINF), from( + 2, -1);
        queue<int> q;
        vis[s] = 1;
        dis[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            // vis[u] = 0;
            for (int v : adj[u]) {
                int w = ; // no weight -> 1, v == t -> 0
                if (chmin(dis[v], dis[u] + w)) {
                    from[v] = u;
                    // if (!vis[v]) {
                        // vis[v] = 1;
                        q.push(v);
                    // }
                }
            }
        }
        if (from[t] == -1) return false;
        for (int cur = from[t];; cur = from[cur]) {
            if (cur == -1 || cur == s) break;
            I[cur] ^= 1;
        }
        return true;
    };
    M1(), M2();
    if (!augment()) break;
}