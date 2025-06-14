std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
inline int rand(int l, int r) { return std::uniform_int_distribution<int>(l, r)(rng); }
inline i64 rand(i64 l, i64 r) { return std::uniform_int_distribution<i64>(l, r)(rng); }