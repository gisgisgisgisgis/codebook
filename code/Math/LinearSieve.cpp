const int C = 1e6 + 5;

int mo[C], lp[C], phi[C], isp[C]; 
vector<int> prime;

void sieve() {
    mo[1] = phi[1] = 1;
    rep (i, 1, C) lp[i] = 1;
    rep (i, 2, C) {
        if (lp[i] == 1) {
            lp[i] = i;
            prime.pb(i);
            isp[i] = 1;
            mo[i] = -1;
            phi[i] = i - 1;
        }
        for (int p : prime) {
            if (i * p >= C) break;
            lp[i * p] = p;
            if (i % p == 0) {
                phi[p * i] = phi[i] * p;
                break;
            }
            phi[i * p] = phi[i] * (p - 1);
            mo[i * p] = mo[i] * mo[p];
        }
    }
}