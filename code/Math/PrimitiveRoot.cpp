ull primitiveRoot(ull p) {
    auto fac = factor(p - 1);
    sort(all(fac));
    fac.erase(unique(all(fac)), fac.end());
    auto test = [p, fac](ull x) {
        for(ull d : fac)
        if (modpow(x, (p - 1) / d, p) == 1)
            return false;
        return true;
    };
    uniform_int_distribution<ull> unif(1, p - 1);
    ull root;
    while(!test(root = unif(rng)));
    return root;
}