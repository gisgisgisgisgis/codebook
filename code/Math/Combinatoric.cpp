vector<mint> fac, inv;

inline void init (int n) {
    fac.resize(n + 1);
    inv.resize(n + 1);
    fac[0] = inv[0] = 1;
    rep (i, 1, n + 1) fac[i] = fac[i - 1] * i;
    inv[n] = fac[n].inv();
    for (int i = n; i > 0; --i) inv[i - 1] = inv[i] * i;
}

inline mint Comb(int n, int k) {
    if (k > n || k < 0) return 0;
    return fac[n] * inv[k] * inv[n - k];
}

inline mint H(int n, int m) {
    return Comb(n + m - 1, m);
}

inline mint catalan(int n){
    return fac[2 * n] * inv[n + 1] * inv[n];
}