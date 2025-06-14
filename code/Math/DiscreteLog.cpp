int power(int a, int b, int p, int res = 1) {
    for (; b; b /= 2, a = 1LL * a * a % p) {
        if (b & 1) {
            res = 1LL * res * a % p;
        }
    }
    return res;
}

int exbsgs(int a, int b, int p) {
    a %= p;
    b %= p;
    if (b == 1 || p == 1) {
        return 0;
    }
    if (a == 0) {
        return b == 0 ? 1 : -1;
    }

    i64 g, k = 0, t = 1;  // t : a ^ k / sum{d}
    while ((g = std::gcd(a, p)) > 1) {
        if (b % g) {
            return -1;
        }
        b /= g;
        p /= g;
        k++;
        t = t * (a / g) % p;
        if (t == b) {
            return k;
        }
    }

    const int n = std::sqrt(p) + 1;
    std::unordered_map<int, int> mp;
    mp[b] = 0;

    int x = b, y = t;
    int mi = power(a, n, p);
    for (int i = 1; i < n; i++) {
        x = 1LL * x * a % p;
        mp[x] = i;
    }

    for (int i = 1; i <= n; i++) {
        t = 1LL * t * mi % p;
        if (mp.contains(t)) {
            return 1LL * i * n - mp[t] + k;
        }
    }

    return -1; // no solution
}