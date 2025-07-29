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
    ModInt(i64 x = 0) { norm(x % P + P); }
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
    friend std::ostream &operator<<(std::ostream &os, const ModInt &r) {
        return os << r.v;
    }
};
