#include <vector>



static void dfs(int row, int n, unsigned full,
                unsigned cols, unsigned d1, unsigned d2,
                std::vector<int>& cur,
                std::vector<std::vector<int>>& res) {
    if (row == n) { res.push_back(cur); return; }
    unsigned avail = full & ~(cols | d1 | d2);
    while (avail) {
        unsigned bit = avail & -avail;
        avail ^= bit;
        cur[row] = __builtin_ctz(bit);
        dfs(row + 1, n, full,
            cols | bit,
            ((d1 | bit) << 1) & full,
            (d2 | bit) >> 1,
            cur, res);
    }
}




std::vector<std::vector<int>> solveNQueens(int n) {
    std::vector<std::vector<int>> res;
    std::vector<int> cur(n);
    dfs(0, n, (1u << n) - 1, 0, 0, 0, cur, res);
    return res;
}
