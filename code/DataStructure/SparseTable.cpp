template<class T>
struct SparseTable{
    function<T(T, T)> F;
    vector<vector<T>> sp;
    SparseTable(vector<T> &a, const auto &f) {
        F = f;
        int n = a.size();
        sp.resize(n, vector<T>(__lg(n) + 1));
        for (int i = n - 1; i >= 0; i--) {
            sp[i][0] = a[i];
            for (int j = 1; i + (1 << j) <= n; j++) {
                sp[i][j] = F(sp[i][j - 1], sp[i + (1 << j - 1)][j - 1]);
            }
        }
    }
    T query(int l, int r) { // [l, r)
        int k = __lg(r - l);
        return F(sp[l][k], sp[r - (1 << k)][k]);
    }
};