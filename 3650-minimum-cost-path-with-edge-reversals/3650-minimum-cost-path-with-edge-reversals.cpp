class Solution {
public:
    int minCost(int n, vector<vector<int>>& edges) {
        // Adjacency list: node -> {neighbor, cost}
        vector<vector<pair<int,int>>> graph(n);
        
        // Build graph
        for (auto &e : edges) {
            int u = e[0];
            int v = e[1];
            
            graph[u].push_back({v, 0}); // use edge as-is
            graph[v].push_back({u, 1}); // reverse edge
        }
        
        // Distance array
        vector<int> dist(n, INT_MAX);
        deque<int> dq;
        
        // Start from node 0
        dist[0] = 0;
        dq.push_front(0);
        
        // 0-1 BFS
        while (!dq.empty()) {
            int node = dq.front();
            dq.pop_front();
            
            for (auto &edge : graph[node]) {
                int next = edge.first;
                int cost = edge.second;
                
                if (dist[node] + cost < dist[next]) {
                    dist[next] = dist[node] + cost;
                    
                    if (cost == 0)
                        dq.push_front(next);
                    else
                        dq.push_back(next);
                }
            }
        }
        
        // If destination unreachable
        return dist[n - 1] == INT_MAX ? -1 : dist[n - 1];
    }
};
