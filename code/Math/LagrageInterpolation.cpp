struct Lagrange {
    int deg{};
    vector<int> C;
    Lagrange(const vector<int> &P) {
        deg = P.size() - 1;
        C.assign(deg + 1, 0);
        for (int i = 0; i <= deg; i++) {
            int q = inv[i] * inv[i - deg] % mod;
            if ((deg - i) % 2 == 1) {
                q = mod - q;
            }
            C[i] = P[i] * q % mod;
        }
    }
    int operator()(int x) { // 0 <= x < mod
        if (0 <= x and x <= deg) {
            int ans = fac[x] * fac[deg - x] % mod;
            if ((deg - x) % 2 == 1) {
                ans = (mod - ans);
            }
            return ans * C[x] % mod;
        }
        vector<int> pre(deg + 1), suf(deg + 1);
        for (int i = 0; i <= deg; i++) {
            pre[i] = (x - i);
            if (i) {
                pre[i] = pre[i] * pre[i - 1] % mod;
            }
        }
        for (int i = deg; i >= 0; i--) {
            suf[i] = (x - i);
            if (i < deg) {
                suf[i] = suf[i] * suf[i + 1] % mod;
            }
        }
        int ans = 0;
        for (int i = 0; i <= deg; i++) {
            ans += (i == 0 ? 1 : pre[i - 1]) * (i == deg ? 1 : suf[i + 1]) % mod * C[i];
            ans %= mod;
        }
        if (ans < 0) ans += mod;
        return ans;
    }
};