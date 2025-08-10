// comb(n, m) % M, M = p^k
// O(M)-O(log(n))
struct Lucas {
    const int p, M;
    vector<int> f;
    Lucas(int p, int M) : p(p), M(M), f(M + 1) {
        f[0] = 1;
        for (int i = 1; i <= M; i++) {
            f[i] = f[i - 1] * (i % p == 0 ? 1 : i) % M;
        }
    }
    int CountFact(int n) {
        int c = 0;
        while (n) c += (n /= p);
        return c;
    }
    // (n! without factor p) % p^k
    int ModFact(int n) {
        int r = 1;
        while (n) {
            r = r * power(f[M], n / M % 2, M) % M * f[n % M] % M;
            n /= p;
        }
        return r;
    }
    int ModComb(int n, int m) {
        if (m < 0 or n < m) return 0;
        int c = CountFact(n) - CountFact(m) - CountFact(n - m);
        int r = ModFact(n) * power(ModFact(m), M / p * (p - 1) - 1, M) % M
                           * power(ModFact(n - m), M / p * (p - 1) - 1, M) % M;
        return r * power(p, c, M) % M;
    }
};