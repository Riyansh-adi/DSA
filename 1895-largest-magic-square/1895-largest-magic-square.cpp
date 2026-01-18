class Solution {
public:
    int largestMagicSquare(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();

        // rowPrefix[i][j] = sum of row i from col 0 to j-1
        vector<vector<int>> rowPrefix(m, vector<int>(n + 1, 0));
        // colPrefix[i][j] = sum of col j from row 0 to i-1
        vector<vector<int>> colPrefix(m + 1, vector<int>(n, 0));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                rowPrefix[i][j + 1] = rowPrefix[i][j] + grid[i][j];
                colPrefix[i + 1][j] = colPrefix[i][j] + grid[i][j];
            }
        }

        auto getRowSum = [&](int r, int c1, int c2) {  // inclusive c1..c2
            return rowPrefix[r][c2 + 1] - rowPrefix[r][c1];
        };

        auto getColSum = [&](int c, int r1, int r2) {  // inclusive r1..r2
            return colPrefix[r2 + 1][c] - colPrefix[r1][c];
        };

        // Try larger squares first
        for (int k = min(m, n); k >= 2; k--) {
            for (int r = 0; r + k - 1 < m; r++) {
                for (int c = 0; c + k - 1 < n; c++) {

                    int target = getRowSum(r, c, c + k - 1);

                    bool ok = true;

                    // check all rows
                    for (int i = r; i < r + k; i++) {
                        if (getRowSum(i, c, c + k - 1) != target) {
                            ok = false;
                            break;
                        }
                    }
                    if (!ok) continue;

                    // check all cols
                    for (int j = c; j < c + k; j++) {
                        if (getColSum(j, r, r + k - 1) != target) {
                            ok = false;
                            break;
                        }
                    }
                    if (!ok) continue;

                    // check main diagonal
                    int diag1 = 0;
                    for (int t = 0; t < k; t++)
                        diag1 += grid[r + t][c + t];

                    if (diag1 != target) continue;

                    // check anti diagonal
                    int diag2 = 0;
                    for (int t = 0; t < k; t++)
                        diag2 += grid[r + t][c + (k - 1 - t)];

                    if (diag2 != target) continue;

                    return k; // largest found
                }
            }
        }

        return 1; // any single cell is always a magic square
    }
};
