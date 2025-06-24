// \sum_0^n floor((a * x + b) / c)) in log(n + m + a + b)
int floor_sum(int a, int b, int c, int n) { // add mod if needed
    int m = (a * n + b) / c;
    if (a >= c || b >= c)
        return (a / c) * (n * (n + 1) / 2) + (b / c) * (n + 1) + floor_sum(a % c, b % c, c, n);
    if (n < 0 || a == 0)
        return 0;
    return n * m - floor_sum(c, c - b - 1, a, m - 1);
}