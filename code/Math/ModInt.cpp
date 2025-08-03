using u32 = unsigned int;
using u64 = unsigned long long;
template <class T>
constexpr T power(T a, u64 b, T res = 1) {
    for (; b != 0; b /= 2, a *= a) {
        if (b & 1) {
            res *= a;
        }
    }
    return res;
}

template <u32 P>
struct ModInt {
    u32 v;
    const static ModInt G;

    constexpr ModInt &norm(u32 x) {
        v = x < P ? x : x - P;
        return *this;
    }
    constexpr ModInt(i64 x = 0) { norm(x % P + P); }
    constexpr ModInt inv() const { return power(*this, P - 2); }
    constexpr ModInt operator-() const { return ModInt() - *this; }
    constexpr ModInt operator+(const ModInt &r) const { return ModInt().norm(v + r.v); }
    constexpr ModInt operator-(const ModInt &r) const { return ModInt().norm(v + P - r.v); }
    constexpr ModInt operator*(const ModInt &r) const { return ModInt().norm(u64(v) * r.v % P); }
    constexpr ModInt operator/(const ModInt &r) const { return *this * r.inv(); }
    constexpr ModInt &operator+=(const ModInt &r) { return *this = *this + r; }
    constexpr ModInt &operator-=(const ModInt &r) { return *this = *this - r; }
    constexpr ModInt &operator*=(const ModInt &r) { return *this = *this * r; }
    constexpr ModInt &operator/=(const ModInt &r) { return *this = *this / r; }
    constexpr bool operator==(const ModInt &r) const { return v == r.v; }
    constexpr bool operator!=(const ModInt &r) const { return v != r.v; }
    explicit constexpr operator bool() const { return v != 0; }
    friend std::ostream &operator<<(std::ostream &os, const ModInt &r) {
        return os << r.v;
    }
};
using mint = ModInt<998244353>;
template <> const mint mint::G = mint(3);
