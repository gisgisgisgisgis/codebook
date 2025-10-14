vector<Pt> BuildHull(vector<Pt> pt) {
    sort(all(pt));
    pt.erase(unique(all(pt)), pt.end());
    if (pt.size() <= 2) return pt;
    vector<Pt> hull;
    int sz = 1;
    rep (t, 0, 2) {
        rep (i, t, ssize(pt)) {
            while (ssize(hull) > sz && ori(hull.end()[-2], pt[i], hull.back()) >= 0)
                hull.pop_back();
            hull.push_back(pt[i]);
        }
        sz = ssize(hull);
        reverse(all(pt));
    }
    hull.pop_back();
    return hull;
}
