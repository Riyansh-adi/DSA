class Solution {
public:
    int maximizeSquareArea(int m, int n, vector<int>& hFences, vector<int>& vFences) {
        const long long MOD = 1e9 + 7;

        // add boundaries
        hFences.push_back(1);
        hFences.push_back(m);
        vFences.push_back(1);
        vFences.push_back(n);

        sort(hFences.begin(), hFences.end());
        sort(vFences.begin(), vFences.end());

        unordered_set<int> hDiff;

        // store all horizontal differences
        for (int i = 0; i < (int)hFences.size(); i++) {
            for (int j = 0; j < i; j++) {
                hDiff.insert(hFences[i] - hFences[j]);
            }
        }

        long long best = -1;

        // check vertical differences
        for (int i = 0; i < (int)vFences.size(); i++) {
            for (int j = 0; j < i; j++) {
                int d = vFences[i] - vFences[j];
                if (hDiff.count(d)) best = max(best, (long long)d);
            }
        }

        if (best == -1) return -1;
        return (best * best) % MOD;
    }
};
