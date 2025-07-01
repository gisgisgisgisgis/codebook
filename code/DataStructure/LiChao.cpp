struct Line {
    int m, k = -INF;
    Line() {}
    Line(int _m, int _k) : m(_m), k(_k) {}
    int operator () (const int &x) const {
        return m * x + k;
    }
};
// max LiChao
struct Node {
    Line line;
    int ls, rs;
    Node() {}
    Node(Line li) : ls(0), rs(0), line(li) {}
};
struct LiChao {  
    vector<Node> tree;
    LiChao () : tree(1) {};
    int newnode(Line line) {
        tree.push_back(Node(line));
        return ssize(tree) - 1;
    }
    void insert (int &pos, int l, int r, Line line) {
        if (pos == 0) {
            pos = newnode(line);
            return;
        }
        auto &tr = tree[pos].line;
        if (l == r) {
            if (line(l) > tr(l)) tr = line;
            return;
        }
        int mid = l + r >> 1;
        if (tr(mid) < line(mid)) swap(tr, line);
        if (tr.m >= line.m) {
            insert(tree[pos].ls, l, mid, line);
        } else {
            insert(tree[pos].rs, mid + 1, r, line);
        }
    }
    int query (int pos, int l, int r, int x) {
        if (pos == 0) return -INF;
        if (l == r) return tree[pos].line(x);
        int mid = l + r >> 1;
        if (x <= mid) return max(query(tree[pos].ls, l, mid, x), tree[pos].line(x));
        else return max(query(tree[pos].rs, mid + 1, r, x), tree[pos].line(x));
    }
};