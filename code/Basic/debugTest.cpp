#include <bits/stdc++.h>
namespace ranges = std::ranges;

#ifdef PEPPA
template <typename R>
concept I = ranges::range<R> && !std::same_as<ranges::range_value_t<R>, char>;
template <typename A, typename B>
std::ostream &operator<<(std::ostream &o, const std::pair<A, B> &p) {
    return o << "(" << p.first << ", " << p.second << ")";
}
template <I T>
std::ostream &operator<<(std::ostream &o, const T &v) {
    o << "{";
    int f = 0;
    for (auto &&i : v) o << (f++ ? " " : "") << i;
    return o << "}";
}
void debug__(int c, auto &&...a) {
    std::cerr << "\e[1;" << c << "m";
    (..., (std::cerr << a << " "));
    std::cerr << "\e[0m" << std::endl;
}
#define debug_(c, x...) debug__(c, __LINE__, "[" + std::string(#x) + "]", x)
#define debug(x...) debug_(93, x)
#else
#define debug(x...) void(0)
#endif

int main() {
    // basic type
    int x_i = 123;
    double x_d = 3.14159;
    bool x_b = true;
    debug(x_i, x_d, x_b);

    // string
    std::string str = "hello";
    debug(str);

    // STL container
    std::vector<int> vec = {1, 2, 3, 5, 8};
    std::list<double> li = {2.71, 1.41, 1.62};
    std::deque<bool> dq = {true, false, true};
    debug(vec);
    debug(li);
    debug(dq);

    // interable STL test
    std::map<std::string, int> mp = {{"foo", 10}, {"bar", 20}};
    std::unordered_set<int> us = {42, 7, 13};
    debug(mp);
    debug(us);

    // C array
    int arr[5] = {10, 20, 30, 40, 50};
    debug(arr);

    std::array<int, 5> stl_arr = {10, 20, 30, 40, 50};
    debug(stl_arr);

    // pair
    std::pair<int, std::string> pa = {7, "seven"};
    std::vector<std::pair<std::string, double>> vec_pa = {{"pi", 3.14}, {"e", 2.71}};
    debug(pa);
    debug(vec_pa);

    // multiple test
    debug(x_i, str, vec, mp, vec_pa);

    return 0;
}
