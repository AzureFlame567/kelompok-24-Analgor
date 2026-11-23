#include <vector>
#include <string>
using namespace std;
typedef vector<int> V;



void h(int r, int n, unsigned a, unsigned b, unsigned c, vector<unsigned>& x, V& v, vector<V>& s) {
    if (r == n) { s.push_back(v); return; }
    unsigned m = ((1u << n) - 1) & ~(a | b | c | x[r]);
    while (m) {
        unsigned t = m & -m; m ^= t;
        v[r] = __builtin_ctz(t);
        h(r + 1, n, a | t, (b | t) << 1, (c | t) >> 1, x, v, s);
    }
}

vector<V> solveHoles(int n, const vector<string>& w) {
    vector<unsigned> x(n); V v(n); vector<V> s;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (w[i][j] != '.') x[i] |= 1u << j;
    h(0, n, 0, 0, 0, x, v, s);
    return s;
}