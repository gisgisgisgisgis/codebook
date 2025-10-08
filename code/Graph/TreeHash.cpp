u64 shift(u64 x) {
    x ^= mask;
    x ^= x << 7;
    x ^= x >> 21;
    x ^= x << 11;
    x ^= mask;
    return x;
}
void hash(int u, int pa) {
    hsh[u] = 1;
    for (int v : adj[u]) {
        if (v == pa) continue;
        hash(hash, v, u);
        hsh[u] += shift(hsh[v]);
    }
}