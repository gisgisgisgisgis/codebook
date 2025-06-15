// a : Matrix; b, c: Vector
// Ax <= b, max c^T x
// T: double or long double
template <typename T>
struct Simplex {
    const T eps = 1E-7;
    const T inf = std::numeric_limits<T>::infinity();

    int n, m, vars, cols;
    std::vector<std::vector<T>> A;
    std::vector<int> basis;

    Simplex(auto& a, auto& b, auto& c) {
        init(a, b, c);
    }

    void init(auto& a, auto& b, auto& c) {
        n = b.size(), m = c.size();
        vars = n + m;
        cols = vars + 1;

        A.assign(n + 1, std::vector<T>(cols));

        for (int i = 0; i < n; i++) {
            ranges::copy(a[i], A[i].begin());
            A[i][m + i] = 1.0;
            A[i].back() = b[i];
        }
        ranges::transform(c, A[n].begin(), [](T x) {
            return -x;
        });

        basis.assign(n, 0);
        ranges::iota(basis, m);
    }

    void pivot(int r, int s) {
        T inv = 1.0 / A[r][s];
        for (auto& x : A[r]) {
            x *= inv;
        }
        for (int i = 0; i <= n; i++) {
            if (i != r && std::fabs(A[i][s]) > eps) {
                T f = std::exchange(A[i][s], 0);
                for (int j = 0; j < cols; j++) {
                    A[i][j] -= f * A[r][j];
                }
            }
        }
        basis[r] = s;
    }

    auto work() {
        while (true) {
            T res = inf;
            int s = -1, r = -1;
            for (int i = 0; i < vars; i++) {
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
                        res = ratio;
                        r = i;
                    }
                }
            }
            if (r == -1) {
                return std::pair(std::vector<T>{}, -1.0);
            }
            pivot(r, s);
        }

        std::vector<T> X(m);
        for (int i = 0; i < n; i++) {
            if (basis[i] < m) {
                X[basis[i]] = A[i].back();
            }
        }

        return std::pair(X, A[n].back());
    }
};
