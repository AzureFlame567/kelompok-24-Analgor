#include <vector>
using namespace std;
typedef vector<int> V;



void f(int r, int n, unsigned a, unsigned b, unsigned c, V& v, vector<V>& s) {
    if (r == n) { s.push_back(v); return; }
    unsigned m = ((1u << n) - 1) & ~(a | b | c);
    while (m) {
        unsigned t = m & -m; m ^= t;
        v[r] = __builtin_ctz(t);
        f(r + 1, n, a | t, (b | t) << 1, (c | t) >> 1, v, s);
    }
}



vector<V> solveNQueens(int n) {
    vector<V> s; V v(n);
    f(0, n, 0, 0, 0, v, s);
    return s;
}