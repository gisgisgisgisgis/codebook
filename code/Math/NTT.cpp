template<typename M = ll>
void NTT(vector<M> &P, M w, bool inv = 0) {
    int n = P.size(), lg = __builtin_ctz(n);
    assert(__builtin_popcount(n) == 1);
    for (int j = 1, i = 0; j < n - 1; ++j) {
        for (int k = n >> 1; k > (i ^= k); k >>= 1); // !!!
        if (j < i) swap(P[i], P[j]);
    }
    vector<M> ws = {inv ? M{1} * fpow(w, MOD - 2, MOD) : w};
    rep (i, 1, lg) ws.pb(ws[i - 1] * ws[i - 1] % MOD);
    reverse(all(ws));
    rep (i, 0, lg) {
        for (int k = 0; k < n; k += 2 << i) {
            M base = M{1};
            rep (j, k, k + (1 << i)) {
                auto t = base * P[j + (1 << i)] % MOD;
                auto u = P[j];
                P[j] = (u + t) % MOD;
                P[j + (1 << i)] = (u - t + MOD) % MOD;
                base = base * ws[i] % MOD;
            }
        }
    }
    if (inv) rep (i, 0, n) P[i] = P[i] * fpow(n, MOD - 2, MOD) % MOD;
}
const int N = 1 << 20;
const auto w = fpow(3, (MOD - 1) / N, MOD);