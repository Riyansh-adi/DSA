class Solution {
public:
    int maxSideLength(vector<vector<int>>& mat, int threshold) {
        int n = mat.size(), m = mat[0].size();
        
        // prefix sum matrix (n+1 x m+1)
        vector<vector<int>> pre(n + 1, vector<int>(m + 1, 0));
        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                pre[i][j] = mat[i-1][j-1] 
                            + pre[i-1][j] 
                            + pre[i][j-1] 
                            - pre[i-1][j-1];
            }
        }
        
        // function to check if any k x k square has sum <= threshold
        auto possible = [&](int k) -> bool {
            for (int i = 0; i + k <= n; i++) {
                for (int j = 0; j + k <= m; j++) {
                    int sum = pre[i+k][j+k] - pre[i][j+k] - pre[i+k][j] + pre[i][j];
                    if (sum <= threshold) return true;
                }
            }
            return false;
        };
        
        int low = 0, high = min(n, m), ans = 0;
        
        while (low <= high) {
            int mid = (low + high) / 2;
            if (possible(mid)) {
                ans = mid;
                low = mid + 1;   // try bigger
            } else {
                high = mid - 1;  // try smaller
            }
        }
        
        return ans;
    }
};
