map<int, int> odt;
// initialize edges odt[1] and odt[n + 1]
auto split = [&](const int &x) -> void {
    const auto it = prev(odt.upper_bound(x));
    odt[x] = it->second;
};
auto merge = [&](const int &l, const int &r) -> void {
    auto itl = odt.lower_bound(l), itr = odt.lower_bound(r + 1);
    for (; itl != itr; itl = odt.erase(itl)) {
        // do something
    }
    // assign value to odt[l]
};