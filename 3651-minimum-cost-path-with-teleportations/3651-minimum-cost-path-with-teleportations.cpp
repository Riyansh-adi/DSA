#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <tuple>

using namespace std;

class Solution {
public:
    int minCost(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();

        // --- 1. Preprocessing & Coordinate Compression ---
        // Map unique grid values to ranks (0, 1, 2...) for Virtual Nodes.
        vector<int> unique_vals;
        for (const auto& row : grid) {
            for (int val : row) {
                unique_vals.push_back(val);
            }
        }
        sort(unique_vals.begin(), unique_vals.end());
        unique_vals.erase(unique(unique_vals.begin(), unique_vals.end()), unique_vals.end());

        // Helper to find rank of a value
        auto get_rank = [&](int val) {
            return lower_bound(unique_vals.begin(), unique_vals.end(), val) - unique_vals.begin();
        };

        int num_ranks = unique_vals.size();
        
        // Group physical cells by their value's rank.
        // cells_by_rank[r] contains all (row, col) coordinates that have value with rank r.
        vector<vector<pair<int, int>>> cells_by_rank(num_ranks);
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                cells_by_rank[get_rank(grid[r][c])].push_back({r, c});
            }
        }

        // --- 2. Dijkstra's Algorithm Setup ---
        // Priority Queue stores: {cost, used_k, type, u, v}
        // type 0: Physical Node at (u, v)
        // type 1: Virtual Node at Rank u (v is ignored)
        using State = tuple<int, int, int, int, int>;
        priority_queue<State, vector<State>, greater<State>> pq;

        // Distance arrays
        // dist[used_k][row][col]
        vector<vector<vector<int>>> dist(k + 1, vector<vector<int>>(m, vector<int>(n, 1e9)));
        // dist_virt[used_k][rank]
        vector<vector<int>> dist_virt(k + 1, vector<int>(num_ranks, 1e9));

        // Initial State
        dist[0][0][0] = 0;
        pq.push({0, 0, 0, 0, 0});

        while (!pq.empty()) {
            auto [cost, used_k, type, u, v] = pq.top();
            pq.pop();

            if (type == 1) { 
                // --- Case A: Virtual Node (In Teleport Network) ---
                int rank = u;
                if (cost > dist_virt[used_k][rank]) continue;

                // 1. Flow Down: If we can land on rank 'i', we can land on 'i-1'
                if (rank > 0) {
                    if (cost < dist_virt[used_k][rank - 1]) {
                        dist_virt[used_k][rank - 1] = cost;
                        pq.push({cost, used_k, 1, rank - 1, 0});
                    }
                }

                // 2. Land: Jump to physical cells with this exact value
                for (auto& p : cells_by_rank[rank]) {
                    int r = p.first;
                    int c = p.second;
                    // Landing cost is 0, so new cost is just current cost
                    if (cost < dist[used_k][r][c]) {
                        dist[used_k][r][c] = cost;
                        pq.push({cost, used_k, 0, r, c});
                    }
                }

            } else {
                // --- Case B: Physical Node (On Grid) ---
                int r = u;
                int c = v;

                if (cost > dist[used_k][r][c]) continue;
                if (r == m - 1 && c == n - 1) return cost;

                // 1. Normal Moves (Right, Down)
                int dr[] = {0, 1};
                int dc[] = {1, 0};
                for (int i = 0; i < 2; ++i) {
                    int nr = r + dr[i];
                    int nc = c + dc[i];

                    if (nr >= 0 && nr < m && nc >= 0 && nc < n) {
                        int new_cost = cost + grid[nr][nc];
                        if (new_cost < dist[used_k][nr][nc]) {
                            dist[used_k][nr][nc] = new_cost;
                            pq.push({new_cost, used_k, 0, nr, nc});
                        }
                    }
                }

                // 2. Start Teleport (Physical -> Virtual)
                if (used_k < k) {
                    int rank = get_rank(grid[r][c]);
                    // Enter virtual network at current value's rank
                    // Cost is 0 to enter, increment K
                    if (cost < dist_virt[used_k + 1][rank]) {
                        dist_virt[used_k + 1][rank] = cost;
                        pq.push({cost, used_k + 1, 1, rank, 0});
                    }
                }
            }
        }

        return -1; // Should not reach here
    }
};