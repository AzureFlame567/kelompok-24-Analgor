#include <vector>
#include <utility>

static void dfs(int r, int n, unsigned full,
                unsigned cols, unsigned ad, unsigned md,
                const std::vector<int>& fix,
                std::vector<int>& cur,
                std::vector<std::vector<int>>& res) {
    while (r < n && fix[r] >= 0) ++r;   
    if (r == n) { res.push_back(cur); return; }

    unsigned avail = full & ~(cols | (ad >> r) | (md >> (n - 1 - r)));
    while (avail) {
        unsigned bit = avail & -avail;
        avail ^= bit;
        int c = __builtin_ctz(bit);
        cur[r] = c;
        dfs(r + 1, n, full,
            cols | bit,
            ad | (1u << (r + c)),
            md | (1u << (c - r + n - 1)),
            fix, cur, res);
    }
}



std::vector<std::vector<int>> solvePreplaced(
        int n, const std::vector<std::pair<int, int>>& preplaced) {
    std::vector<std::vector<int>> res;
    std::vector<int> fix(n, -1), cur(n, -1);
    unsigned full = (1u << n) - 1, cols = 0, ad = 0, md = 0;

    for (const auto& p : preplaced) {
        int r = p.first, c = p.second;
        if (r < 0 || r >= n || c < 0 || c >= n) return res;  
        if (fix[r] >= 0) return res;                         
        unsigned bit = 1u << c;
        unsigned a = 1u << (r + c), m = 1u << (c - r + n - 1);
        if ((cols & bit) || (ad & a) || (md & m)) return res;  
        fix[r] = cur[r] = c;
        cols |= bit; ad |= a; md |= m;
    }

    dfs(0, n, full, cols, ad, md, fix, cur, res);
    return res;
}