void fwt(vector<ll> &f, bool inv = false) { // xor-convolution
    const int N = 31 - __builtin_clz(ssize(f)),
              inv2 = (MOD + 1) / 2;
    rep (i, 0, N) rep (j, 0, 1 << N) {
        if (j >> i & 1 ^ 1) {
            ll a = f[j], b = f[j | (1 << i)];
            if (inv) {
                f[j] = (a + b) * inv2 % MOD;
                f[j | (1 << i)] = (a - b + MOD) * inv2 % MOD;
            } else {
                f[j] = (a + b) % MOD;
                f[j | (1 << i)] = (a - b + MOD) % MOD;
            }
        }
    }
}