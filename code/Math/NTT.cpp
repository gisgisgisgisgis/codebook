// add sub mul
struct ntt {
    vector<int> ws;
    ntt(int N) : ws(N) {
        int wb = fpow(3, (MOD - 1) / N, MOD);
        ws[0] = 1;
        rep (i, 1, N) ws[i] = mul(ws[i - 1], wb);
    }
    void operator()(vector<int> &P, bool inv = 0) {
        int n = P.size(), lg = __builtin_ctz(n);
        assert(__builtin_popcount(n) == 1);
        for (int j = 1, i = 0; j < n - 1; ++j) {
            for (int k = n >> 1; k > (i ^= k); k >>= 1); // !!!
            if (j < i) swap(P[i], P[j]);
        }
        for (int L = 2; L <= n; L <<= 1) {
            int dx = n / L, dl = L >> 1;
            for (int k = 0; k < n; k += L) {
                for (int j = k, x = 0; j < k + dl; j++, x += dx) {
                    int t = mul(ws[x], P[j + dl]);
                    P[j + dl] = sub(P[j], t);
                    P[j] = add(P[j], t);
                }
            }
        }
        if (inv) {
            reverse(1 + all(P));
            int invn = fpow(n, MOD - 2, MOD);
            rep (i, 0, n) P[i] = mul(P[i], invn);
        }
    }
};
const int N = 1 << 20;
ntt NTT(N);