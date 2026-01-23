#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumPairRemoval(vector<int>& nums) {
        int n = (int)nums.size();
        if (n <= 1) return 0;

        vector<long long> val(nums.begin(), nums.end());
        vector<int> nxt(n), prv(n);

        for (int i = 0; i < n; i++) {
            nxt[i] = i + 1;
            prv[i] = i - 1;
        }

        // ordered by (pairSum, index) -> index handles "leftmost tie"
        set<pair<long long,int>> st;
        for (int i = 0; i < n - 1; i++) {
            st.insert({val[i] + val[i + 1], i});
        }

        auto isInv = [&](int i) -> bool {
            int j = nxt[i];
            if (i < 0 || i >= n || j >= n) return false;
            return val[i] > val[j];
        };

        // count inversion boundaries
        int inv = 0;
        for (int i = 0; i < n - 1; i++) {
            if (val[i] > val[i + 1]) inv++;
        }

        int ops = 0;

        while (inv > 0) {
            ops++;

            // forced merge: smallest sum, leftmost if tie
            auto [sum, i] = *st.begin();
            st.erase(st.begin());

            int j = nxt[i];          // second element
            int L = prv[i];          // left neighbor
            int R = (j < n ? nxt[j] : n); // right neighbor of j

            // Remove affected pair sums from set (old links)
            if (L >= 0) {
                st.erase({val[L] + val[i], L});
            }
            if (j < n && R < n) {
                st.erase({val[j] + val[R], j});
            }

            // Update inversion count: remove old boundaries
            if (L >= 0) {
                if (val[L] > val[i]) inv--;
            }
            if (j < n) {
                if (val[i] > val[j]) inv--;
            }
            if (j < n && R < n) {
                if (val[j] > val[R]) inv--;
            }

            // Merge i and j into i
            val[i] = sum;

            // Relink: remove j
            nxt[i] = R;
            if (R < n) prv[R] = i;

            // Add new pair sums after relink
            if (L >= 0) {
                st.insert({val[L] + val[i], L});
            }
            if (R < n) {
                st.insert({val[i] + val[R], i});
            }

            // Add new inversion boundaries
            if (L >= 0) {
                if (val[L] > val[i]) inv++;
            }
            if (R < n) {
                if (val[i] > val[R]) inv++;
            }
        }

        return ops;
    }
};
