struct Cir { 
    Pt o;
    double r;
    bool inside(Pt p) {
        return sgn(r - abs(p - o)) >= 0;
    } 
};
bool disjunct(const Cir &a, const Cir &b) {
    return sgn(abs(a.o - b.o) - a.r - b.r) >= 0; 
}
bool contain(const Cir &a, const Cir &b) {
    return sgn(a.r - b.r - abs(a.o - b.o)) >= 0; 
}