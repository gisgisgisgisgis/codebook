// a : Matrix; b, c : Vector
// max cᵀx subject to (Ax <= b and x >= 0)
// return {state, opt, solVector}
//   state = 0 → optimal
//   state = 1 → unbounded
//   state = 2 → infeasible
template <typename T>
struct Simplex {
    const T eps = 1E-7;
    const T inf = std::numeric_limits<T>::infinity();
    int n, m, V, C;
    std::vector<std::vector<T>> A;
    std::vector<int> basis;

    Simplex(const std::vector<std::vector<T>>& a,
            const std::vector<T>& b,
            const std::vector<T>& c) : n(b.size()), m(c.size()), V(n + m), C(V + 1), A(n + 1, std::vector<T>(C)), basis(n) {
        for (int i = 0; i < n; i++) {
            ranges::copy(a[i], A[i].begin());
            A[i][m + i] = 1.0;
            A[i].back() = b[i];
        }
        ranges::transform(c, A[n].begin(), [](T x) {
            return -x;
        });
        ranges::iota(basis, m);
    }

    void pivot(int r, int s) {
        const T inv = 1.0 / A[r][s];
        for (auto& x : A[r]) {
            x *= inv;
        }
        for (int i = 0; i <= n; i++) {
            if (i != r && std::fabs(A[i][s]) > eps) {
                const T f = std::exchange(A[i][s], 0);
                for (int j = 0; j < C; j++) {
                    if (j != s) {
                        A[i][j] -= f * A[r][j];
                    }
                }
            }
        }
        basis[r] = s;
    }
    
    auto work() {
        for (int i = 0; i < n; i++) {
            if (A[i].back() < -eps) {
                return std::tuple(2, inf, std::vector<T>{});
            }
        }
        while (true) {
            int s = -1, r = -1;
            T res = inf;
            for (int i = 0; i < V; i++) {
                if (A.back()[i] < -eps) {
                    s = i;
                    break;
                }
            }
            if (s == -1) {
                break;
            }
            for (int i = 0; i < n; i++) {
                if (A[i][s] > eps) {
                    T ratio = A[i].back() / A[i][s];
                    if (ratio < res - eps) {
                        res = ratio, r = i;
                    }
                }
            }
            if (r == -1) {
                return std::tuple(1, inf, std::vector<T>{});
            }
            pivot(r, s);
        }
        std::vector<T> X(m);
        for (int i = 0; i < n; i++) {
            if (basis[i] < m) {
                X[basis[i]] = A[i].back();
            }
        }
        return std::tuple(0, A[n].back(), std::move(X));
    }
};