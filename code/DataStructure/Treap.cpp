struct Treap{
    Treap *l, *r;
    int key, size;
    Treap(int k) : l(nullptr), r(nullptr), key(k), size(1) {}
    void pull();
    void push() {};
};

inline int SZ(Treap *p){
    return p == nullptr ? 0 : p->size;
}

void Treap::pull() {
    size = 1 + SZ(l) + SZ(r);
}

Treap *merge(Treap *a, Treap *b){
    if (!a || !b) return a ? a : b;
    if (rand() % (SZ(a) + SZ(b)) < SZ(a)) {
        return a->push(), a->r = merge(a->r, b), a->pull(), a;
    }
    return b->push(), b->l = merge(a, b->l), b->pull(), b;
}
// <= k, > k
void split(Treap *p, Treap *&a, Treap *&b, int k) { // by key
    if (!p) return a = b = nullptr, void();
    p->push();
    if (p->key <= k) {
        a = p, split(p->r, a->r, b, k), a->pull();
    } else {
        b = p, split(p->l, a, b->l, k), b->pull();
    }
}
// k, n - k
void split2(Treap *p, Treap *&a, Treap *&b, int k) { // by size
    if (!p) return a = b = nullptr, void();
    p->push();
    if (SZ(p->l) + 1 <= k) {
        a = p, split2(p->r, a->r, b, k - SZ(p->l) - 1);
    } else {
        b = p, split2(p->l, a, b->l, k);
    }
    p->pull();
}

void insert(Treap *&p, int k) {
    Treap *l, *r;
    p->push(), split(p, l, r, k);
    p = merge(merge(l, new Treap(k)), r);
    p->pull();
}

bool erase(Treap *&p, int k) {
    if (!p) return false;
    if (p->key == k) {
        Treap *t = p;
        p->push(), p = merge(p->l, p->r);
        delete t;
        return true;
    } 
    Treap *&t = k < p->key ? p->l : p->r;
    return erase(t, k) ? p->pull(), true : false;
}

int Rank(Treap *p, int k) {
    if (!p) return 0;
    if (p->key < k) return SZ(p->l) + 1 + Rank(p->r, k);
    return Rank(p->l, k);
}

Treap *kth(Treap *p, int k) {
    if (k <= SZ(p->l)) return kth(p->l, k);
    if (k == SZ(p->l) + 1) return p;
    return kth(p->r, k - SZ(p->l) - 1);
}

tuple<Treap*, Treap*, Treap*> interval(Treap *&o, int l, int r) { // 1-based
    Treap *a, *b, *c; // b: [l, r]
    split2(o, a, b, l - 1), split2(b, b, c, r - l + 1);
    return make_tuple(a, b, c);
}