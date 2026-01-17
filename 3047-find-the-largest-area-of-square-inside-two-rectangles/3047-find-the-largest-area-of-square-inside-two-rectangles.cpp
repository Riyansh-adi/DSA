class Solution {
public:
    long long largestSquareArea(vector<vector<int>>& bottomLeft,
                                vector<vector<int>>& topRight) {
        int n = bottomLeft.size();
        long long ans = 0;

        for (int i = 0; i < n; i++) {
            int ax1 = bottomLeft[i][0], ay1 = bottomLeft[i][1];
            int ax2 = topRight[i][0],   ay2 = topRight[i][1];

            for (int j = i + 1; j < n; j++) {
                int bx1 = bottomLeft[j][0], by1 = bottomLeft[j][1];
                int bx2 = topRight[j][0],   by2 = topRight[j][1];

                int left   = max(ax1, bx1);
                int right  = min(ax2, bx2);
                int bottom = max(ay1, by1);
                int top    = min(ay2, by2);

                int w = right - left;
                int h = top - bottom;

                if (w > 0 && h > 0) {
                    long long side = min(w, h);
                    ans = max(ans, side * side);
                }
            }
        }
        return ans;
    }
};
