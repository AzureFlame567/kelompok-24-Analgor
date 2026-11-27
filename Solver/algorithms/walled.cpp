#include "nqueens.h"
#include <vector>
#include <string>
#include <utility>
using namespace std;

struct Z {
    int N, B = 0;
    vector<int> I[4], R;
    vector<char> W, U;
    vector<pair<int, int>> C;
    vector<vector<pair<int, int>>> S;

    Z(int n, const vector<string>& g) : N(n), R(n + 1, 0), W(n * n, 0) {
        for (auto& i : I) i.assign(n * n, -1);
        const int dr[] = {0, -1, -1, -1}, dc[] = {-1, 0, -1, 1};
        int t = 0;
        for (int r = 0; r < n; r++)
            for (int c = 0; c < n; c++) {
                int p = r * n + c;
                if (W[p] = g[r][c] != '.') continue;
                for (int k = 0; k < 4; k++) {
                    int y = r + dr[k], x = c + dc[k];
                    if (y >= 0 && x >= 0 && x < n && !W[y * n + x]) I[k][p] = I[k][y * n + x];
                    else { I[k][p] = t++; if (!k) R[r]++; }
                }
            }
        U.assign(t, 0);
        for (int r = n - 1; r >= 0; r--) R[r] += R[r + 1];
    }

    void d(int s, int k) {
        if (k >= B) { if (k > B) { B = k; S.clear(); } S.push_back(C); }
        for (int p = s; p < N * N; p++) {
            if (k + R[p / N] < B) break;
            if (W[p]) continue;
            int a = I[0][p], b = I[1][p], c = I[2][p], e = I[3][p];
            if (U[a] | U[b] | U[c] | U[e]) continue;
            U[a] = U[b] = U[c] = U[e] = 1;
            C.emplace_back(p / N, p % N);
            d(p + 1, k + 1);
            C.pop_back();
            U[a] = U[b] = U[c] = U[e] = 0;
        }
    }
};

vector<vector<pair<int, int>>> solveWalled(int n, const vector<string>& g) {
    Z z(n, g);
    z.d(0, 0);
    return z.S;
}
