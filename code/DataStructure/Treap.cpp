struct Treap {
    Treap *l, *r;
    int size, pri;
    Treap() : l(nullptr), r(nullptr), size(1), pri(rand()) {}
    void pull();
};

inline int sz(Treap *p) {
    return (p == nullptr ? 0 : p->size);
}

void Treap::pull() {
    size = sz(l) + sz(r) + 1;
}

Treap *merge(Treap *a, Treap *b) {
    if (a == nullptr) return b;
    if (b == nullptr) return a;
    if (a->pri < b->pri) {
        a->r = merge(a->r, b);
        a->pull();
        return a;
    } else {
        b->l = merge(a, b->l);
        b->pull();
        return b;
    }
}
 
void split(Treap *root, Treap *&a, Treap *&b, int k) {
    if (root == nullptr) {
        a = b = nullptr;
        return;
    }
    if (sz(root->l) < k) {
        a = root;
        split(root->r, a->r, b, k - sz(root->l) - 1);
        a->pull();
    } else {
        b = root;
        split(root->l, a, b->l, k);
        b->pull();
    }
}