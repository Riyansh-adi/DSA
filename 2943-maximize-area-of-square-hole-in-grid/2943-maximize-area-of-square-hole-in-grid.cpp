class Solution {
public:
    int maxConsecutive(vector<int>& bars) {
        sort(bars.begin(), bars.end());
        int best = 1, cur = 1;

        for (int i = 1; i < (int)bars.size(); i++) {
            if (bars[i] == bars[i - 1] + 1) cur++;   // consecutive
            else cur = 1;                            // reset
            best = max(best, cur);
        }
        return best;
    }

    int maximizeSquareHoleArea(int n, int m, vector<int>& hBars, vector<int>& vBars) {
        int maxH = maxConsecutive(hBars) + 1; // +1 because bars removal merges cells
        int maxV = maxConsecutive(vBars) + 1;

        int side = min(maxH, maxV);
        return side * side;
    }
};
