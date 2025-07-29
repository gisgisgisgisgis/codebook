struct Timer {
    int t;
    bool enable = false;

    void start() {
        enable = true;
        t = std::clock();
    }
    int msecs() {
        assert(enable);
        return (std::clock() - t) * 1000 / CLOCKS_PER_SEC;
    }
};
