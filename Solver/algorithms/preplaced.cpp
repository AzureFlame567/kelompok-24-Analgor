#include <vector>
#include <utility>
using namespace std;
typedef vector<int> V;



void g(int r, int n, unsigned a, unsigned b, unsigned c, V& x, V& v, vector<V>& s) {
    while (r < n && x[r] >= 0) r++;
    if (r == n) { s.push_back(v); return; }
    unsigned m = ((1u << n) - 1) & ~(a | b >> r | c >> (n - 1 - r));
    while (m) {
        unsigned t = m & -m; m ^= t;
        int k = __builtin_ctz(t);
        v[r] = k;
        g(r + 1, n, a | t, b | 1u << r + k, c | 1u << k - r + n - 1, x, v, s);
    }
}
vector<V> solvePreplaced(int n, const vector<pair<int, int>>& p) {
    vector<V> s; V x(n, -1), v(n, -1);
    unsigned a = 0, b = 0, c = 0;
    for (auto& q : p) {
        int r = q.first, k = q.second;
        x[r] = v[r] = k;
        a |= 1u << k; b |= 1u << r + k; c |= 1u << k - r + n - 1;
    }
    g(0, n, a, b, c, x, v, s);
    return s;
}