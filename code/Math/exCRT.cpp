i64 exgcd(i64 a, i64 b, i64 &x, i64 &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    i64 g = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}

// return {x, T}
// a: moduli, b: remainders
// x: first non-negative solution, T: minimum period
std::pair<i64, i64> exCRT(auto &a, auto &b) {
    auto [m1, r1] = std::tie(a[0], b[0]);
    for (int i = 1; i < std::ssize(a); i++) {
        auto [m2, r2] = std::tie(a[i], b[i]);
        i64 x, y;
        i64 g = exgcd(m1, m2, x, y);
        if ((r2 - r1) % g) { // no solution
            return {-1, -1};
        }
        x = (i128(x) * (r2 - r1) / g) % (m2 / g);
        if (x < 0) {
            x += (m2 / g);
        }
        r1 = m1 * x + r1;
        m1 = std::lcm(m1, m2);
    }
    r1 %= m1;
    if (r1 < 0) {
        r1 += m1;
    }
    return {r1, m1};
};