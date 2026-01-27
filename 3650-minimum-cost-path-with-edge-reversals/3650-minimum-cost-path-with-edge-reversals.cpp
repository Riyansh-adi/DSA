class Solution {
public:
    int minCost(int n, vector<vector<int>>& edges) {
        vector<vector<pair<int,int>>> out(n), in(n);

        // Build outgoing and incoming edge lists
        for (auto &e : edges) {
            int u = e[0], v = e[1], w = e[2];
            out[u].push_back({v, w});
            in[v].push_back({u, w});
        }

        vector<long long> dist(n, LLONG_MAX);
        priority_queue<pair<long long,int>, 
                       vector<pair<long long,int>>, 
                       greater<>> pq;

        dist[0] = 0;
        pq.push({0, 0});

        while (!pq.empty()) {
            auto [cost, u] = pq.top();
            pq.pop();

            if (cost > dist[u]) continue;
            if (u == n - 1) return cost;

            // 1️⃣ Normal outgoing edges
            for (auto &[v, w] : out[u]) {
                if (dist[v] > cost + w) {
                    dist[v] = cost + w;
                    pq.push({dist[v], v});
                }
            }

            // 2️⃣ Reverse incoming edges using switch at u
            for (auto &[v, w] : in[u]) {
                long long newCost = cost + 2LL * w;
                if (dist[v] > newCost) {
                    dist[v] = newCost;
                    pq.push({newCost, v});
                }
            }
        }

        return dist[n - 1] == LLONG_MAX ? -1 : dist[n - 1];
    }
};
