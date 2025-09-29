#include <unistd.h>
int OP;
char OB[65536];
inline char RC() {
    static char buf[65536], *p = buf, *q = buf;
    return p == q && (q = (p = buf) + read(0, buf, 65536)) == buf ? -1 : *p++;
}
inline int R() {
    static char c;
    while ((c = RC()) < '0');
    int a = c ^ '0';
    while ((c = RC()) >= '0') a *= 10, a += c ^ '0';
    return a;
}
inline void W(int n) {
    static char buf[12], p;
    if (n == 0) OB[OP++] = '0';
    p = 0;
    while (n) buf[p++] = '0' + (n % 10), n /= 10;
    for (--p; p >= 0; --p) OB[OP++] = buf[p];
    if (OP > 65520) write(1, OB, OP), OP = 0;
}
// {b95f3b}

// another FastIO
char buf[1 << 21], *p1 = buf, *p2 = buf;
inline char getc() {
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? 0 : *p1++;
}
template<typename T> void Cin(T &a) {
    T res = 0; int f = 1;
    char c = getc();
    for (; c < '0' || c > '9'; c = getc()) {
        if (c == '-') f = -1;
    }
    for (; c >= '0' && c <= '9'; c = getc()) {
        res = res * 10 + c - '0';
    }
    a = f * res;
}
template<typename T, typename... Args> void Cin(T &a, Args &...args) {
    Cin(a), Cin(args...);
}
template<typename T> void Cout(T x) { // there's no '\n' in output
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) Cout(x / 10);
    putchar(x % 10 + '0');
}
// {795778}
