using Z = ModInt<998244353>;
// using F = long double;
using Matrix = std::vector<std::vector<Z>>;
// using Matrix = std::vector<std::vector<F>>; (double)
// using Matrix = std::vector<std::bitset<5000>>; (mod 2)

template <typename T>
auto gauss(Matrix &A, std::vector<T> &b, int n, int m) {
    assert(ssize(b) == n);
    int r = 0;
    std::vector<int> where(m, -1);
    for (int i = 0; i < m && r < n; i++) {
        int p = r;  // pivot
        while (p < n && A[p][i] == T(0)) p++;
        if (p == n) continue;
        std::swap(A[r], A[p]), std::swap(b[r], b[p]);
        where[i] = r;
        // coef: mod 2 don't need this
        T inv = T(1) / A[r][i];
        for (int j = i; j < m; j++) A[r][j] *= inv;
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
        //         A[j] ^= A[r], b[j] ^= b[r];
        //     }
        // }
        r++;
    }
    for (int i = r; i < n; i++) {
        if (ranges::all_of(A[i] | views::take(m), [](auto &x) { return x == T(0); }) && b[i] != T(0)) {
            return std::tuple(-1, std::vector<T>(), std::vector<std::vector<T>>());  // no solution
        }
        // if (A[i].none() && b[i]) { // (mod 2)
        //     return std::tuple(-1, std::vector<T>(), std::vector<std::vector<T>>());
        // }
    }
    // if (r < m) { // infinite solution
    //     return ;
    // }
    std::vector<T> sol(m);
    std::vector<std::vector<T>> basis;
    for (int i = 0; i < m; i++) {
        if (where[i] != -1) {
            sol[i] = b[where[i]];
        } else {
            std::vector<T> v(m); v[i] = 1;
            for (int j = 0; j < m; j++) {
                if (where[j] != -1) {
                    v[j] = A[where[j]][i] * T(-1);
                    // v[j] = A[where[j]][i]; (mod 2)
                }
            }
            basis.push_back(std::move(v));
        }
    }
    return std::tuple(r, sol, basis);
};
