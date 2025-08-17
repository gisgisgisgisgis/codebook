struct ACM {
    int idx = 0;
    vector<array<int, 26>> tr;
    vector<int> cnt, fail;
    
    void clear() {
        tr.resize(1, array<int, 26>{});
        cnt.resize(1, 0);
        fail.resize(1, 0);
    }
 
    ACM() {
        clear();
    }
 
    int newnode() {
        tr.push_back(array<int, 26>{});
        cnt.push_back(0);
        fail.push_back(0);
        return ++idx;
    }
 
    void insert(string &s) {
        int u = 0;
        for (char c : s) {
            c -= 'a';
            if (tr[u][c] == 0) tr[u][c] = newnode();
            u = tr[u][c];
        }
        cnt[u]++;
    }
 
    void build() {
        queue<int> q;
        rep (i, 0, 26) if (tr[0][i]) q.push(tr[0][i]);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            rep (i, 0, 26) {
                if (tr[u][i]) {
                    fail[tr[u][i]] = tr[fail[u]][i];
                    cnt[tr[u][i]] += cnt[fail[tr[u][i]]];
                    q.push(tr[u][i]);
                } else {
                    tr[u][i] = tr[fail[u]][i];
                }
            }
        }
    }

    int query(string &s) {
        int u = 0, res = 0;
        for (char c : s) {
            c -= 'a';
            u = tr[u][c];
            res += cnt[u];
        }
        return res;
    }
};