struct zvalue {
    vector<int> z;
    int operator[](const int& x) const {
        return z[x];
    }
    zvalue(string s) {
        int n = s.size();
        z.resize(n);
        z[0] = 0;
        for (int i = 1, l = 1, r = 0; i < n; i++) {
            z[i] = min(z[i - l], max<int>(0, r - i));
            while (i + z[i] < n && s[i + z[i]] == s[z[i]]) z[i]++;
            if (i + z[i] > r) l = i, r = i + z[i];
        }
    }
};