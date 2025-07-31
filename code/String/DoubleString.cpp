// need zvalue
int ans = 0;
auto dc = [&](auto self, string cur) -> void {
    int m = cur.size();
    if (m <= 1) return;
    string _s = cur.substr(0, m / 2), _t = cur.substr(m / 2, m);
    self(self, _s);
    self(self, _t);
    rep (T, 0, 2) {
        int m1 = _s.size(), m2 = _t.size();
        string s = _t + "$" + _s, t = _s;
        reverse(all(t));
        zvalue z1(s), z2(t);
        auto get_z = [&](zvalue &z, int x) -> int {
            if (0 <= x && x < z.z.size()) return z[x];
            return 0;
        };
        rep (i, 0, m1) if (_s[i] == _t[0]) {
            int len = m1 - i;
            int L = m1 - min(get_z(z2, m1 - i), len - 1), 
                R = get_z(z1, m2 + 1 + i);
            if (T == 0) R = min(R, len - 1);
            R = i + R;
            ans += max(0, R - L + 1);
        }
        swap(_s, _t);
        reverse(all(_s));
        reverse(all(_t));
    }
};
dc(dc, str);