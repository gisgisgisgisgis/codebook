template <class T>
constexpr T power(T a, u64 b, T res = 1) {
    for (; b != 0; b /= 2, a *= a) {
        if (b & 1) {
            res *= a;
        }
    }
    return res;
}

template <u32 P = 998244353>
struct ModInt {
    u32 v;
    ModInt(i64 x = 0) { norm((x % P + P) % P); }
    ModInt &norm(u32 x) {
        v = x < P ? x : x - P;
        return *this;
    }
    ModInt inv() const { return power(*this, P - 2); }
    ModInt operator+(const ModInt &r) const { return ModInt().norm(v + r.v); }
    ModInt operator-(const ModInt &r) const { return ModInt().norm(v + P - r.v); }
    ModInt operator*(const ModInt &r) const { return ModInt().norm(u64(v) * r.v % P); }
    ModInt operator/(const ModInt &r) const { return *this * r.inv(); }
    ModInt &operator+=(const ModInt &r) { return *this = *this + r; }
    ModInt &operator-=(const ModInt &r) { return *this = *this - r; }
    ModInt &operator*=(const ModInt &r) { return *this = *this * r; }
    ModInt &operator/=(const ModInt &r) { return *this = *this / r; }
    bool operator==(const ModInt &r) const { return v == r.v; }
    explicit operator bool() const { return v != 0; }
    friend ostream &operator<<(ostream &os, const ModInt &x) {
        return os << x.v;
    }
};

using Z = ModInt<998244353>;
// using F = long double;

using Matrix = std::vector<std::vector<Z>>;
// using Matrix = std::vector<std::vector<F>>; (double)
// using Matrix = std::vector<std::bitset<5000>>; (mod 2)

template <typename T>
auto gauss(Matrix &A, std::vector<T> &b, int n, int m) {
    assert(std::ssize(b) == n);
    int r = 0;
    std::vector<int> where(m, -1);

    for (int i = 0; i < m && r < n; i++) {
        int p = r;  // pivot
        while (p < n && A[p][i] == T(0)) {
            p++;
        }
        if (p == n) {
            continue;
        }

        std::swap(A[r], A[p]);
        std::swap(b[r], b[p]);
        where[i] = r;

        // coef: mod 2 don't need this
        T inv = T(1) / A[r][i];
        for (int j = i; j < m; j++) {
            A[r][j] *= inv;
        }
        b[r] *= inv;

        for (int j = 0; j < n; j++) {  // deduct: mod 2 don't need this
            if (j != r) {
                T x = A[j][i];
                for (int k = i; k < m; k++) {
                    A[j][k] -= x * A[r][k];
                }
                b[j] -= x * b[r];
            }
        }

        // for (int j = 0; j < n; ++j) { // (mod 2) -> coef and deduct
        //     if (j != r && A[j][i]) {
        //         A[j] ^= A[r];
        //         b[j] ^= b[r];
        //     }
        // }

        r++;
    }

    for (int i = r; i < n; i++) {
        if (ranges::all_of(A[i] | views::take(m), [](auto x) { return x == 0; }) && b[i] != T(0)) {
            return std::vector<T>();  // no solution
        }
        // if (A[i].none() && b[i]) { // (mod 2)
        //     return std::vector<T>();
        // }
    }

    // if (r < m) { // infinite solution
    //     return std::vector<T>();
    // }

    std::vector<T> res(m);
    for (int i = 0; i < m; i++) {
        if (where[i] != -1) {
            res[i] = b[where[i]];
        }
    }
    return res;
};