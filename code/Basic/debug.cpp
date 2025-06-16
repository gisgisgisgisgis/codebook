#ifdef PEPPA
template <typename R>
concept I = ranges::range<R> && !std::same_as<ranges::range_value_t<R>, char>;
template <typename A, typename B>
std::ostream& operator<<(std::ostream& o, const std::pair<A, B>& p) {
    return o << "(" << p.first << ", " << p.second << ")";
}
template <I T>
std::ostream& operator<<(std::ostream& o, const T& v) {
    o << "{";
    int f = 0;
    for (auto i : v) o << (f++ ? " " : "") << i;
    return o << "}";
}
void debug__(int c, auto&&... a) {
    std::cerr << "\e[1;" << c << "m";
    (..., (std::cerr << a << " "));
    std::cerr << "\e[0m" << std::endl;
}
#define debug_(c, x...) debug__(c, __LINE__, "[" + std::string(#x) + "]", x)
#define debug(x...) debug_(93, x)
#else
#define debug(x...) void(0)
#endif