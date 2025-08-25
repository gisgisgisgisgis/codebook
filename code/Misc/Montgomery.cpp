struct Montgomery {
    u32 mod, modr;
    Montgomery(u32 m) : mod(m), modr(1) {
        for (int i = 0; i < 5; ++i) modr *= 2 - mod * modr;
    }
    u32 reduce(u64 x) const {
        u32 q = u32(x) * modr;
        u32 m = (u64(q) * mod) >> 32;
        u32 v = (x >> 32) + mod - m;
        return (v >= mod ? v - mod : v);
    }
    u32 mul(u32 x, u32 y) const { return reduce(u64(x) * y); }
    u32 add(u32 x, u32 y) const { return (x + y >= mod ? x + y - mod : x + y); }
    u32 sub(u32 x, u32 y) const { return (x < y ? x + mod - y : x - y); }
    u32 transform(u32 x) const { return (u64(x) << 32) % mod; }
};
int p;
Montgomery space(p);
u32 a[n][n], b[n][n], c[n][n]; // 裡 面 元 素 皆 已 v = space.transform(v); 過
for (int i = 0; i < n; ++i) {
    for (int k = 0; k < n; ++k) {
        for (int j = 0; j < n; ++j) {
            c[i][j] = space.add(c[i][j], space.mul(a[i][k], b[k][j]));
        }
    }
}
cout << space.reduce(c[0][0]) << "\n"; // 輸 出 (a * b)[0][0] mod 